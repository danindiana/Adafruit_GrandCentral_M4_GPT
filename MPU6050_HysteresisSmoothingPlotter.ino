#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

float lastAccelX = 0, lastAccelY = 0, lastAccelZ = 0;
float lastGyroX = 0, lastGyroY = 0, lastGyroZ = 0;
float hysteresisThreshold = 0.1;

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
}

void loop() {
    mpu.getEvent(&a, &g, &temp);

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

    // Output the values to the Serial port
    Serial.print(lastAccelX); Serial.print(",");
    Serial.print(lastAccelY); Serial.print(",");
    Serial.print(lastAccelZ); Serial.print(",");
    Serial.print(lastGyroX); Serial.print(",");
    Serial.print(lastGyroY); Serial.print(",");
    Serial.println(lastGyroZ);

    // Short delay before the next reading
    delay(100);
}
