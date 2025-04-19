#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;  // Reset pin for RC522
constexpr uint8_t SS_PIN  = D4;  // SDA pin for RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte bufferLen = 18;
byte readBlockData[18];
MFRC522::StatusCode status;
 
// Your equipment data (combine name and ID into a single 16-byte block)
byte equipmentData[16] = {"ECGMonitor-ID25"};  // Block 2 (16 bytes max)

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan RFID Tag to write medical equipment data...");
}

void loop() {
  // Prepare key (default all to 0xFF)
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  // Check for new RFID card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  Serial.println("\n**Card Detected**");

  // Print UID of the card
  Serial.print("UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX); Serial.print(" ");
  }
  Serial.println();

  // Write name and ID to tag (in a single block)
  WriteDataToBlock(2, equipmentData);

  // Read back to verify
  Serial.println("\nVerifying written data:");
  ReadDataFromBlock(2, readBlockData);
  Serial.print("Equipment Data: ");
  for (int j = 0; j < 16; j++) {
    Serial.write(readBlockData[j]);
  }
  Serial.println();

  delay(3000);
  mfrc522.PICC_HaltA();  // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}

// Function to write data to a specific block
void WriteDataToBlock(int blockNum, byte blockData[]) {
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Auth failed for block "); Serial.println(blockNum);
    return;
  }

  status = mfrc522.MIFARE_Write(blockNum, blockData, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Write failed for block "); Serial.println(blockNum);
    return;
  }

  Serial.print("Data written to block "); Serial.println(blockNum);
}

// Function to read data from a specific block
void ReadDataFromBlock(int blockNum, byte readBlockData[]) {
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Auth failed for block "); Serial.println(blockNum);
    return;
  }

  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Read failed for block "); Serial.println(blockNum);
    return;
  }
}
