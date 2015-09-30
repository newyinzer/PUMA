/* 
PUMAcore.ino

Description:
PUMA receives two joystick values from Pi and sends what it gets back on the monitor.
This is primarily to test radio functionality. Motor functionality will be added later.

Connections:
1 - GND
2 - VCC 3.3V !!! NOT 5V
3 - CE to Arduino pin 7
4 - CSN to Arduino pin 8
5 - SCK to Arduino pin 13
6 - MOSI to Arduino pin 11
7 - MISO to Arduino pin 12
8 - UNUSED
*/

// Libraries
#include <SPI.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

// Constants
#define CE_PIN 7
#define CSN_PIN 8
#define LFWD 0
#define LREV 1
#define RFWD 0
#define RREV 1
#define SCALING 0

// Variables
int ldirection;
int rdirection;
int lspeed;
int rspeed;

// Pipes
const uint64_t pipe_t = 0xF0F0F0F0D2LL; // Define the transmit pipe
const uint64_t pipe_r = 0xF0F0F0F0E1LL; // define the receive pipe

// Radio
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

// end
bool done;
int i;

// Joystick Values
byte joystick[4];  // 4 element array holding Joystick readings

// setup: Sets up system
void setup()
{
  Serial.begin(57600);
  delay(2000);
  printf_begin();
  Serial.println("Nrf24L01 Receiver Starting");
  done = radio.begin();
  Serial.println("");
  radio.enableDynamicPayloads();
  radio.setRetries(5,15);
  radio.printDetails();
  radio.openWritingPipe(pipe_t);
  radio.openReadingPipe(1,pipe_r);
  radio.printDetails();
  radio.startListening();
  ldirection = LFWD;
  rdirection = RFWD;
  lspeed = 0;
  rspeed = 0;
  i = 0;
}

// loop: Runs constantly
void loop()
{
  
  if ( radio.available() )
  {
    Serial.println("Radio Available");
    // Read the data payload until we've received everything
    done = false;
    while (radio.available())
    {
      // Fetch the data payload
      radio.read( joystick, sizeof(joystick) );
      
      Serial.print("L = ");
      
      
      Serial.print(joystick[0]);
      
      Serial.print(" R = ");      
      Serial.print(joystick[1]);
      Serial.print(" Special2 = ");      
      Serial.print(joystick[2]);
      Serial.print(" Special3 = ");      
      Serial.println(joystick[3]);
    }
    
    lspeed = joystick[0] >> SCALING;
    lspeed = abs(lspeed);
    
    rspeed = joystick[1] >> SCALING;
    rspeed = abs(rspeed);
    
    if(joystick[0] < 0) { ldirection = LREV; }
    else { ldirection = LFWD; }
    if(joystick[1] < 0) { rdirection = RREV; }
    else { rdirection = RFWD; }
  }
  else
  {    
      Serial.println("NO Radio Available");
      ldirection = LFWD;
      rdirection = RFWD;
      lspeed = 0;
      rspeed = 0;
  }
  
  // Write Motor Values
  // Insert later KEYWORD
  
  // Print Left
  if(ldirection = LREV) { Serial.print("Left Reverse "); }
  else { Serial.print("Left Forward "); }
  Serial.println(lspeed);
  
  // Print Right
  if(rdirection = RREV) { Serial.print("Right Reverse "); }
  else { Serial.print("Right Forward "); }
  Serial.println(rspeed);
  
  // Wait
  delay(100);
}
