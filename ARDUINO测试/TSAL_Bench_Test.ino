#include <Arduino.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// TSAL bench harness, Arduino Nano ATmega328P (5 V / 16 MHz).
//
// D13 MAINN#         D12 MAINN_ACTUAL
// D11 MAINP#         D10 MAINP_ACTUAL
// D9  PRE#           D8  PRE_ACTUAL
// D7  V_CONTROLLER   D6  V_BATTERY
// D5  unused, always high impedance
// D3  GREEN_OUT_K    D2  RED_OUT_K (active-low inputs with 5 V pull-ups)
//
// The TSAL 12 V supply is switched manually. Keep it OFF while the Nano
// resets, is uploaded, or while a serial connection is being opened.

enum PairState : uint8_t {
  PAIR_OPEN,
  PAIR_CLOSED,
  PAIR_FAULT_00,
  PAIR_FAULT_11
};

static const uint8_t PIN_RED_K = 2;
static const uint8_t PIN_GREEN_K = 3;
static const uint8_t PIN_LATCH_MONITOR = 4;
static const uint8_t PIN_UNUSED_D5 = 5;
static const uint8_t PIN_V_BATTERY = 6;
static const uint8_t PIN_V_CONTROLLER = 7;

// D8..D13 are PB0..PB5. Each pair is updated in one PORTB write so a
// commanded valid-state transition does not create a software GPIO glitch.
static const uint8_t MASK_PRE = _BV(PB0) | _BV(PB1);
static const uint8_t MASK_MAINP = _BV(PB2) | _BV(PB3);
static const uint8_t MASK_MAINN = _BV(PB4) | _BV(PB5);
static const uint8_t MASK_ALL_PAIRS = MASK_PRE | MASK_MAINP | MASK_MAINN;

static const uint8_t BIT_PRE_ACTUAL = _BV(PB0);
static const uint8_t BIT_PRE_N = _BV(PB1);
static const uint8_t BIT_MAINP_ACTUAL = _BV(PB2);
static const uint8_t BIT_MAINP_N = _BV(PB3);
static const uint8_t BIT_MAINN_ACTUAL = _BV(PB4);
static const uint8_t BIT_MAINN_N = _BV(PB5);

static char lineBuffer[80];
static uint8_t lineLength = 0;
static bool powerCycleRequired = false;

static void uppercase(char *text) {
  if (text == NULL) return;
  while (*text != '\0') {
    *text = (char)toupper(*text);
    ++text;
  }
}

static const char *stateName(PairState state) {
  switch (state) {
    case PAIR_OPEN: return "OPEN";
    case PAIR_CLOSED: return "CLOSED";
    case PAIR_FAULT_00: return "FAULT00";
    case PAIR_FAULT_11: return "FAULT11";
  }
  return "?";
}

static bool parseState(const char *text, PairState &state) {
  if (!strcmp(text, "OPEN")) state = PAIR_OPEN;
  else if (!strcmp(text, "CLOSED")) state = PAIR_CLOSED;
  else if (!strcmp(text, "FAULT00")) state = PAIR_FAULT_00;
  else if (!strcmp(text, "FAULT11")) state = PAIR_FAULT_11;
  else return false;
  return true;
}

static uint8_t pairBits(PairState state, uint8_t actualBit, uint8_t inverseBit) {
  switch (state) {
    case PAIR_OPEN: return inverseBit;                  // ACTUAL=0, #=1
    case PAIR_CLOSED: return actualBit;                 // ACTUAL=1, #=0
    case PAIR_FAULT_00: return 0;
    case PAIR_FAULT_11: return actualBit | inverseBit;
  }
  return 0;
}

static void setPair(uint8_t mask, uint8_t actualBit, uint8_t inverseBit,
                    PairState state) {
  uint8_t next = PORTB;
  next &= (uint8_t)~mask;
  next |= pairBits(state, actualBit, inverseBit);
  PORTB = next;
  if (state == PAIR_FAULT_00 || state == PAIR_FAULT_11) {
    powerCycleRequired = true;
  }
}

static PairState readPair(uint8_t actualBit, uint8_t inverseBit) {
  uint8_t value = PORTB;
  bool actual = (value & actualBit) != 0;
  bool inverse = (value & inverseBit) != 0;
  if (!actual && inverse) return PAIR_OPEN;
  if (actual && !inverse) return PAIR_CLOSED;
  if (!actual && !inverse) return PAIR_FAULT_00;
  return PAIR_FAULT_11;
}

