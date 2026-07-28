#include <Arduino.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// USB serial uses D0/D1, so this tester intentionally never reconfigures them.
// D2-D13 and A0-A5 can be used as digital GPIO. A6/A7 are analog-input only.

static char lineBuffer[64];
static uint8_t lineLength = 0;

static bool parsePin(const char *text, uint8_t &pin) {
  if (text == NULL || *text == '\0') return false;

  if (toupper(text[0]) == 'A') {
    char *end = NULL;
    long analogIndex = strtol(text + 1, &end, 10);
    if (*end != '\0' || analogIndex < 0 || analogIndex > 7) return false;
    pin = (uint8_t)(A0 + analogIndex);
    return true;
  }

  const char *numberText = text;
  if (toupper(text[0]) == 'D') {
    numberText = text + 1;
    if (*numberText == '\0') return false;
  }

  char *end = NULL;
  long value = strtol(numberText, &end, 10);
  if (*end != '\0' || value < 0 || value > 21) return false;
  pin = (uint8_t)value;
  return true;
}

static bool isSerialPin(uint8_t pin) {
  return pin == 0 || pin == 1;
}

static bool isDigitalPin(uint8_t pin) {
  return pin >= 2 && pin <= 19;
}

static bool isAnalogPin(uint8_t pin) {
  return pin >= A0 && pin <= A7;
}

static bool isPwmPin(uint8_t pin) {
  return pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11;
}

static void printPin(uint8_t pin) {
  if (pin >= A0 && pin <= A7) {
    Serial.print('A');
    Serial.print(pin - A0);
  } else {
    Serial.print(pin);
  }
}

static void makeSafe(uint8_t pin) {
  if (isDigitalPin(pin)) {
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
  }
}

static void printHelp() {
  Serial.println(F("Nano GPIO tester ready (ATmega328P, 5 V logic)"));
  Serial.println(F("Commands:"));
  Serial.println(F("  LIST"));
  Serial.println(F("  MODE <D2..D13|A0..A5> IN|PULLUP|OUT"));
  Serial.println(F("  WRITE <pin> 0|1"));
  Serial.println(F("  READ <D2..D13|A0..A7>"));
  Serial.println(F("  AREAD <A0..A7>"));
  Serial.println(F("  PWM <D3|D5|D6|D9|D10|D11> <0..255>"));
  Serial.println(F("  PAIR <output> <input>   (connect the two pins first)"));
  Serial.println(F("  SAFE                       (all test pins high-Z)"));
  Serial.println(F("D0/D1 are reserved for USB serial; A6/A7 are analog-only."));
}

static void listPins() {
  Serial.println(F("Digital: D2-D13, A0-A5 (D3,D5,D6,D9,D10,D11 PWM)"));
  Serial.println(F("Analog:  A0-A7 (10-bit ADC, nominal range 0..5 V)"));
}

static void safeAll() {
  for (uint8_t pin = 2; pin <= 19; ++pin) makeSafe(pin);
  Serial.println(F("OK SAFE"));
}

static void reportDigital(uint8_t pin) {
  printPin(pin);
  Serial.print('=');
  Serial.println(digitalRead(pin));
}

static void handleCommand(char *line) {
  char *command = strtok(line, " \t");
  if (command == NULL) return;
  for (char *p = command; *p; ++p) *p = (char)toupper(*p);

  if (!strcmp(command, "HELP") || !strcmp(command, "?")) {
    printHelp();
    return;
  }
  if (!strcmp(command, "LIST")) {
    listPins();
    return;
  }
  if (!strcmp(command, "SAFE")) {
    safeAll();
    return;
  }

  char *pinText = strtok(NULL, " \t");
  uint8_t pin = 0;
  if (!parsePin(pinText, pin) || isSerialPin(pin)) {
    Serial.println(F("ERR invalid/reserved pin"));
    return;
  }

  if (!strcmp(command, "READ")) {
    if (!isDigitalPin(pin)) {
      Serial.println(F("ERR A6/A7 are analog-only"));
      return;
    }
    reportDigital(pin);
    return;
  }

  if (!strcmp(command, "AREAD")) {
    if (!isAnalogPin(pin)) {
      Serial.println(F("ERR use A0..A7"));
      return;
    }
    printPin(pin);
    Serial.print('=');
    Serial.println(analogRead(pin));
    return;
  }

  if (!strcmp(command, "MODE")) {
    if (!isDigitalPin(pin)) {
      Serial.println(F("ERR A6/A7 are analog-only"));
      return;
    }
    char *mode = strtok(NULL, " \t");
    if (mode == NULL) {
      Serial.println(F("ERR missing mode"));
      return;
    }
    for (char *p = mode; *p; ++p) *p = (char)toupper(*p);
    if (!strcmp(mode, "IN")) {
      pinMode(pin, INPUT);
    } else if (!strcmp(mode, "PULLUP")) {
      pinMode(pin, INPUT_PULLUP);
    } else if (!strcmp(mode, "OUT")) {
      digitalWrite(pin, LOW);
      pinMode(pin, OUTPUT);
    } else {
      Serial.println(F("ERR mode must be IN, PULLUP, or OUT"));
      return;
    }
    Serial.println(F("OK"));
    return;
  }

  if (!strcmp(command, "WRITE")) {
    if (!isDigitalPin(pin)) {
      Serial.println(F("ERR A6/A7 are analog-only"));
      return;
    }
    char *valueText = strtok(NULL, " \t");
    if (valueText == NULL || (strcmp(valueText, "0") && strcmp(valueText, "1"))) {
      Serial.println(F("ERR value must be 0 or 1"));
      return;
    }
    digitalWrite(pin, valueText[0] == '1' ? HIGH : LOW);
    Serial.println(F("OK"));
    return;
  }

  if (!strcmp(command, "PWM")) {
    char *valueText = strtok(NULL, " \t");
    char *end = NULL;
    long value = valueText == NULL ? -1 : strtol(valueText, &end, 10);
    if (!isPwmPin(pin) || valueText == NULL || *end != '\0' || value < 0 || value > 255) {
      Serial.println(F("ERR PWM pin/value"));
      return;
    }
    pinMode(pin, OUTPUT);
    analogWrite(pin, (uint8_t)value);
    Serial.println(F("OK"));
    return;
  }

  if (!strcmp(command, "PAIR")) {
    char *inputText = strtok(NULL, " \t");
    uint8_t inputPin = 0;
    if (!isDigitalPin(pin) || !parsePin(inputText, inputPin) || !isDigitalPin(inputPin) || pin == inputPin) {
      Serial.println(F("ERR PAIR needs two different digital test pins"));
      return;
    }

    pinMode(inputPin, INPUT_PULLUP);
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);
    delay(5);
    bool lowOk = digitalRead(inputPin) == LOW;
    digitalWrite(pin, HIGH);
    delay(5);
    bool highOk = digitalRead(inputPin) == HIGH;
    makeSafe(pin);
    makeSafe(inputPin);

    Serial.print(F("PAIR "));
    printPin(pin);
    Serial.print(F("->"));
    printPin(inputPin);
    Serial.println(lowOk && highOk ? F(" PASS") : F(" FAIL"));
    return;
  }

  Serial.println(F("ERR unknown command; type HELP"));
}

void setup() {
  for (uint8_t pin = 2; pin <= 19; ++pin) makeSafe(pin);
  Serial.begin(115200);
  delay(50);
  printHelp();
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
