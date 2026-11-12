
#include <SPI.h>
#include <MFRC522.h>

// ESP32 RFID connections
#define SS_PIN    5
#define RST_PIN   22
#define SCK_PIN   18
#define MISO_PIN  19
#define MOSI_PIN  23

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  mfrc522.PCD_Init();

  delay(100);
  Serial.println("RFID Scanner Starting...");

  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("Ready! Tap your RFID card.");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("CARD DETECTED!");

  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("Card Type: ");
  MFRC522::PICC_Type type =
      mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(type));

  Serial.println("----------------------");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
