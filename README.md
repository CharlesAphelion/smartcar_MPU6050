# Smartcar MPU6050 library
An extension of the [Smartcar shield](http://plat.is/smartcar) library that uses the MPU6050 6DOF IMU

## Description
This library is an extension to the Smartcar shield library, that allows the integration of the MPU6050 6DOF IMU, with the Smartcar platform. Particularly, the MPU6050 can be used instead of the default gyroscope, in order to allow the smartcar to [rotate](https://github.com/platisd/smartcar_shield/wiki/API-documentation#void-rotateint-degrees) according to the specified degrees.

The library is essentially a stripped down version of the [MPU6050](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050) Arduino library, by Jeff Rowberg. It merely allows the user to get the angularDisplacement, since the beginning of MPU6050's operation. Essentially the sensor's heading. Calibration currently is not supported, so you should try the equivalent sketches of the original library if you need to do get those values. Furtheremore, the library by default uses the YAW value (Z axis) as the displacement, as in the Smartcar domain, we do not care about all the three axes of movement. If you need to use another axis, due to different orientation of your MPU6050, change `ypr[0]` in [/MPU6050_Sensor.cpp](/MPU6050_Sensor.cpp) to `ypr[1]` for pitch (y axis) and `ypr[2]` for roll (x axis).

The original API has become private, for higher clarity. If you need to just use the MPU6050, without the Smartcar, please use the original library!

You can find various example sketches, which illustrate the usage of the MPU6050 sensor, in the [/examples](/examples) folder.

## Dependencies
* Wire library (included with Arduino IDE)
* [Smartcar shield](http://plat.is/smartcar) library

## API
In order to use the library, you have to include the Smartcar_MPU6050.h file, by writing `#include <Smartcar_MPU6050.h>`. If you are using the Arduino IDE 1.6.6 or newer, you don't have to include the Smartcar.h file for the Smartcar shield library, or other dependencies related to these two libraries.

**Note:** When using the MPU6050, keep in mind that the output values are between -180 and 180, unlike the Gyroscope of Smartcar library. So, when using the MPU6050 with `Car`, `rotate(360)` will never be reached.

### MPU6050_Sensor(int gyroOffset, int accelOffset, uint8_t address)
The constructor of the MPU6050_Sensor. Use it to instantiate the MPU6050_Sensor class. The arguments are optional. Gyro offset and accelerometer offset, should be determined using the [original library](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050). The default and most common address is `0x68`. Less often, it can also be `0x69` depending on your module. The default address, is represented by the `MPU6050_DEFAULT_ADDRESS` constant in [MPU6050_Sensor.h](MPU6050_Sensor.h).

**Example**
```arduino
#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;
//MPU6050_Sensor mpu(0, 1758, 0x69);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
```

### boolean attach(unsigned short digitalPin)
Always use this method in `setup()` in order to bind the MPU6050 sensor to an pin enabled with an external interrupt. You can find which ones are those for your board [here](https://www.arduino.cc/en/Reference/AttachInterrupt).

If an invalid digital pin is supplied or connection to the MPU6050 fails, false will be returned. You can use this method's return value to determine if initialization was succesful.

**Example**
```arduino
#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;

void setup() {
  mpu.attach(2); //MPU6050 attached to pin D2
}

void loop() {
  // put your main code here, to run repeatedly:
}
```

### void update()
Always use this method in `loop()` in order to update the measurements from the MPU6050 sensor. This method should be run as frequent as possible.

**Example**
```arduino
#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;

void setup() {
  mpu.attach(2); //MPU6050 attached to pin D2
}

void loop() {
  mpu.update(); //update the MPU6050 readings
}
```

### int getAngularDisplacement()
Use this method in order to get the angular displacement (or heading) at the specific moment. This method is inherited from the [HeadingSensor](https://github.com/platisd/smartcar_shield/blob/master/src/HeadingSensor.cpp) class of the Smartcar shield library.

**Example**
```arduino
#include <Smartcar_MPU6050.h>

MPU6050_Sensor mpu;

void setup() {
  Serial.begin(9600); //initialize serial at 9600 BAUD rate
  mpu.attach(2); //MPU6050 attached to pin D2
}

void loop() {
  mpu.update(); //update the MPU6050 readings
  Serial.println(mpu.getAngularDisplacement()); //print the current displacement
}
```

## Known issues
* Sometimes the MPU6050 readings of `getAngularDisplacement` become random, either being totally unstable or very high (approximately -179). This tends to get corrected if the INT pin gets plugged out and in. As the issue is hard to replicate, the reasons behind it are under investigations.

## Examples
Examples can be found under the [/examples](/tree/master/examples) folder.
* [Smartcar_MPU6050_displacement](/examples/Smartcar_MPU6050_displacement/Smartcar_MPU6050_displacement.ino)
A sketch that illustrates how to get the angular displacement readings from the MPU6050 sensor.
* [Smartcar_MPU6050_Car](/examples/Smartcar_MPU6050_Car/Smartcar_MPU6050_Car.ino)
A sketch that illustrates how to integrate the MPU6050 sensor with the Car class of the Smartcar shield library. Particularly, you can use it the same way with the Gyroscope.
