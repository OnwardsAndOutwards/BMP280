#define BLYNK_PRINT Serial  // For communicating with Blynk android app via the cloud
#include <SPI.h>  // Arduino Serial Peripheral Interface
#include <DHT.h>  // DHT Temperature / Humidity Sensor
#include <BlynkSimpleEsp8266.h>  // Onboard ESP control for da internetz


char auth[] = "2fa8e0076d4e4d79add6a9ab2f7b18ae"; // Blynk Token
char ssid[] = "CowboyBeepBoop"; // Wireless Network
char pass[] = "GARYoldman!"; // Wifi Password


#define DHTPIN 4

//#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT21   // DHT 21, AM2301
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature() if you ain't using `murican
  float tf = dht.readTemperature(true);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, tf);
  Blynk.virtualWrite(V0, 16);
}

void setup()
{

  Serial.begin(9600);  // Debug console via serial monitor

  //  Blynk.begin(auth);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

  float h = dht.readHumidity();

  delay(1000);

}
