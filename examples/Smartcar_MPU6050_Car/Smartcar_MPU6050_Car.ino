#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;

Car car;

void setup() {
  Serial.begin(9600);
  mpu.attach(2);
  car.begin(mpu);
  delay(13000); //wait for the MPU6050 to get ready
  car.rotate(90); //turn 90 degrees to the right
}

void loop() {
  mpu.update();
}
