int ledPin = 13; //LED anode connected to digital pin 13

int inputPin = 2; //infrared proximity switch connected to digital pin 2

int val = 1; //this variable will read the value from the sensor
int i = 0;
void setup() 
{
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT); //declare LED as output
  pinMode(inputPin, INPUT); //declare infrared sensor as input

}

void loop()

{

      val = digitalRead(inputPin); // read input value
      
      if (val == HIGH)  //check if the input is HIGH
      {
          i += 1;
          delay(1000);
          Serial.println();
          Serial.print(i);
      }
      
      else      
      {
         Serial.println();
      }

}
