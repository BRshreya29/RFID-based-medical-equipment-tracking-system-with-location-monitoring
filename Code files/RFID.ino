#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

#define RST_PIN  D3
#define SS_PIN   D4

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
ESP8266WiFiMulti WiFiMulti;
MFRC522::StatusCode status;

int blockNum = 2;
byte bufferLen = 18;
byte readBlockData[18];

String data2;
const String data1 = "https://script.google.com/macros/s/AKfycbzIZCA4f27nTCCdFUQc0wKJJ36rsEFOTEvdiJTRkR1JhvhqskEsVpNHRtQUEEyFPhAI/exec?name=";

bool wifiConnectedPrinted = false;

void setup() {
  Serial.begin(9600);
  Serial.println("\nConnecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Shreya Reddy B R", "987654321");

  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // Only print once when WiFi is first connected
  if (!wifiConnectedPrinted && WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("WiFi connected!");
    wifiConnectedPrinted = true;
  }

  // Wait for a card to be present
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("\nCard detected!");

  ReadDataFromBlock(blockNum, readBlockData);

  Serial.print("Data from block ");
  Serial.print(blockNum);
  Serial.print(" --> ");
  for (int j = 0; j < 16; j++) {
    Serial.write(readBlockData[j]);
  }
  Serial.println();

  // Show WiFi status before attempting to send
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("WiFi is stable ✅");

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure(); // Ignore SSL certificate

    data2 = data1 + String((char*)readBlockData);
    data2.trim();
    Serial.println("Sending to: " + data2);

    HTTPClient https;
    if (https.begin(*client, data2)) {
      int httpCode = https.GET();
      Serial.print("HTTP Response code: ");
      Serial.println(httpCode);
      https.end();
    } else {
      Serial.println("Unable to connect to server");
    }
  } else {
    Serial.println("WiFi is not connected ❌");
  }

  // Halt the card so it can be detected again
  mfrc522.PICC_HaltA();        // Stop reading the card
  mfrc522.PCD_StopCrypto1();   // Stop encryption

  delay(1000); // Wait before next scan
}

void ReadDataFromBlock(int blockNum, byte readBlockData[]) {
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.println("Block read successfully.");
}
