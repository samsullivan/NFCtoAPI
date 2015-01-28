/*
  @file     NFCtoAPI.ino
  @author   Sam Sullivan
  @created  2014-01-28
*/

#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (4)
#define RESET (5)
#define LED   (13)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);
uint8_t verifiedUID[] = { 0x47, 0xA1, 0x91, 0x74 };

void setup() 
{
  // Initalize LED
  pinMode(LED, OUTPUT);

  // Initialize NFC
  nfc.begin();
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
}

void loop()
{
  // Placeholders for reading tag
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  // Successful tag read
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength))
  {
    if(memcmp(uid, verifiedUID, sizeof(verifiedUID)) == 0) {
      // Valid tag
      digitalWrite(LED, HIGH);
      delay(3000);
      digitalWrite(LED, LOW);
    } else {
      // Invalid tag
      for(int i = 0; i < 3; i++) {
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
      }
    }

    // Wait 1 second before continuing
    delay(1000);
  }
}

