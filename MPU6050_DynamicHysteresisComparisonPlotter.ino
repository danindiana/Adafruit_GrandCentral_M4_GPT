#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

float lastAccelX = 0, lastAccelY = 0, lastAccelZ = 0;
float lastGyroX = 0, lastGyroY = 0, lastGyroZ = 0;
float hysteresisThreshold = 0.1;
unsigned long hysteresisTime = 0;
unsigned long noHysteresisTime = 0;
unsigned long startTime = 0;
bool useHysteresis = true;

void setup() {
    Wire.begin();
    Serial.begin(115200);

    // Initialize the MPU6050
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Serial.println("MPU6050 connection successful");

    // Prompt user to set hysteresis threshold
    Serial.println("Enter the hysteresis threshold (e.g., 0.1):");
    while (!Serial.available()) {}
    hysteresisThreshold = Serial.parseFloat();
    Serial.print("Hysteresis threshold set to: ");
    Serial.println(hysteresisThreshold);

    // Prompt user to set time with hysteresis (in milliseconds)
    Serial.println("Enter the length of time to observe with hysteresis (in milliseconds):");
    while (!Serial.available()) {}
    hysteresisTime = Serial.parseInt();
    Serial.print("Time with hysteresis set to: ");
    Serial.println(hysteresisTime);

    // Prompt user to set time without hysteresis (in milliseconds)
    Serial.println("Enter the length of time to observe without hysteresis (in milliseconds):");
    while (!Serial.available()) {}
    noHysteresisTime = Serial.parseInt();
    Serial.print("Time without hysteresis set to: ");
    Serial.println(noHysteresisTime);

    startTime = millis();
}

void loop() {
    mpu.getEvent(&a, &g, &temp);

    unsigned long currentTime = millis();

    if (useHysteresis) {
        // Hysteresis smoothing
        if (abs(a.acceleration.x - lastAccelX) > hysteresisThreshold) {
            lastAccelX = a.acceleration.x;
        }
        if (abs(a.acceleration.y - lastAccelY) > hysteresisThreshold) {
            lastAccelY = a.acceleration.y;
        }
        if (abs(a.acceleration.z - lastAccelZ) > hysteresisThreshold) {
            lastAccelZ = a.acceleration.z;
        }
        if (abs(g.gyro.x - lastGyroX) > hysteresisThreshold) {
            lastGyroX = g.gyro.x;
        }
        if (abs(g.gyro.y - lastGyroY) > hysteresisThreshold) {
            lastGyroY = g.gyro.y;
        }
        if (abs(g.gyro.z - lastGyroZ) > hysteresisThreshold) {
            lastGyroZ = g.gyro.z;
        }

        if (currentTime - startTime >= hysteresisTime) {
            useHysteresis = false;
            startTime = currentTime;
        }
    } else {
        // Without Hysteresis smoothing
        lastAccelX = a.acceleration.x;
        lastAccelY = a.acceleration.y;
        lastAccelZ = a.acceleration.z;
        lastGyroX = g.gyro.x;
        lastGyroY = g.gyro.y;
        lastGyroZ = g.gyro.z;

        if (currentTime - startTime >= noHysteresisTime) {
            useHysteresis = true;
            startTime = currentTime;
        }
    }

    // Output the values to the Serial port
    Serial.print(lastAccelX); Serial.print(",");
    Serial.print(lastAccelY); Serial.print(",");
    Serial.print(lastAccelZ); Serial.print(",");
    Serial.print(lastGyroX); Serial.print(",");
    Serial.print(lastGyroY); Serial.print(",");
    Serial.println(lastGyroZ);

    // Short delay before the next reading
    delay(1000);
}
