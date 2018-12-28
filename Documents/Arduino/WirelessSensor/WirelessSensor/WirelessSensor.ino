#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

char auth[] = "2fa8e0076d4e4d79add6a9ab2f7b18ae"; // Blynk Token
char ssid[] = "CowboyBeepBoop"; // Wireless Network
char pass[] = "GARYoldman!"; // Wifi Password

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

BlynkTimer timer;

Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void sendSensor() {

}

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  Blynk.begin(auth, ssid, pass);

  if (!bme.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {

  Blynk.run();
  timer.run();

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C / ");
  Serial.print((9 * bme.readTemperature() / 5) + 32);
  Serial.println(" *F / ");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure());
  Serial.println(" Pa");

  Serial.print("Approx altitude = ");
  Serial.print(bme.readAltitude(1030.00)); // this should be adjusted to your local forcase
  Serial.println(" m / ");
  Serial.print((bme.readAltitude(1030.00) * 3.28 )); // this should be adjusted to your local forcase
  Serial.println(" ft");

  Serial.println();
  delay(2000);

  Blynk.virtualWrite(V4, int(bme.readAltitude(1030.00)));
  Blynk.virtualWrite(V5, int((bme.readAltitude(1030.00) * 3.28 )));
  Blynk.virtualWrite(V6, int(bme.readTemperature()));
  Blynk.virtualWrite(V7, int((9 * bme.readTemperature() / 5) + 32));
  //  Blynk.virtualWrite(V0, 16);
}
