#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <MPU6050.h>

SoftwareSerial s(D6,D5);
WiFiClientSecure client;
const char* ssid = "meh";
const char* password = "12345678";
const char* host = "maker.ifttt.com";
const int httpsPort = 443;
int data;
float hori1,veri1,jungkir1;

void setup() {
  s.begin(9600);
  Serial.begin(9600);
  randomSeed( analogRead(A0) ); //randomize random seed value
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
  
}
 
void loop() {
  String url = "/trigger/Kecelakaan/with/key/d33sWynyDeR-GPAfTWDiMT?value1=";
  String nilai = "NilaiX1_";
  s.write("s");
  if (s.available()>0)
  {
    if (s.find('A')) hori1 = s.parseFloat();
    if (s.find('B')) veri1 = s.parseFloat();
    if (s.find('C')) jungkir1 = s.parseFloat();
    if (s.find('D')) data = s.parseInt();
    
    Serial.println(data);
    nilai += hori1;
    nilai += "_Y1_";
    nilai += veri1;
    nilai += "_Z1_";
    nilai += jungkir1;
    Serial.println(nilai);
    url += nilai;
    url += "&value2=";
    if (data==1) {
      Serial.println("Kanan");
      url += "Kanan";
      } else if (data==2) {
      Serial.println("Kiri");
      url += "Kiri";
      } else {
        data = 0;
        Serial.println("Normal");
        }
  if (data > 0) {
    client.setInsecure();
    Serial.print("Connecting to ");
    Serial.println(host);
    if (!client.connect(host, httpsPort)) {
      Serial.println("Connection failed");
      return;
      }
      
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("request sent");
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers received");
        break;
      }
    }
    String line = client.readStringUntil('\n');

    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
    Serial.println("closing connection");
    delay (5000);
    Serial.println("Mulai Dari Awal");
      }
  }
 
 
}
