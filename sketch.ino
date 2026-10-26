#include <WiFi.h>
#include <HTTPClient.h>
#include <DHTesp.h>

// Student Information
const char* universityID = "12217938";

// WiFi Configuration
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingSpeak Configuration
const char* server = "http://api.thingspeak.com/update";
const char* apiKey="DJIZ056RHZG6S10U";

// DHT22 Sensor
#define DHT_PIN 15
DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  Serial.println("ESP32 ThingSpeak IoT Lab");
  Serial.print("University ID: ");
  Serial.println(universityID);

  // Connect to WiFi
  WiFi.begin(ssid, password, 6);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temperature = data.temperature;
  float humidity = data.humidity;

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT22!");
    delay(20000);
    return;
  }

  Serial.println("----------------------");

  Serial.print("University ID: ");
  Serial.println(universityID);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, server);

    http.addHeader(
      "Content-Type",
      "application/x-www-form-urlencoded"
    );

    String payload =
      "api_key=" + String(apiKey) +
      "&field1=" + String(temperature, 2) +
      "&field2=" + String(humidity, 2);

    int httpCode = http.POST(payload);

    if (httpCode > 0) {
      String response = http.getString();

      Serial.print("HTTP Code: ");
      Serial.println(httpCode);

      Serial.print("ThingSpeak Response: ");
      Serial.println(response);

      if (httpCode == 200 && response.toInt() > 0) {
        Serial.println("Data sent successfully!");
      } else {
        Serial.println("ThingSpeak rejected the update.");
      }
    } else {
      Serial.print("HTTP Error: ");
      Serial.println(http.errorToString(httpCode));
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected!");
  }

  // Update every 20 seconds
  delay(20000);
}
