#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
byte comdata;
LiquidCrystal_I2C lcd(0x27,18,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.begin(16, 2); // set up the LCD 16x2
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Swipe your card to the reader for access right...");
  Serial.println();
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  for (int i = 0; i < 3; i++) {
        lcd.backlight();
        delay(250);
        
    }
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Hello,Alvin!");
  delay(500);
  lcd.setCursor(1,1);
  lcd.print("Swipe your card");
  delay(500);
  
}


void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  //if (content.substring(1) == "69 2C 7F 9B") //change here the UID of the card/cards that you want to give access
  if (content.substring(1) == "53 B9 A2 03") //change here the UID of the card/cards that you want to give access
  
  {
    Serial.println("1");
    Serial.println();
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.clear();
    lcd.print("Deducted $2");
    delay(5000);
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.clear();
    lcd.print("Hello,Alvin");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("Swipe your card");
    delay(3000);
  }
 
 else   {
    Serial.println("2");
    Serial.println();
    lcd.backlight();
    lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("Access Denied");
    delay(3000);
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.clear();
    lcd.print("Hello,Alvin");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("Swipe your card");
    delay(500);
    
  }
}
