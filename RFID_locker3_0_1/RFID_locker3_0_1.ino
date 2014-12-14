////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <DS1302.h>

/* RTC
CE(DS1302 pin5) -> Arduino D5
IO(DS1302 pin6) -> Arduino D6
SCLK(DS1302 pin7) -> Arduino D7
*/
uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;

char buf[50];
char day[10];

String comdata = "";
int numdata[7] ={0};
int j = 0, mark = 0;

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

////////////////////////////////////////////////////////////////////////

#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#include <SD.h>
File myFile;

#define SS_PIN 10
#define RST_PIN 9

Servo myservo;
MFRC522 rfid(SS_PIN, RST_PIN);

unsigned char reading_card[5]; //for reading card
unsigned char master[5] = {131,142,23,188,0}; // allowed card
unsigned char i;

void indication(int led);
void allow();
void denied();
int pos = 0;
const int chipSelect = 4;

boolean acces = false;
String num;

boolean lock = false;

void setup()
{
	myservo.attach(3);
	Serial.begin(9600);
	SPI.begin();
	rfid.PCD_Init();

	myservo.write(180);

	rtc.write_protect(false);
	rtc.halt(false);
	pinMode(10, OUTPUT);
}

void loop()
{
	// Look for new cards
	if ( ! rfid.PICC_IsNewCardPresent())
	return;
	{
		if (rfid.PICC_ReadCardSerial())
		{
			for (i = 0; i < 5; i++)
			{
				num += rfid.uid.uidByte[i];
				num += " ";
				reading_card[i] = rfid.uid.uidByte[i];
			}

			//verification
			for (i = 0; i < 5; i++)
			{
				if (reading_card[i]!=master[i])
				{
					break;
				}
			}
			if (i == 5)
			{
				save();
				acces = true;
				allow();
				
				save();
			}
			else
			{
				acces = false;
				save();
			}
		}
	}
	rfid.PICC_HaltA();
}

void allow()
{
	if(lock == false)
	{
		myservo.write(90);
		lock = true;
	}
	else
	{
		myservo.write(180);
		lock = false;
	}
}




