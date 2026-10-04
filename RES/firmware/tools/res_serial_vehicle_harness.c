#ifdef _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "res_protocol.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RES_TEST_BAUD_RATE       9600u
#define RES_TEST_DEFAULT_FRAMES  30u
#define RES_TEST_DEFAULT_MS      15000u
#define RES_VEHICLE_SAFE_STOP    4u

static const uint8_t auth_key[RES_AUTH_KEY_SIZE] = {
    0x63u, 0x68u, 0x61u, 0x6Eu, 0x67u, 0x65u, 0x2Du, 0x74u,
    0x68u, 0x69u, 0x73u, 0x2Du, 0x6Bu, 0x65u, 0x79u, 0x21u
};

static bool configure_serial(HANDLE port)
{
    DCB dcb = {0};
    COMMTIMEOUTS timeouts = {0};

    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(port, &dcb)) {
        return false;
    }
    dcb.BaudRate = RES_TEST_BAUD_RATE;
    dcb.ByteSize = 8u;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fBinary = TRUE;
    dcb.fParity = FALSE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fTXContinueOnXoff = TRUE;
    dcb.fOutX = FALSE;
    dcb.fInX = FALSE;
    dcb.fErrorChar = FALSE;
    dcb.fNull = FALSE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError = FALSE;
    if (!SetCommState(port, &dcb)) {
        return false;
    }

    timeouts.ReadIntervalTimeout = 20u;
    timeouts.ReadTotalTimeoutConstant = 40u;
    timeouts.ReadTotalTimeoutMultiplier = 0u;
    timeouts.WriteTotalTimeoutConstant = 300u;
    timeouts.WriteTotalTimeoutMultiplier = 2u;
    return SetCommTimeouts(port, &timeouts) != FALSE;
}

static bool write_all(HANDLE port, const uint8_t *data, size_t length)
{
    size_t offset = 0u;

    while (offset < length) {
        DWORD written = 0u;
        const DWORD remaining = (DWORD)(length - offset);
        if (!WriteFile(port, data + offset, remaining, &written, NULL) ||
            (written == 0u)) {
            return false;
        }
        offset += written;
    }
    return true;
}

static bool send_safe_ack(HANDLE port,
                          const res_frame_t *received,
                          uint32_t *next_sequence)
{
    res_frame_t reply;
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    size_t encoded_length;

    memset(&reply, 0, sizeof(reply));
    reply.type = RES_MSG_ACK;
    reply.source = RES_NODE_VEHICLE;
    reply.destination = RES_NODE_REMOTE;
    reply.channel = received->channel;
    reply.sequence = (*next_sequence)++;
    reply.session = 0x56544331u; /* "VTC1": deterministic test session. */
    reply.payload_length = 8u;
    reply.payload[0] = received->type;
    reply.payload[1] = RES_VEHICLE_SAFE_STOP;
    reply.payload[2] = 0u; /* Both safety relays reported open. */
    reply.payload[3] = 0u;
    res_put_u32_le(reply.payload + 4u, received->sequence);

    encoded_length = res_frame_encode(encoded, sizeof(encoded), &reply, auth_key);
    return (encoded_length != 0u) && write_all(port, encoded, encoded_length);
}

static void make_device_path(char path[16], const char *port_name)
{
    if (strncmp(port_name, "\\\\.\\", 4u) == 0) {
        (void)snprintf(path, 16u, "%s", port_name);
    } else {
        (void)snprintf(path, 16u, "\\\\.\\%s", port_name);
    }
}

