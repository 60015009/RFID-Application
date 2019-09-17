/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

String ID1 = "";
String ID2 = "";
String ID3 = "";
String ID4 = "";
String ID5 = "";
String ID6 = "";
String ID7 = "";
String ID8 = "";
String ID9 = "";
String ID10 = "";

// เช็คเข้าออก
int bo1 = 0;
int bo2 = 0;
int bo3 = 0;
int bo4 = 0;
int bo5 = 0;
int bo6 = 0;
int bo7 = 0;
int bo8 = 0;
int bo9 = 0;
int bo10 = 0;

int i = 10;


MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

void setup() {
  
	Serial.begin(9600);		// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
  rfid.PCD_Init();

     
  
}

void loop() {

 if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial() )
    
      return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_ReadCardSerial());

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
  //  Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  
  strID.toUpperCase();

/////////////////////////////////////////////////////////////////////////////////////////

  if(strID.indexOf(ID1) >= 0 && bo1 == 1)
     {
      
      Serial.println(ID1);
      Serial.println("out");
      ID1 = "";
      bo1 = 0;
      delay(1000);
      goto bailout;
      
     }

  if(strID.indexOf(ID2) >= 0 && bo2 == 1)
     {
      
      Serial.println(ID2);
      Serial.println("out");
      ID2 = "";
      bo2 = 0;
      delay(1000);
      goto bailout;
      
     }

////////////////////////////////////////////////////////////////////////////////////////

  if ((bo1 == 0) && (ID1 = ""))
    {
      bo1 = 1;
      ID1 = strID;
      Serial.print("Tap card key: ");
      Serial.println(ID1);
      Serial.println("in");
      delay(1000);
      
    }
   else if ((bo2 == 0) && (ID2 = ""))
    {
      bo2 = 1;
      ID2 = strID;
      Serial.print("Tap card key: ");
      Serial.println(ID2);
      Serial.println("in");
      delay(1000);
    }

   ///////////////////////////////////////////////////////////////////////
   
    
  bailout:

   rfid.PICC_HaltA();
   rfid.PCD_StopCrypto1();
    
  
}
