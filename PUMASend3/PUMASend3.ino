/* 
PUMASend3.ino

Description:
Control module sends two joystick values to the PUMA.
This is primarily to test radio functionality. Motor functionality will be added later.

Radio Connections:
1 - GND
2 - VCC 3.3V !!! NOT 5V
3 - CE to Arduino pin 7
4 - CSN to Arduino pin 8
5 - SCK to Arduino pin 13
6 - MOSI to Arduino pin 11
7 - MISO to Arduino pin 12
8 - UNUSED

Turret Data:
0 - Turn turret clockwise
1 - Turn turret counter clockwise
2 - Turret move up
3 - Turret move down
4 - Fire
5 - Unused
6 - Unused
7 - Unused

Code Reference:
https://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-ExampleSketches
*/

// Libraries
#include <SPI.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include "printf.h"

// Pin Assignments
#define CW_PIN 2 // Connected to clockwise input
#define ERR_PIN 3 // Turn on if message not sent
#define FIRE_PIN 4 // Connected to turret fire
#define UP_PIN 5 // Connected to turret up
#define DN_PIN 6 // Connected to turret down
#define CE_PIN 7 // Radio
#define CSN_PIN 8 // Radio
#define CCW_PIN 9 // Connected to counter clockwise input
#define SS_PIN 10 // DON'T USE THIS PIN AS AN INPUT
#define MOSI_PIN 11 // Radio
#define MISO_PIN 12 // Radio
#define SCK_PIN 13 // Radio
#define INL 14 // Connected to left joystick, a0
#define INR 15 // Connected to right joystick, a1

// Constants
#define TIMEOUT 5
#define LFWD 0
#define LREV 1
#define RFWD 0
#define RREV 1
#define SCALING 0
#define CFG 1 // Activate motor out
#define TSTOP 0 // Turret stop
#define TCW 1 // Turret clockwise
#define TCCW 2 // Turret counterclockwise

// Variables
int lval;
int rval;
int fval;

// Pipes
const uint64_t pipe_r = 0xF0F0F0F0D2LL; // Define the receive pipe
const uint64_t pipe_t = 0xF0F0F0F0E1LL; // define the transmit pipe

// Radio
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

// end
bool done;
bool tx_ok, tx_fail, rx_ready;

// Joystick Values
byte joystick[4];  // 4 element array holding Joystick readings

// Turns the raw joystick values into bytes to send
byte processJoystick(int turretval) {
  byte output = B0000;
  if(turretval >= 959) { output = B1111; }      // Forward 7
  else if(turretval >= 895) { output = B1110; } // Forward 6
  else if(turretval >= 831) { output = B1101; } // Forward 5
  else if(turretval >= 767) { output = B1100; } // Forward 4
  else if(turretval >= 703) { output = B1011; } // Forward 3
  else if(turretval >= 639) { output = B1010; } // Forward 2
  else if(turretval >= 575) { output = B1001; } // Forward 1
  else if(turretval >= 511) { output = B1000; } // Stop
  else if(turretval >= 447) { output = B0000; } // Stop
  else if(turretval >= 383) { output = B0001; } // Reverse 1
  else if(turretval >= 319) { output = B0010; } // Reverse 2
  else if(turretval >= 255) { output = B0011; } // Reverse 3
  else if(turretval >= 191) { output = B0100; } // Reverse 4
  else if(turretval >= 127) { output = B0101; } // Reverse 5
  else if(turretval >=  63) { output = B0110; } // Reverse 6
  else if(turretval >=   0) { output = B0111; } // Reverse 7
  else { output = B0000; } // Stop
  return output;
}

// Reads bits and determines turret commands
byte processTurret() {
  byte output = 0;
    
  // Read Turret Values
  if(digitalRead(CW_PIN) == HIGH) { output = output | 0x01; }
  if(digitalRead(CCW_PIN) == HIGH) { output = output | 0x02; }
  if(digitalRead(UP_PIN) == HIGH) { output = output | 0x04; }
  if(digitalRead(DN_PIN) == HIGH) { output = output | 0x08; }
  if(digitalRead(FIRE_PIN) == HIGH) { output = output | 0x10; }
  
  return output;
}

// setup: Sets up system
void setup()
{
  // Start serial transmission
  Serial.begin(9600);
  //printf_begin();
  
  // Wait 1 second
  delay(2000);
  
  // Start Radio
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(5,15);
  radio.enableDynamicAck();
  //radio.setChannel(108);  // Above most Wifi Channels // do we need this?
  //radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(pipe_t);
  //radio.openReadingPipe(1,pipe_r);
  //radio.stopListening();
  delay(1000);

  // Initialize variables
  lval = 0;
  rval = 0;
  fval = 0;
  joystick[0] = 0;
  joystick[1] = 0;
  joystick[2] = 0;
  joystick[3] = 0;
  
  // Start Joysticks
  pinMode(INL,INPUT);
  pinMode(INR,INPUT);
  
  // Start Cannon Rotation
  pinMode(CW_PIN,INPUT);
  pinMode(CCW_PIN,INPUT);
  pinMode(UP_PIN,INPUT);
  pinMode(DN_PIN,INPUT);
  pinMode(FIRE_PIN,INPUT);
  
  // Set up error output
  pinMode(ERR_PIN,OUTPUT);
  digitalWrite(ERR_PIN,HIGH);

}

// loop: Runs constantly
void loop()
{
  // Read Joystick Values
  lval = analogRead(INL);
  rval = analogRead(INR);
  //Serial.print("Left = ");
  //Serial.print(lval);
  //Serial.print(" Right = ");
  //Serial.print(rval);
  //Serial.print("\n");

  // Set up message
  joystick[0] = processJoystick(lval);
  joystick[1] = processJoystick(rval);
  joystick[2] = processTurret();
  joystick[3] = 0;
  
  // Send Joystick Values
  //Serial.print(fval);
  //Serial.print(" Now Sending Left = ");
  //Serial.print(joystick[0]);
  //Serial.print(" Right = ");
  //Serial.print(joystick[1]);
  //Serial.print(" Turret = ");
  //Serial.print(joystick[2]); 
  //Serial.print(" Other = ");
  //Serial.print(joystick[3]);
  //Serial.print(" Status = ");
  done = radio.write(&joystick, sizeof(joystick));
  Serial.print(fval);
  if (done) { 
    Serial.print(" SUCCESS\n");
    digitalWrite(ERR_PIN,LOW);
  }
  else { 
    Serial.print(" FAILURE\n");
    digitalWrite(ERR_PIN,HIGH);
  }
  
  
  // Wait
  fval++;
  delay(100);
  //radio.whatHappened(tx_ok,tx_fail,rx_ready);
  //Serial.print(tx_ok);
  //Serial.print(" ");
  //Serial.print(tx_fail);
  //Serial.print(" ");
  //Serial.print(rx_ready);
  //Serial.print("\n");
  //radio.printDetails();
  //radio.powerDown();
  //delay(100);
  //radio.powerUp();
}
