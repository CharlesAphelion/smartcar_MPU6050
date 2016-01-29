#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;
boolean setupSuccess = false;

void setup() {
  Serial.begin(9600);
  setupSuccess = mpu.attach(2);
  if (!setupSuccess) {
    Serial.println("There was an error during setup");
  } else {
    Serial.println("Connection established");
  }
}

void loop() {
  if (!setupSuccess) return; //if there was an error, don't do anything
  mpu.update();
  Serial.println(mpu.getAngularDisplacement());
}