int main(int argc, char **argv)
{
    char device_path[16];
    HANDLE port;
    res_stream_parser_t parser;
    uint32_t next_sequence = 1u;
    unsigned target_frames = RES_TEST_DEFAULT_FRAMES;
    unsigned timeout_ms = RES_TEST_DEFAULT_MS;
    unsigned valid_frames = 0u;
    unsigned hello_frames = 0u;
    unsigned heartbeat_frames = 0u;
    unsigned acks_sent = 0u;
    unsigned invalid_bytes = 0u;
    uint32_t remote_session = 0u;
    const ULONGLONG start_ms = GetTickCount64();

    if (argc < 2) {
        fprintf(stderr,
                "Usage: %s COMx [valid_frame_count] [timeout_ms]\n",
                argv[0]);
        return 2;
    }
    if (argc >= 3) {
        target_frames = (unsigned)strtoul(argv[2], NULL, 10);
    }
    if (argc >= 4) {
        timeout_ms = (unsigned)strtoul(argv[3], NULL, 10);
    }
    make_device_path(device_path, argv[1]);
    port = CreateFileA(device_path,
                       GENERIC_READ | GENERIC_WRITE,
                       0u,
                       NULL,
                       OPEN_EXISTING,
                       0u,
                       NULL);
    if (port == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Cannot open %s (Win32 error %lu).\n",
                argv[1], (unsigned long)GetLastError());
        return 3;
    }
    if (!configure_serial(port)) {
        fprintf(stderr, "Cannot configure %s (Win32 error %lu).\n",
                argv[1], (unsigned long)GetLastError());
        CloseHandle(port);
        return 4;
    }

    PurgeComm(port, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
    res_stream_parser_init(&parser);
    printf("Listening on %s at %u 8N1; replies always report safe STOP.\n",
           argv[1], RES_TEST_BAUD_RATE);

    while (((GetTickCount64() - start_ms) < timeout_ms) &&
           (valid_frames < target_frames)) {
        uint8_t input[128];
        DWORD bytes_read = 0u;
        DWORD index;

        if (!ReadFile(port, input, sizeof(input), &bytes_read, NULL)) {
            fprintf(stderr, "Read failed (Win32 error %lu).\n",
                    (unsigned long)GetLastError());
            CloseHandle(port);
            return 5;
        }
        if (bytes_read == 0u) {
            continue;
        }
        for (index = 0u; index < bytes_read; ++index) {
            res_frame_t frame;
            const uint8_t before = parser.length;

            if (!res_stream_parser_push(&parser, input[index], &frame, auth_key)) {
                if ((before != 0u) && (parser.length == 0u)) {
                    ++invalid_bytes;
                }
                continue;
            }
            if ((frame.source != RES_NODE_REMOTE) ||
                (frame.destination != RES_NODE_VEHICLE)) {
                continue;
            }
            ++valid_frames;
            if (remote_session == 0u) {
                remote_session = frame.session;
                printf("Remote session 0x%08lX detected.\n",
                       (unsigned long)remote_session);
            }
            if (frame.type == RES_MSG_HELLO) {
                ++hello_frames;
            } else if (frame.type == RES_MSG_HEARTBEAT) {
                ++heartbeat_frames;
            }
            if ((frame.flags & RES_FLAG_ACK_REQUIRED) != 0u) {
                if (!send_safe_ack(port, &frame, &next_sequence)) {
                    fprintf(stderr, "ACK write failed (Win32 error %lu).\n",
                            (unsigned long)GetLastError());
                    CloseHandle(port);
                    return 6;
                }
                ++acks_sent;
            }
            printf("RX #%u type=%u seq=%lu ch=%u payload=%u; ACKs=%u\n",
                   valid_frames,
                   frame.type,
                   (unsigned long)frame.sequence,
                   frame.channel,
                   frame.payload_length,
                   acks_sent);
        }
    }

    CloseHandle(port);
    printf("SUMMARY valid=%u hello=%u heartbeat=%u acks=%u resync=%u\n",
           valid_frames, hello_frames, heartbeat_frames, acks_sent, invalid_bytes);
    if ((valid_frames >= target_frames) &&
        (hello_frames != 0u) &&
        (heartbeat_frames >= 3u) &&
        (acks_sent >= heartbeat_frames)) {
        puts("PASS: authenticated bidirectional LoRa/UART link established.");
        return 0;
    }
    fputs("FAIL: did not observe HELLO -> ACK -> sustained HEARTBEAT.\n", stderr);
    return 1;
}

#else

#include <stdio.h>

int main(void)
{
    fputs("This hardware harness requires Windows.\n", stderr);
    return 2;
}

#endif
