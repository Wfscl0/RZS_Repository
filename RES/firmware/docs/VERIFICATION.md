# Mandatory bench and HIL verification

Do not connect the relay contacts into the vehicle shutdown circuit until every
item below has a recorded result.

1. Measure PB10/PB11 and relay contacts during power rise, NRST, watchdog reset,
   brownout and firmware download. Both relays must be open during reset.
2. Verify the purchased relay module polarity and add 4.7--10 kOhm pull-ups to
   inactive. Confirm R1-only with receiver powered and remote absent.
3. Press E-stop at every system state. Record RF-to-contact-open latency and
   verify both relays open. Repeat with each antenna removed and E220 power cut.
4. Break the remote NC E-stop detector wire and remove detector-module power;
   both must behave exactly like E-stop.
5. Jam/block each hop channel separately, then two channels. Capture bridge scan,
   reacquisition and the receiver's 500 ms timeout behavior.
6. Replay captured frames, corrupt CRC/tag/sequence/session and inject malformed
   UART lengths. None may create GO or close a latched receiver.
7. Disconnect CAN-H, CAN-L and transceiver power. Verify VCU asserts RES_ERROR on
   150 ms status timeout and the hardware circuit reaches the safe state.
8. Force FDCAN bus-off and TX FIFO saturation. Verify no stale GO event is acted
   upon and VCU supervision remains fail-safe.
9. Measure INA226 thresholds with a programmable supply. Sensor failure keeps the
   handheld non-running during its 500 ms startup grace and then latches STOP.
10. Perform the 1500 m obstructed-site range test with both operators moving,
    worst-case antenna orientation, low battery and nearby transmitters. Record
    RSSI/link loss, stop latency and packet error rate for each channel.

Finally inspect both programmed STM8 images and confirm the same three-frequency
table, air-rate index 4 and blocking TX-completion mode. A single unmodified E220
bridge disables real hopping.