static void setAllPairs(PairState state) {
  uint8_t bits = 0;
  bits |= pairBits(state, BIT_PRE_ACTUAL, BIT_PRE_N);
  bits |= pairBits(state, BIT_MAINP_ACTUAL, BIT_MAINP_N);
  bits |= pairBits(state, BIT_MAINN_ACTUAL, BIT_MAINN_N);
  PORTB = (PORTB & (uint8_t)~MASK_ALL_PAIRS) | bits;
  if (state == PAIR_FAULT_00 || state == PAIR_FAULT_11) {
    powerCycleRequired = true;
  }
}

static void printOutput(const __FlashStringHelper *name, uint8_t pin) {
  Serial.print(name);
  Serial.print('=');
  Serial.print(digitalRead(pin) == LOW ? F("ON") : F("OFF"));
}

static void printStatus() {
  Serial.print(F("PRE="));
  Serial.print(stateName(readPair(BIT_PRE_ACTUAL, BIT_PRE_N)));
  Serial.print(F(" MAINP="));
  Serial.print(stateName(readPair(BIT_MAINP_ACTUAL, BIT_MAINP_N)));
  Serial.print(F(" MAINN="));
  Serial.print(stateName(readPair(BIT_MAINN_ACTUAL, BIT_MAINN_N)));
  Serial.print(F(" VB="));
  Serial.print(digitalRead(PIN_V_BATTERY));
  Serial.print(F(" VC="));
  Serial.print(digitalRead(PIN_V_CONTROLLER));
  Serial.print(' ');
  printOutput(F("RED"), PIN_RED_K);
  Serial.print(' ');
  printOutput(F("GREEN"), PIN_GREEN_K);
  Serial.print(F(" LATCH_NODE="));
  Serial.print(digitalRead(PIN_LATCH_MONITOR));
  Serial.print(F(" POWER_CYCLE_REQUIRED="));
  Serial.println(powerCycleRequired ? F("YES") : F("NO"));
}

static void printRatio(uint32_t lowSamples, uint32_t totalSamples) {
  uint32_t hundredths = totalSamples == 0
    ? 0
    : (lowSamples * 10000UL) / totalSamples;
  Serial.print(hundredths / 100);
  Serial.print('.');
  if ((hundredths % 100) < 10) Serial.print('0');
  Serial.print(hundredths % 100);
  Serial.print('%');
}

static void measureOutputs(uint16_t durationMs) {
  const uint8_t outputMask = _BV(PD2) | _BV(PD3);
  uint8_t previous = PIND & outputMask;
  uint32_t redLow = 0;
  uint32_t greenLow = 0;
  uint32_t samples = 0;
  uint32_t redEdges = 0;
  uint32_t greenEdges = 0;
  unsigned long start = millis();

  do {
    uint8_t current = PIND & outputMask;
    if ((current ^ previous) & _BV(PD2)) ++redEdges;
    if ((current ^ previous) & _BV(PD3)) ++greenEdges;
    if ((current & _BV(PD2)) == 0) ++redLow;
    if ((current & _BV(PD3)) == 0) ++greenLow;
    ++samples;
    previous = current;
    delayMicroseconds(50);
  } while ((uint16_t)(millis() - start) < durationMs);

  Serial.print(F("MEASURE ms="));
  Serial.print(durationMs);
  Serial.print(F(" samples="));
  Serial.print(samples);
  Serial.print(F(" RED_low="));
  printRatio(redLow, samples);
  Serial.print(F(" RED_edges="));
  Serial.print(redEdges);
  Serial.print(F(" GREEN_low="));
  printRatio(greenLow, samples);
  Serial.print(F(" GREEN_edges="));
  Serial.println(greenEdges);
}

static void setSafeSignals() {
  setAllPairs(PAIR_OPEN);
  digitalWrite(PIN_V_BATTERY, LOW);
  digitalWrite(PIN_V_CONTROLLER, LOW);
  powerCycleRequired = false;
}

static void printHelp() {
  Serial.println(F("TSAL bench tester ready; D5 is unused/high-Z."));
  Serial.println(F("Keep TSAL 12 V OFF during Nano reset/upload/serial-open."));
  Serial.println(F("Commands:"));
  Serial.println(F("  STATUS"));
  Serial.println(F("  SET PRE|MAINP|MAINN OPEN|CLOSED|FAULT00|FAULT11"));
  Serial.println(F("  SET ALL OPEN|CLOSED"));
  Serial.println(F("  SET VB|VC 0|1"));
  Serial.println(F("  MEASURE 100..10000   (continuous D2/D3 active-low sampling)"));
  Serial.println(F("  SAFE"));
  Serial.println(F("  POWERCYCLED   (send only after manual 12 V off/on)"));
}

