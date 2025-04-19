#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include <WiFiClientSecure.h>

const char* ssid     = "Shreya Reddy B R";
const char* password = "987654321";
const char* serverName = "https://script.google.com/macros/s/AKfycbzIZCA4f27nTCCdFUQc0wKJJ36rsEFOTEvdiJTRkR1JhvhqskEsVpNHRtQUEEyFPhAI/exec";

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // RX=16, TX=17

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    Serial.print("Latitude: "); Serial.println(latitude, 6);
    Serial.print("Longitude: "); Serial.println(longitude, 6);

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client;
      client.setInsecure();

      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");

      String mapsLink = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
      String jsonData = "{\"lat\":" + String(latitude, 6) +
                        ",\"lon\":" + String(longitude, 6) +
                        ",\"link\":\"" + mapsLink + "\"}";

      Serial.println("Sending GPS Data:");
      Serial.println(jsonData);

      int httpResponseCode = http.POST(jsonData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      http.end();
    }
    delay(10000);
  }
}
