#include <Arduino.h>
#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <MPU6050.h>
#include <SoftwareSerial.h>

SoftwareSerial s(5,6);
MPU6050 mpu;
int r, l, f, b, up;
int data;
float hori1,veri1,jungkir1;
float hori2,veri2,jungkir2;
float hori3,veri3,jungkir3;
void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  Wire.begin();
  TCA9548A(0);
  mpu.begin();
   mpu.setAccelOffsetX(1375);
   mpu.setAccelOffsetY(1850);
   mpu.setAccelOffsetZ(-300);
  TCA9548A(1);
  mpu.begin();
   mpu.setAccelOffsetX(-2800);
   mpu.setAccelOffsetY(-1300);
   mpu.setAccelOffsetZ(-850);
  TCA9548A(2);
  mpu.begin();
   mpu.setAccelOffsetX(-2050);
   mpu.setAccelOffsetY(1825);
   mpu.setAccelOffsetZ(-625);
}

void loop() {
  r=0;
  l=0;
  f=0;
  b=0;
  up=0;
  
  TCA9548A(0);    // select I2C bus 7 for the BMP180
  if (mpu.begin()) {
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

  Serial.println("Hasil Baca Sensor 1 : ");
  hori1 = normAccel.XAxis;
  veri1 = normAccel.YAxis;
  jungkir1 = normAccel.ZAxis;
  Serial.print(" X 1 = ");
  Serial.print(hori1);
  Serial.print(" Y 1 = ");
  Serial.println(veri1);
  Serial.print(" Z 1 = ");
  Serial.println(jungkir1);
//  if(s.available()>0) {
//        s.print('A' + String((float)hori1) +
//                'B' + String((float)veri1) +
//                'C' + String((float)jungkir1));
//      }
  if (normAccel.XAxis > 8) {
    r = r+1;
    Serial.print("Status Motor : Miring Kanan, ");
    Serial.print("Nilai R :");
    Serial.println(r);
    }
  else if (normAccel.XAxis < -8) {
    l = l+1;
    Serial.print("Status Motor : Miring Kiri, ");
    Serial.print("Nilai L :");
    Serial.println(l);
    }
  }
  else {
    Serial.println("Sensor 1 Rusak");
    }
  
  TCA9548A(1); // select I2C bus 0 for the OLED
  if (mpu.begin()) {
  Vector rawAccel1 = mpu.readRawAccel();
  Vector normAccel1 = mpu.readNormalizeAccel();
  
  hori2 = normAccel1.XAxis;
  veri2 = normAccel1.YAxis;
  jungkir2 = normAccel1.ZAxis;
  Serial.println("Hasil Baca Sensor 2 : ");
  Serial.print(" X 2 = ");
  Serial.print(normAccel1.XAxis);
  Serial.print(" Y 2 = ");
  Serial.println(normAccel1.YAxis);
  Serial.print(" Z 2 = ");
  Serial.println(normAccel1.ZAxis);
//  if(s.available()>0) {
//        s.print('D' + String((float)hori2) +
//                'E' + String((float)veri2) +
//                'F' + String((float)jungkir2));
//      }
  
  if (normAccel1.XAxis > 8) {
    r = r+1;
    Serial.print("Status Motor : Miring Kanan, ");
    Serial.print("Nilai R :");
    Serial.println(r);
    }
  else if (normAccel1.XAxis < -8) {
    l = l+1;
    Serial.print("Status Motor : Miring Kiri, ");
    Serial.print("Nilai L :");
    Serial.println(l);
    }
  }
  else {
    Serial.println("Sensor 2 Rusak");
    }
    
  // next, display the temperature on the OLED
  TCA9548A(2); // select I2C bus 0 for the OLED
  if (mpu.begin()) {
  Vector rawAccel2 = mpu.readRawAccel();
  Vector normAccel2 = mpu.readNormalizeAccel();

  hori2 = normAccel2.XAxis;
  veri2 = normAccel2.YAxis;
  jungkir2 = normAccel2.ZAxis;
  Serial.println("Hasil Baca Sensor 3 : ");
  Serial.print(" X 3 = ");
  Serial.print(normAccel2.XAxis);
  Serial.print(" Y 3 = ");
  Serial.println(normAccel2.YAxis);
  Serial.print(" Z 3 = ");
  Serial.println(normAccel2.ZAxis);
//  if(s.available()>0) {
//        s.print('G' + String((float)hori2) +
//                'H' + String((float)veri2) +
//                'I' + String((float)jungkir2));
//      }
  
  if (normAccel2.XAxis > 8) {
    r = r+1;
    Serial.print("Status Motor : Miring Kanan, ");
    Serial.print("Nilai R :");
    Serial.println(r);
    }
  else if (normAccel2.XAxis < -8) {
    l = l+1;
    Serial.print("Status Motor : Miring Kiri, ");
    Serial.print("Nilai L :");
    Serial.println(l);
    }
  }
  else {
    Serial.println("Sensor 3 Rusak");
    }
  if (r>1) {
    Serial.println("Motor Miring Kanan");
    data = 1;
    delay(5000);
    }
  else if (l>1) {
    Serial.println("Motor Miring Kiri");
    data = 2;
    delay(5000);
    }
  else {
    Serial.println("Motor Berjalan Normal");
    data = 0;
    }
      if(s.available()>0) {
        Serial.println(data);
        s.print('A' + String((float)hori1) +
                'B' + String((float)veri1) +
                'C' + String((float)jungkir1) +
                'D' + String((float)hori2) +
                'E' + String((float)veri2) +
                'F' + String((float)jungkir2) +
                'G' + String((float)hori2) +
                'H' + String((float)veri2) +
                'I' + String((float)jungkir2) +
                'J' + String((int)data));
      }
}
