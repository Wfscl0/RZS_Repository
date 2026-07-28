#include <Arduino.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// BSPD digital-input bench harness, Arduino Nano ATmega328P (5 V / 16 MHz).
// D2 OIL1, D3 OIL2, D4 OIL3, D5 OIL4, D6 CURRENT: push-pull 0/5 V.
// D7 SC_IN: held at 0 V. D8 SC_OUT: INPUT_PULLUP continuity input.
// Startup is safe for an unpowered BSPD: all analog substitutes start at 0 V.

static const uint8_t SIGNAL_PINS[] = {2, 3, 4, 5, 6};
static const char *const SIGNAL_NAMES[] = {"OIL1", "OIL2", "OIL3", "OIL4", "CURRENT"};
static const uint8_t SIGNAL_COUNT = sizeof(SIGNAL_PINS) / sizeof(SIGNAL_PINS[0]);
static const uint8_t PIN_SCIN = 7;
static const uint8_t PIN_SCOUT = 8;

static char lineBuffer[80];
static uint8_t lineLength = 0;
static bool levels[SIGNAL_COUNT] = {false, false, false, false, false};

static void uppercase(char *value) {
  while (value != NULL && *value != '\0') {
    *value = (char)toupper(*value);
    ++value;
  }
}

static int8_t signalIndex(const char *name) {
  for (uint8_t i = 0; i < SIGNAL_COUNT; ++i) {
    if (!strcmp(name, SIGNAL_NAMES[i])) return (int8_t)i;
  }
  return -1;
}

static bool parseLevel(const char *value, bool &high) {
  if (!strcmp(value, "HIGH") || !strcmp(value, "ON") || !strcmp(value, "1")) {
    high = true;
    return true;
  }
  if (!strcmp(value, "LOW") || !strcmp(value, "OFF") || !strcmp(value, "0")) {
    high = false;
    return true;
  }
  return false;
}

static void setSignal(uint8_t index, bool high) {
  digitalWrite(SIGNAL_PINS[index], high ? HIGH : LOW);
  levels[index] = high;
}

static void setAll(bool high) {
  for (uint8_t i = 0; i < SIGNAL_COUNT; ++i) setSignal(i, high);
}

static bool contactClosed() {
  return digitalRead(PIN_SCOUT) == LOW;
}

static void printStatus() {
  for (uint8_t i = 0; i < SIGNAL_COUNT; ++i) {
    if (i != 0) Serial.print(' ');
    Serial.print(SIGNAL_NAMES[i]);
    Serial.print('=');
    Serial.print(levels[i] ? F("5V") : F("0V"));
  }
  Serial.print(F(" CONTACT="));
  Serial.println(contactClosed() ? F("CLOSED") : F("OPEN"));
}

static void measureContact(uint16_t durationMs) {
  const unsigned long start = millis();
  bool previous = contactClosed();
  uint32_t samples = 0;
  uint32_t closedSamples = 0;
  uint16_t edges = 0;
  long firstEdgeMs = -1;

  do {
    bool current = contactClosed();
    if (current) ++closedSamples;
    if (current != previous) {
      ++edges;
      if (firstEdgeMs < 0) firstEdgeMs = (long)(millis() - start);
      previous = current;
    }
    ++samples;
    delayMicroseconds(100);
  } while ((uint16_t)(millis() - start) < durationMs);

  Serial.print(F("MEASURE ms="));
  Serial.print(durationMs);
  Serial.print(F(" samples="));
  Serial.print(samples);
  Serial.print(F(" closed="));
  Serial.print(samples == 0 ? 0 : (closedSamples * 100UL) / samples);
  Serial.print(F("% edges="));
  Serial.print(edges);
  Serial.print(F(" first_edge_ms="));
  if (firstEdgeMs < 0) Serial.print(F("NONE")); else Serial.print(firstEdgeMs);
  Serial.print(F(" final="));
  Serial.println(previous ? F("CLOSED") : F("OPEN"));
}

static void printHelp() {
  Serial.println(F("BSPD bench tester ready."));
  Serial.println(F("Commands:"));
  Serial.println(F("  STATUS"));
  Serial.println(F("  SET OIL1|OIL2|OIL3|OIL4|CURRENT HIGH|LOW"));
  Serial.println(F("  SET ALL HIGH|LOW"));
  Serial.println(F("  MEASURE 100..30000"));
  Serial.println(F("  SAFE"));
}

static void handleCommand(char *line) {
  char *command = strtok(line, " \t");
  if (command == NULL) return;
  uppercase(command);

  if (!strcmp(command, "HELP") || !strcmp(command, "?")) {
    printHelp();
  } else if (!strcmp(command, "STATUS")) {
    printStatus();
  } else if (!strcmp(command, "SAFE")) {
    setAll(false);
    Serial.println(F("OK SAFE: OIL1..4=0V CURRENT=0V"));
    printStatus();
  } else if (!strcmp(command, "SET")) {
    char *target = strtok(NULL, " \t");
    char *value = strtok(NULL, " \t");
    if (target == NULL || value == NULL) {
      Serial.println(F("ERR SET needs target and level"));
      return;
    }
    uppercase(target);
    uppercase(value);
    bool high;
    if (!parseLevel(value, high)) {
      Serial.println(F("ERR level must be HIGH or LOW"));
      return;
    }
    if (!strcmp(target, "ALL")) {
      setAll(high);
    } else {
      int8_t index = signalIndex(target);
      if (index < 0) {
        Serial.println(F("ERR target must be OIL1..OIL4, CURRENT, or ALL"));
        return;
      }
      setSignal((uint8_t)index, high);
    }
    Serial.println(F("OK"));
    printStatus();
  } else if (!strcmp(command, "MEASURE")) {
    char *durationText = strtok(NULL, " \t");
    char *end = NULL;
    unsigned long duration = durationText == NULL ? 0 : strtoul(durationText, &end, 10);
    if (durationText == NULL || *end != '\0' || duration < 100 || duration > 30000) {
      Serial.println(F("ERR MEASURE duration must be 100..30000 ms"));
      return;
    }
    measureContact((uint16_t)duration);
  } else {
    Serial.println(F("ERR unknown command; type HELP"));
  }
}

void setup() {
  for (uint8_t i = 0; i < SIGNAL_COUNT; ++i) {
    digitalWrite(SIGNAL_PINS[i], LOW);
    pinMode(SIGNAL_PINS[i], OUTPUT);
  }
  digitalWrite(PIN_SCIN, LOW);
  pinMode(PIN_SCIN, OUTPUT);
  pinMode(PIN_SCOUT, INPUT_PULLUP);

  Serial.begin(115200);
  delay(100);
  printHelp();
  printStatus();
  Serial.println(F("ACTION: keep BSPD 24V power OFF until wiring is checked."));
}

void loop() {
  while (Serial.available() > 0) {
    char ch = (char)Serial.read();
    if (ch == '\r' || ch == '\n') {
      if (lineLength > 0) {
        lineBuffer[lineLength] = '\0';
        handleCommand(lineBuffer);
        lineLength = 0;
      }
    } else if (lineLength < sizeof(lineBuffer) - 1) {
      lineBuffer[lineLength++] = ch;
    } else {
      lineLength = 0;
      Serial.println(F("ERR command too long"));
    }
  }
}
