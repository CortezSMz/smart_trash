#include "static/Cards.h"
#include "static/Colors.h"
#include "Util.h"

void printDFPDetail(int type, int value);
ColorDictionary getColor(char *name);
RfidCardDictionary getCard(char *UID);

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

// LCD
#include <LiquidCrystal_I2C.h>

#define LCD_I2C_SDA 25
#define LCD_I2C_SCL 26

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

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
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextWrap(true, true);

  // LCD
  lcd.init(LCD_I2C_SDA, LCD_I2C_SCL);
  lcd.backlight();

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
  DFPlayer.volume(30); // Volume value. From 0 to 30
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

  // Reset the loop if no new card present on the sensor/reader OR if DFPlayer is busy.
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() || !digitalRead(dfBusyPin))
  {
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

  // Get card info
  RfidCardDictionary card = getCard((char *)tagContent.c_str());
  ColorDictionary color = getColor(card.color);

  // Write to TFT
  tft.setCursor(0, 0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("TAG UID: ");
  tft.println(tagContent);
  tft.println();
  tft.setTextColor(color.code, TFT_BLACK);
  tft.println(card.text);
  tft.fillRectVGradient(0, 50, 128, 128, TFT_BLACK, color.code);

  // Write to LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(card.text);
  lcd.setCursor(0, 1);
  lcd.print(color.name);
  lcd.print(" TRASH");

  // Check if song index is within sound file count and play
  if (card.songId > 0 && card.songId <= DFPlayer.readFileCounts())
  {
    DFPlayer.play(card.songId);

    delay(500);

    return;
  }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println();
  tft.print("No sound for ID:");
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.println(card.songId);

  delay(500);
}
