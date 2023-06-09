#include "static/Cards.h"
#include "static/Colors.h"
#include "Util.h"

// Images
#include "images/trash_can.h"
#include "images/recycle_arrow.h"
#include "images/current_item.h"

void printDFPDetail(int type, int value);
ColorShade getColorShade(unsigned short color);
RfidCard getCard(char *UID);
void updateTFT();
void updateLCD(RfidCard card, ColorShade color);

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
TFT_eSprite bgSprite = TFT_eSprite(&tft);
TFT_eSprite trashCanSprite = TFT_eSprite(&tft);
TFT_eSprite recycleArrowSprite = TFT_eSprite(&tft);
TFT_eSprite currentItemSprite = TFT_eSprite(&tft);

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
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  bgSprite.createSprite(128, 128);
  bgSprite.setSwapBytes(true);

  trashCanSprite.createSprite(88, 100);

  recycleArrowSprite.createSprite(30, 28);
  recycleArrowSprite.setSwapBytes(true);

  currentItemSprite.createSprite(30, 30);

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
  Serial.print("Audio files:");
  Serial.println(DFPlayer.readFileCounts());

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

  if (!tagContent.isEmpty())
    updateTFT();

  // Reset the loop if no new card present on the sensor/reader OR if DFPlayer is busy.
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() || !digitalRead(dfBusyPin))
  {
    delay(50);
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

  // Get card info
  RfidCard card = getCard((char *)tagContent.c_str());
  ColorShade color = getColorShade(card.color);
  Serial.print("card: ");
  Serial.print(card.color);
  Serial.print(" - ");
  Serial.print(card.RFIDUID);
  Serial.print(" - ");
  Serial.print(card.songId);
  Serial.print(" - ");
  Serial.println(card.text);

  setTrashCanColor(color.shades[0]);

  setCurrentItem(card);

  updateLCD(card, color);

  if (card.songId >= 0 && card.songId <= DFPlayer.readFileCounts())
  {

    DFPlayer.play(card.songId);

    delay(500);
  }
}

void updateTFT()
{
  bgSprite.fillScreen(TFT_BLACK);

  trashCanSprite.pushImage(0, 0, 88, 100, trash_can);
  trashCanSprite.pushToSprite(&bgSprite, 20, 28, TFT_BLACK);

  bgSprite.setPivot(65, 98);
  recycleArrowSprite.pushImage(0, 0, 30, 28, recycle_arrow);
  recycleArrowSprite.pushRotated(&bgSprite, arrowAngle, TFT_BLACK);

  currentItemSprite.pushImage(0, 0, 30, 30, current_item);
  currentItemSprite.pushToSprite(&bgSprite, 5, 100, TFT_BLACK);

  bgSprite.pushSprite(0, 0);

  rotateRecycleArrow();

  bgSprite.flush();
}

void updateLCD(RfidCard card, ColorShade color)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(card.text);
  lcd.setCursor(0, 1);
  lcd.print(color.name);
  lcd.print(" TRASH");
}
