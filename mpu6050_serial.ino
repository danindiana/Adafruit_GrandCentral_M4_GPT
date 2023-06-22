#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

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

    // Output the values to the Serial port
    Serial.print(a.acceleration.x); Serial.print(",");
    Serial.print(a.acceleration.y); Serial.print(",");
    Serial.print(a.acceleration.z); Serial.print(",");
    Serial.print(g.gyro.x); Serial.print(",");
    Serial.print(g.gyro.y); Serial.print(",");
    Serial.println(g.gyro.z);

    // Short delay before the next reading
    delay(100);
}
