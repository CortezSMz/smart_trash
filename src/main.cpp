#include "Static.h"
#include "Util.h"

void printDFPDetail(int type, int value);

// MFRC522
#include <Wire.h>
#include <MFRC522v2.h>
#include <MFRC522Debug.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>

MFRC522DriverPinSimple ss_pin(15);
MFRC522DriverSPI driver{ss_pin};
MFRC522 mfrc522{driver};

String tagContent = "";

// TFT ST7735
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// DFPlayer Mini
#include "HardwareSerial.h"
#include "DFRobotDFPlayerMini.h"

const byte RXD2 = 17;
const byte TXD2 = 16;
const byte dfBusyPin = 22;
HardwareSerial dfSD(1);
DFRobotDFPlayerMini DFPlayer;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // MFRC522 setup
  mfrc522.PCD_Init();
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
  Serial.println();
  Serial.println(F("Scan the RFID card to see the UID..."));

  // TFT ST7735 setup
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextWrap(true, true);

  // DFPlayer Mini setup
  dfSD.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  delay(5000);
  if (!DFPlayer.begin(dfSD))
  {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  pinMode(dfBusyPin, INPUT);
  DFPlayer.setTimeOut(500);
  DFPlayer.volume(10); // Volume value. From 0 to 30
  DFPlayer.EQ(0);      /*  0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass */
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

void loop()
{
  // Read DFPlayer status
  if (DFPlayer.available())
  {
    printDFPDetail(DFPlayer.readType(), DFPlayer.read());
  }

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() || !digitalRead(dfBusyPin))
  {
    delay(250);
    return;
  }

  // Get RFID card UID
  tagContent = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    tagContent.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tagContent.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagContent.toUpperCase();
  Serial.println(tagContent);

  // Loop trought card info
  for (int i = 0; i < (sizeof(cards) / sizeof(int)) - 1; i++)
  {
    if (strcmp(cards[i].RFIDUID, tagContent.c_str()) == 0)
    {
      // Break if file count is lower than current index
      if ((i + 1) > DFPlayer.readFileCounts())
      {
        break;
      }

      DFPlayer.play(cards[i].song);

      // Write UID to screen
      tft.setCursor(0, 0);
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.println("TAG UID: ");
      tft.println(tagContent);

      // Write card info
      tft.println("");
      tft.setTextColor(cards[i].color, TFT_BLACK);
      tft.println(cards[i].text);
      tft.fillRectVGradient(0, 50, 128, 128, TFT_BLACK, cards[i].color);

      break;
    }
  }
}