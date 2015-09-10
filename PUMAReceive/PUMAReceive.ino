/* 
PUMAcore.ino

Description:
PUMA receives two joystick values from Pi and sends what it gets back on the monitor.
This is primarily to test radio functionality. Motor functionality will be added later.

Connections:
1 - GND
2 - VCC 3.3V !!! NOT 5V
3 - CE to Arduino pin 9
4 - CSN to Arduino pin 10
5 - SCK to Arduino pin 13
6 - MOSI to Arduino pin 11
7 - MISO to Arduino pin 12
8 - UNUSED
*/

// Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Constants
#define CE_PIN   9
#define CSN_PIN 10
#define LFWD 0
#define LREV 1
#define RFWD 0
#define RREV 1

// Variables
int ldirection;
int rdirection;
int lspeed;
int rspeed;

// Pipes
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

// Radio
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

// Joystick Values
int joystick[2];  // 2 element array holding Joystick readings

// 

// setup: Sets up system
void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

// loop: Runs constantly
void loop()
{
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.print(joystick[0]);
      Serial.print(" Y = ");      
      Serial.println(joystick[1]);
    }
  }
  else
  {    
      Serial.println("No radio available");
  }

}
