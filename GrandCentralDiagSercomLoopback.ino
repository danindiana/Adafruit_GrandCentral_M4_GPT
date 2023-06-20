#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Uart.h>

Uart Serial1 (&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2); // RX, TX

void SERCOM1_Handler()
{
    Serial1.IrqHandler();
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial1.begin(9600);

  // Assign SERCOM functionality to pins
  pinPeripheral(10, PIO_SERCOM);
  pinPeripheral(11, PIO_SERCOM);

  Serial.println("Press 's' to start the diagnostics.");
  while (Serial.read() != 's');

  performTest("GPIO Pins Test", checkGPIOPins);
  performTest("Analog Pins Test", checkAnalogPins);
  performTest("I2C Test", checkI2C);
  performTest("SPI Test", checkSPI);
  performTest("UART Test", checkUART);
  performTest("SERCOM Test", checkSERCOM);
  performTest("Pin Loopback Test", checkPinLoopback);
}

void loop() {
  // Empty loop. The diagnostics are run once in setup().
}

template<typename TestFunction>
void performTest(const char* testName, TestFunction testFunction) {
  Serial.print("Performing ");
  Serial.println(testName);
  unsigned long startTime = millis();
  testFunction();
  unsigned long elapsedTime = millis() - startTime;
  Serial.print(testName);
  Serial.print(" completed in ");
  Serial.print(elapsedTime);
  Serial.println(" ms");
  Serial.println();
}

void checkGPIOPins() {
  // ...
  // Same as before
  // ...
}

void checkAnalogPins() {
  // ...
  // Same as before
  // ...
}

void checkI2C() {
  // ...
  // Same as before
  // ...
}

void checkSPI() {
  // ...
  // Same as before
  // ...
}

void checkUART() {
  // ...
  // Same as before
  // ...
}

void checkSERCOM() {
  Serial.println("Checking SERCOM using Serial1...");

  const char* testMessage = "SERCOM test message";
  Serial1.println(testMessage);

  delay(100);

  char receivedMessage[50];
  int i = 0;
  while (Serial1.available()) {
    receivedMessage[i++] = Serial1.read();
  }
  receivedMessage[i] = '\0';

  if (strcmp(receivedMessage, testMessage) == 0) {
    Serial.println("SERCOM test passed.");
  } else {
    Serial.println("SERCOM test failed.");
  }
}

void checkPinLoopback() {
  Serial.println("Checking Pin Loopback...");
  
  // Assuming pin 9 is connected to pin 8 for loopback
  pinMode(9, OUTPUT);
  pinMode(8, INPUT);

  digitalWrite(9, HIGH);
  delay(10);
  if (digitalRead(8) == HIGH) {
    Serial.println("Loopback test passed.");
  } else {
    Serial.println("Loopback test failed.");
  }

  digitalWrite(9, LOW);
}
