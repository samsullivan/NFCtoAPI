/*
  @file     NFCtoAPI.ino
  @author   Sam Sullivan
  @created  2014-01-28
*/

#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (4)
#define RESET (5)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);
uint8_t verifiedUID[] = { 0x47, 0xA1, 0x91, 0x74 };

void setup() 
{
  Serial.begin(115200);
  while (!Serial); // waiting for Leonardo

  nfc.begin();
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
}

void loop()
{
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength))
  {
    uint8_t scannedUid[uidLength];
    for(uint8_t i = 0; i < uidLength; i++) {
      scannedUid[i] = uid[i];
    }

    if(memcmp(scannedUid, verifiedUID, sizeof(verifiedUID)) == 0) {
      Serial.println("Valid tag!");
    } else {
      Serial.println("Invalid tag...");
    }

    // Wait 1 second before continuing
    delay(1000);
  }
}

