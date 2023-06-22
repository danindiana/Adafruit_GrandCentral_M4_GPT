#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

bool sampleAccelX = false, sampleAccelY = false, sampleAccelZ = false;
bool sampleGyroX = false, sampleGyroY = false, sampleGyroZ = false;

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

    // Prompt user for axes to sample
    Serial.println("Enter axes to sample as a sequence of characters (e.g., 'axyz' for accel x and gyro yz):");
    Serial.println("a - accelerometer");
    Serial.println("g - gyroscope");
    Serial.println("xyz - x, y, and z axes");

    while (!Serial.available()) {
        // Wait for user input
    }
    
    String input = Serial.readString();

    if (input.indexOf('x') >= 0) {
        sampleAccelX = input.indexOf('a') >= 0;
        sampleGyroX = input.indexOf('g') >= 0;
    }
    if (input.indexOf('y') >= 0) {
        sampleAccelY = input.indexOf('a') >= 0;
        sampleGyroY = input.indexOf('g') >= 0;
    }
    if (input.indexOf('z') >= 0) {
        sampleAccelZ = input.indexOf('a') >= 0;
        sampleGyroZ = input.indexOf('g') >= 0;
    }
}

void loop() {
    mpu.getEvent(&a, &g, &temp);

    // Output the selected values to the Serial port
    if (sampleAccelX) { Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" ");}
    if (sampleAccelY) { Serial.print("Accel Y: "); Serial.print(a.acceleration.y); Serial.print(" ");}
    if (sampleAccelZ) { Serial.print("Accel Z: "); Serial.print(a.acceleration.z); Serial.print(" ");}
    if (sampleGyroX) { Serial.print("Gyro X: "); Serial.print(g.gyro.x); Serial.print(" ");}
    if (sampleGyroY) { Serial.print("Gyro Y: "); Serial.print(g.gyro.y); Serial.print(" ");}
    if (sampleGyroZ) { Serial.print("Gyro Z: "); Serial.print(g.gyro.z); Serial.print(" ");}

    Serial.println();

    // Short delay before the next reading
    delay(100);
}
