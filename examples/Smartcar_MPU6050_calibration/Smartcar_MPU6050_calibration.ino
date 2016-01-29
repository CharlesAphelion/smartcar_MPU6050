#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;
boolean setupSuccess = false;

void setup() {
  Serial.begin(9600);
  setupSuccess = mpu.calibrate();
  if (!setupSuccess) {
    Serial.println("There was an error during setup");
  } else {
    Serial.println("Connection established");
  }
  Serial.print("Gyro offset: ");
  Serial.println(mpu.calibrateGyroscope());
  Serial.println("Accell offset: ");
  Serial.println(mpu.calibrateAccelerometer());
}

void loop() {
}
