#include <Arduino.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Error-latch board bench harness, Arduino Nano ATmega328P (5 V / 16 MHz).
//
// D13 EBS_ERROR   output: HEALTHY=5 V, FAULT=0 V
// D12 unused      high impedance; RES_ERROR requires an external 12/0 V source
// D11 R_E_RESET   open-drain output, active low
// D10 BMS_RESET   open-drain output, active low
// D9  IMD_RESET   open-drain output, active low
// D8  SCOUT       input with Nano pull-up
// D7  SCIN        output held at GND
// D6  R_E_LED     high-impedance input
// D5  BMS_LED     high-impedance input
// D4  IMD_LED     high-impedance input
//
// H5 LED outputs are high-side 5 V outputs. Their OFF state can float, so a
// raw LOW reading is conclusive only when each input has an external pulldown
// (about 10 kOhm recommended). Never enable the Nano pull-ups on D4..D6.
//
// The lock-board 12 V and IMD/BMS analog voltages are switched manually.
// Nano startup is safe for an unpowered board: EBS/RES start at FAULT (0 V),
// RESET pins are high impedance, and LED pins are high impedance.

static const uint8_t PIN_IMD_LED = 4;
static const uint8_t PIN_BMS_LED = 5;
static const uint8_t PIN_RE_LED = 6;
static const uint8_t PIN_SCIN = 7;
static const uint8_t PIN_SCOUT = 8;
static const uint8_t PIN_IMD_RESET = 9;
static const uint8_t PIN_BMS_RESET = 10;
static const uint8_t PIN_RE_RESET = 11;
static const uint8_t PIN_UNUSED_D12 = 12;
static const uint8_t PIN_EBS_ERROR = 13;

static char lineBuffer[80];
static uint8_t lineLength = 0;
static bool ebsHealthy = false;

static void uppercase(char *text) {
  if (text == NULL) return;
  while (*text != '\0') {
    *text = (char)toupper(*text);
    ++text;
  }
}

static void releaseReset(uint8_t pin) {
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
}

static void assertReset(uint8_t pin) {
  digitalWrite(pin, LOW);
  pinMode(pin, OUTPUT);
}

static void pulseReset(uint8_t pin, uint16_t durationMs) {
  assertReset(pin);
  delay(durationMs);
  releaseReset(pin);
}

static void pulseAllResets(uint16_t durationMs) {
  assertReset(PIN_IMD_RESET);
  assertReset(PIN_BMS_RESET);
  assertReset(PIN_RE_RESET);
  delay(durationMs);
  releaseReset(PIN_IMD_RESET);
  releaseReset(PIN_BMS_RESET);
  releaseReset(PIN_RE_RESET);
}

static void setErrorInput(uint8_t pin, bool healthy) {
  digitalWrite(pin, healthy ? HIGH : LOW);
  if (pin == PIN_EBS_ERROR) ebsHealthy = healthy;
}

static const __FlashStringHelper *levelName(bool healthy) {
  return healthy ? F("HEALTHY(5V)") : F("FAULT(0V)");
}

static void printStatus() {
  Serial.print(F("EBS="));
  Serial.print(levelName(ebsHealthy));
  Serial.print(F(" RES=EXTERNAL_12V_OR_0V"));
  Serial.print(F(" CONTACT="));
  Serial.print(digitalRead(PIN_SCOUT) == LOW ? F("CLOSED") : F("OPEN"));
  Serial.print(F(" IMD_LED_RAW="));
  Serial.print(digitalRead(PIN_IMD_LED));
  Serial.print(F(" BMS_LED_RAW="));
  Serial.print(digitalRead(PIN_BMS_LED));
  Serial.print(F(" R_E_LED_RAW="));
  Serial.println(digitalRead(PIN_RE_LED));
}

static void printRatio(uint32_t activeSamples, uint32_t totalSamples) {
  uint32_t hundredths = totalSamples == 0
    ? 0
    : (activeSamples * 10000UL) / totalSamples;
  Serial.print(hundredths / 100);
  Serial.print('.');
  if ((hundredths % 100) < 10) Serial.print('0');
  Serial.print(hundredths % 100);
  Serial.print('%');
}

static void measureSignals(uint16_t durationMs) {
  uint32_t contactClosed = 0;
  uint32_t imdHigh = 0;
  uint32_t bmsHigh = 0;
  uint32_t reHigh = 0;
  uint32_t samples = 0;
  uint32_t contactEdges = 0;
  bool previousContact = digitalRead(PIN_SCOUT) == LOW;
  unsigned long start = millis();

  do {
    bool contact = digitalRead(PIN_SCOUT) == LOW;
    if (contact != previousContact) ++contactEdges;
    if (contact) ++contactClosed;
    if (digitalRead(PIN_IMD_LED) == HIGH) ++imdHigh;
    if (digitalRead(PIN_BMS_LED) == HIGH) ++bmsHigh;
    if (digitalRead(PIN_RE_LED) == HIGH) ++reHigh;
    ++samples;
    previousContact = contact;
    delayMicroseconds(100);
  } while ((uint16_t)(millis() - start) < durationMs);

  Serial.print(F("MEASURE ms="));
  Serial.print(durationMs);
  Serial.print(F(" samples="));
  Serial.print(samples);
  Serial.print(F(" CONTACT_closed="));
  printRatio(contactClosed, samples);
  Serial.print(F(" edges="));
  Serial.print(contactEdges);
  Serial.print(F(" IMD_LED_high="));
  printRatio(imdHigh, samples);
  Serial.print(F(" BMS_LED_high="));
  printRatio(bmsHigh, samples);
  Serial.print(F(" R_E_LED_high="));
  printRatio(reHigh, samples);
  Serial.println(F(" (LED OFF requires external pulldowns for certainty)"));
}