static void handleSet(char *target, char *value) {
  if (target == NULL || value == NULL) {
    Serial.println(F("ERR SET needs target and value"));
    return;
  }
  uppercase(target);
  uppercase(value);

  if (!strcmp(target, "VB") || !strcmp(target, "VC")) {
    if (strcmp(value, "0") && strcmp(value, "1")) {
      Serial.println(F("ERR VB/VC value must be 0 or 1"));
      return;
    }
    uint8_t pin = !strcmp(target, "VB") ? PIN_V_BATTERY : PIN_V_CONTROLLER;
    digitalWrite(pin, value[0] == '1' ? HIGH : LOW);
    Serial.println(F("OK"));
    return;
  }

  PairState state;
  if (!parseState(value, state)) {
    Serial.println(F("ERR state must be OPEN, CLOSED, FAULT00, or FAULT11"));
    return;
  }
  if (!strcmp(target, "ALL")) {
    if (state == PAIR_FAULT_00 || state == PAIR_FAULT_11) {
      Serial.println(F("ERR ALL accepts only OPEN or CLOSED"));
      return;
    }
    setAllPairs(state);
  } else if (!strcmp(target, "PRE")) {
    setPair(MASK_PRE, BIT_PRE_ACTUAL, BIT_PRE_N, state);
  } else if (!strcmp(target, "MAINP")) {
    setPair(MASK_MAINP, BIT_MAINP_ACTUAL, BIT_MAINP_N, state);
  } else if (!strcmp(target, "MAINN")) {
    setPair(MASK_MAINN, BIT_MAINN_ACTUAL, BIT_MAINN_N, state);
  } else {
    Serial.println(F("ERR unknown SET target"));
    return;
  }

  Serial.println(F("OK"));
  if (state == PAIR_FAULT_00 || state == PAIR_FAULT_11) {
    Serial.println(F("NOTICE: fault latch test active; manual 12 V power cycle required before the next normal case."));
  }
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
    setSafeSignals();
    Serial.println(F("OK SAFE; signal defaults restored. This command does not switch 12 V."));
  } else if (!strcmp(command, "SET")) {
    // Do not pass two strtok() calls as function arguments: argument
    // evaluation order is unspecified in the AVR C++11 toolchain.
    char *target = strtok(NULL, " \t");
    char *value = strtok(NULL, " \t");
    handleSet(target, value);
  } else if (!strcmp(command, "MEASURE")) {
    char *durationText = strtok(NULL, " \t");
    char *end = NULL;
    unsigned long duration = durationText == NULL
      ? 0
      : strtoul(durationText, &end, 10);
    if (durationText == NULL || *end != '\0' || duration < 100 || duration > 10000) {
      Serial.println(F("ERR MEASURE duration must be 100..10000 ms"));
    } else {
      measureOutputs((uint16_t)duration);
    }
  } else if (!strcmp(command, "POWERCYCLED")) {
    powerCycleRequired = false;
    Serial.println(F("OK power-cycle flag cleared"));
  } else {
    Serial.println(F("ERR unknown command; type HELP"));
  }
}

void setup() {
  // D5 is deliberately not connected to any relay or load.
  digitalWrite(PIN_UNUSED_D5, LOW);
  pinMode(PIN_UNUSED_D5, INPUT);

  // Optional digital-only latch probe: connect D4 through about 1 kOhm to
  // TSAL net $1N382 (U9 pin 13; same net as U14 pins 6/7).
  // No pull-up is enabled to avoid back-powering the unpowered TSAL board.
  digitalWrite(PIN_LATCH_MONITOR, LOW);
  pinMode(PIN_LATCH_MONITOR, INPUT);

  // H4 outputs are bare low-side MOSFET drains in the TSAL netlist.
  pinMode(PIN_RED_K, INPUT_PULLUP);
  pinMode(PIN_GREEN_K, INPUT_PULLUP);

  digitalWrite(PIN_V_BATTERY, LOW);
  digitalWrite(PIN_V_CONTROLLER, LOW);
  pinMode(PIN_V_BATTERY, OUTPUT);
  pinMode(PIN_V_CONTROLLER, OUTPUT);

  // Load valid OPEN values before enabling D8..D13 as outputs.
  PORTB = (PORTB & (uint8_t)~MASK_ALL_PAIRS)
        | BIT_PRE_N | BIT_MAINP_N | BIT_MAINN_N;
  DDRB |= MASK_ALL_PAIRS;

  Serial.begin(115200);
  delay(100);
  printHelp();
  printStatus();
  Serial.println(F("ACTION: after this READY message, the operator may switch TSAL 12 V ON."));
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
