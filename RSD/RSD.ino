#include <LiquidCrystal_PCF8574.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
int num = 0;
LiquidCrystal_PCF8574 lcd(0x3F);
File myFile;
const int chipSelect = 10;

void setup() {
  lcd.setBacklight(255);
  lcd.begin(20,4);
  lcd.display();
  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    return;  
  }
  ReadText();
}

void loop() {
  
}


void ReadText(){
  myFile = SD.open("test.txt",FILE_READ);
  if (myFile) {
      while (myFile.available()) {  
        char readByte = myFile.read();
          Serial.write(readByte);
          //lcd.write(readByte);
        if (readByte != '\n'){
          //lcd.print(readByte);
          lcd.write(readByte);
          delay(100);
        }else if(num - 3 == 0){
          lcd.setCursor(0,0);
          num = 0;
          delay(1000);
          lcd.clear();
          delay(1000);
        }else{
          num++;
          lcd.setCursor(0,num);
        }

}
    // close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}










