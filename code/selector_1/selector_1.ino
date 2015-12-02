/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define WHITE 0x7
float value=0.0;
int binaryValue= 0;
int bit0=0;
int bit1=0;
int bit2=0;
int bit3=0;
int bit4=0;
int bit5=0;

int bitSelect=0;

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  bit0 = bitRead(binaryValue,0);
  bit1 = bitRead(binaryValue,1);
  bit2 = bitRead(binaryValue,2);
  bit3 = bitRead(binaryValue,3);
  bit4 = bitRead(binaryValue,4);
  bit5 = bitRead(binaryValue,5);
  
  lcd.setCursor(0, 0);
  lcd.print(value); 


    if(value >= 10.0){
      lcd.setCursor(5, 0);  
      lcd.print(" dB   ");  
      }
    else{
      lcd.setCursor(4, 0);  
      lcd.print(" dB   "); 
    }

  lcd.setCursor(10, 0);
  lcd.print(bit5);  
  lcd.setCursor(11, 0);
  lcd.print(bit4);  
  lcd.setCursor(12, 0);
  lcd.print(bit3);  
  lcd.setCursor(13, 0);
  lcd.print(bit2);  
  lcd.setCursor(14, 0);
  lcd.print(bit1);  
  lcd.setCursor(15, 0);
  lcd.print(bit0);  

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(8,bit0);
  digitalWrite(9,bit1);
  digitalWrite(10,bit2);
  digitalWrite(11,bit3);
  digitalWrite(12,bit4);
  digitalWrite(13,bit5);
  

  lcd.setCursor(15-bitSelect, 1);
  lcd.print("^");  
}

uint8_t i=0;
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);

  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
 //   lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {      
      binaryValue += int(pow(2.0,float(bitSelect)+0.0001));
      }
    if (buttons & BUTTON_DOWN) {
      binaryValue -= int(pow(2.0,float(bitSelect)+0.0001));
      }
    if (buttons & BUTTON_LEFT){      
      bitSelect += 1;
      if(bitSelect > 5){
        bitSelect = 0;
        }
      }
    if (buttons & BUTTON_RIGHT){ 
       bitSelect -= 1;
      if(bitSelect < 0){
        bitSelect = 5;
        }
      }
    bit0 = bitRead(binaryValue,0);
    bit1 = bitRead(binaryValue,1);
    bit2 = bitRead(binaryValue,2);
    bit3 = bitRead(binaryValue,3);
    bit4 = bitRead(binaryValue,4);
    bit5 = bitRead(binaryValue,5);
  
    value = 0.5*bit0 + bit1 + 2.0*bit2 + 4.0*bit3 + 8.0*bit4 + 16.0*bit5;
  
    lcd.setCursor(0, 0);
    lcd.print(value); 
//    lcd.setCursor(0, 1);
  //  lcd.print(binaryValue); 

  //  lcd.setCursor(8, 1);
 //   lcd.print(bitSelect); 

//    lcd.setCursor(4,1);
 //   lcd.print(pow(2,bitSelect));

    if(value >= 10.0){
      lcd.setCursor(5, 0);  
      lcd.print(" dB   ");  
      }
    else{
      lcd.setCursor(4, 0);  
      lcd.print(" dB   "); 
    }  
    lcd.setCursor(10, 0);
    lcd.print(bit5);  
    lcd.setCursor(11, 0);
    lcd.print(bit4);  
    lcd.setCursor(12, 0);
    lcd.print(bit3);  
    lcd.setCursor(13, 0);
    lcd.print(bit2);  
    lcd.setCursor(14, 0);
    lcd.print(bit1);  
    lcd.setCursor(15, 0);
    lcd.print(bit0);  

    digitalWrite(8,bit0);
    digitalWrite(9,bit1);
    digitalWrite(10,bit2);
    digitalWrite(11,bit3);
    digitalWrite(12,bit4);
    digitalWrite(13,bit5);


    lcd.setCursor(15-bitSelect, 1);
    lcd.print("^");
    delay(50);
    }
 }  

