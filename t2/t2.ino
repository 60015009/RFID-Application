#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <Time.h>

LiquidCrystal_PCF8574 lcd(0x3F);
String a = "60015031";
long randNumber;
void setup()
{
  lcd.setBacklight(255);
  lcd.begin(20,4);
  lcd.display();
  lcd.setCursor(0, 2);
  lcd.print(a);
  randomSeed(analogRead(0))
}
void loop()
{
  tmElements_t tm; 
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    lcd.setCursor(0, 0);
    lcd.print("Time = ");
    lcd.print(tm.Hour);
    
    Serial.write(':');
    print2digits(tm.Minute);
    lcd.print(":");
    lcd.print(tm.Minute);
    

    
    Serial.write(':');
    print2digits(tm.Second);
    lcd.print(":");
    lcd.print(tm.Second);
    
    
    Serial.print(", Date = ");
    Serial.print(tm.Day);
    lcd.setCursor(0, 1);
    lcd.print("Date = ");
    lcd.print(tm.Day);

    
    Serial.write('/');
    Serial.print(tm.Month);
    lcd.print("/");
    lcd.print(tm.Month);
    
    
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
    lcd.print("/");
    lcd.print(tmYearToCalendar(tm.Year));
    lcd.setCursor(0, 1);
    randNumber = random(300);
    lcd.print(randNumber);
    delay(50);

    
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
  

