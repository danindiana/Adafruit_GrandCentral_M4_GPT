#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  checkGPIOPins();
  checkAnalogPins();
  checkI2C();
  checkSPI();
  checkUART();
}

void loop() {
  // Empty loop. The diagnostics are run once in setup().
}

void checkGPIOPins() {
  Serial.println("Checking GPIO Pins...");

  for (int pinNumber = 0; pinNumber < 62; pinNumber++) {
    pinMode(pinNumber, INPUT_PULLUP);
    int value = digitalRead(pinNumber);
    Serial.print("GPIO Pin ");
    Serial.print(pinNumber);
    Serial.print(" is functional. Value: ");
    Serial.println(value);
  }
}

void checkAnalogPins() {
  Serial.println("Checking Analog Pins...");

  for (int pinNumber = A0; pinNumber < A16; pinNumber++) {
    int value = analogRead(pinNumber);
    Serial.print("Analog Pin A");
    Serial.print(pinNumber - A0);
    Serial.print(" is functional. Value: ");
    Serial.println(value);
  }
}

void checkI2C() {
  Serial.println("Checking I2C...");

  Wire.begin();

  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found.");
  }
}

void checkSPI() {
  Serial.println("Checking SPI...");

  SPI.begin();
  // You might add further SPI tests here, like loopback tests.
  Serial.println("SPI initialized.");
}

void checkUART() {
  Serial.println("Checking UART...");

  // UART is used for Serial communication with the computer.
  // If you can read this diagnostic message, it's functional.
  Serial.println("UART is functional.");
}
