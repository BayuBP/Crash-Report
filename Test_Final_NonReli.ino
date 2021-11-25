#include <Arduino.h>
#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <MPU6050.h>
#include <SoftwareSerial.h>

SoftwareSerial s(5,6);
MPU6050 mpu;
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int data;
float hori1,veri1,jungkir1;

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  Wire.begin();
  mpu.begin();
    mpu.setAccelOffsetX(-1050);
    mpu.setAccelOffsetY(2999);
    mpu.setAccelOffsetZ(-700);
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers

  mpu.begin();
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

  hori1 = normAccel.XAxis;
  veri1 = normAccel.YAxis;
  jungkir1 = normAccel.ZAxis;
  
  Serial.println("Hasil Baca Sensor 1 : ");
  Serial.print(" X = ");
  Serial.print(hori1);
  Serial.print(" Y = ");
  Serial.println(veri1);
  Serial.print(" Z = ");
  Serial.println(jungkir1);
  
  if (normAccel.XAxis > 8) {
    Serial.println("Status Motor : Miring Kanan");
    data = 1;
    delay(1000);
    }
  else if (normAccel.XAxis < -8) {
    Serial.println("Status Motor : Miring Kiri");
    data = 2;
    delay(1000);
    }
  else {
    Serial.println("Status Motor : Motor Normal");
    data = 0;
    delay(1000);
    }
    Serial.println(data);
      if(s.available()>0) {
        s.print('A' + String((float)hori1) +
                'B' + String((float)veri1) +
                'C' + String((float)jungkir1) +
                'D' + String((int)data));
      }
}