static void setSafeState() {
  setErrorInput(PIN_EBS_ERROR, false);
  digitalWrite(PIN_UNUSED_D12, LOW);
  pinMode(PIN_UNUSED_D12, INPUT);
  releaseReset(PIN_IMD_RESET);
  releaseReset(PIN_BMS_RESET);
  releaseReset(PIN_RE_RESET);
}

static void printHelp() {
  Serial.println(F("LOCK bench tester ready."));
  Serial.println(F("Commands:"));
  Serial.println(F("  STATUS"));
  Serial.println(F("  SET EBS HEALTHY|FAULT"));
  Serial.println(F("  RESET IMD|BMS|RE|ALL [20..1000 ms; default 150]"));
  Serial.println(F("  MEASURE 100..10000"));
  Serial.println(F("  SAFE"));
  Serial.println(F("12 V and IMD/BMS voltages are manual; RESET outputs are open-drain."));
}

static bool parseHealthy(const char *value, bool &healthy) {
  if (!strcmp(value, "HEALTHY") || !strcmp(value, "1") || !strcmp(value, "HIGH")) {
    healthy = true;
    return true;
  }
  if (!strcmp(value, "FAULT") || !strcmp(value, "0") || !strcmp(value, "LOW")) {
    healthy = false;
    return true;
  }
  return false;
}

static void handleSet(char *target, char *value) {
  if (target == NULL || value == NULL) {
    Serial.println(F("ERR SET needs target and value"));
    return;
  }
  uppercase(target);
  uppercase(value);

  bool healthy;
  if (!parseHealthy(value, healthy)) {
    Serial.println(F("ERR value must be HEALTHY or FAULT"));
    return;
  }

  if (strcmp(target, "EBS")) {
    Serial.println(F("ERR target must be EBS; RES requires external 12/0 V"));
    return;
  }
  setErrorInput(PIN_EBS_ERROR, healthy);
  Serial.println(F("OK"));
  printStatus();
}

static void handleReset(char *target, char *durationText) {
  if (target == NULL) {
    Serial.println(F("ERR RESET needs IMD, BMS, RE, or ALL"));
    return;
  }
  uppercase(target);

  unsigned long duration = 150;
  if (durationText != NULL) {
    char *end = NULL;
    duration = strtoul(durationText, &end, 10);
    if (*end != '\0' || duration < 20 || duration > 1000) {
      Serial.println(F("ERR reset duration must be 20..1000 ms"));
      return;
    }
  }

  if (!strcmp(target, "IMD")) {
    pulseReset(PIN_IMD_RESET, (uint16_t)duration);
  } else if (!strcmp(target, "BMS")) {
    pulseReset(PIN_BMS_RESET, (uint16_t)duration);
  } else if (!strcmp(target, "RE") || !strcmp(target, "R_E")) {
    pulseReset(PIN_RE_RESET, (uint16_t)duration);
  } else if (!strcmp(target, "ALL")) {
    pulseAllResets((uint16_t)duration);
  } else {
    Serial.println(F("ERR RESET target must be IMD, BMS, RE, or ALL"));
    return;
  }
  Serial.print(F("OK RESET "));
  Serial.print(target);
  Serial.print(' ');
  Serial.print(duration);
  Serial.println(F(" ms"));
  printStatus();
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
    setSafeState();
    Serial.println(F("OK SAFE: EBS=0 V, D12 high-Z; RESET pins released."));
    printStatus();
  } else if (!strcmp(command, "SET")) {
    char *target = strtok(NULL, " \t");
    char *value = strtok(NULL, " \t");
    handleSet(target, value);
  } else if (!strcmp(command, "RESET")) {
    char *target = strtok(NULL, " \t");
    char *durationText = strtok(NULL, " \t");
    handleReset(target, durationText);
  } else if (!strcmp(command, "MEASURE")) {
    char *durationText = strtok(NULL, " \t");
    char *end = NULL;
    unsigned long duration = durationText == NULL
      ? 0
      : strtoul(durationText, &end, 10);
    if (durationText == NULL || *end != '\0' || duration < 100 || duration > 10000) {
      Serial.println(F("ERR MEASURE duration must be 100..10000 ms"));
    } else {
      measureSignals((uint16_t)duration);
    }
  } else {
    Serial.println(F("ERR unknown command; type HELP"));
  }
}

void setup() {
  // LED outputs are high-side drivers; do not add Nano pull-ups.
  digitalWrite(PIN_IMD_LED, LOW);
  digitalWrite(PIN_BMS_LED, LOW);
  digitalWrite(PIN_RE_LED, LOW);
  pinMode(PIN_IMD_LED, INPUT);
  pinMode(PIN_BMS_LED, INPUT);
  pinMode(PIN_RE_LED, INPUT);

  // Use the dry relay contact as a grounded-loop continuity test.
  digitalWrite(PIN_SCIN, LOW);
  pinMode(PIN_SCIN, OUTPUT);
  pinMode(PIN_SCOUT, INPUT_PULLUP);

  // Load FAULT before enabling EBS output to avoid a startup HIGH pulse.
  digitalWrite(PIN_EBS_ERROR, LOW);
  pinMode(PIN_EBS_ERROR, OUTPUT);
  digitalWrite(PIN_UNUSED_D12, LOW);
  pinMode(PIN_UNUSED_D12, INPUT);

  releaseReset(PIN_IMD_RESET);
  releaseReset(PIN_BMS_RESET);
  releaseReset(PIN_RE_RESET);

  Serial.begin(115200);
  delay(100);
  printHelp();
  printStatus();
  Serial.println(F("ACTION: keep board power OFF until wiring has been checked."));
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
