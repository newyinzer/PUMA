/* 
PUMASend.ino

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
*/

// Libraries
#include <SPI.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

// Pin Assignments
#define CE_PIN 7 // Radio
#define CSN_PIN 8 // Radio
#define INL 14 // Connected to left joystick
#define INR 15 // Connected to right joystick

// Constants
#define TIMEOUT 5
#define LFWD 0
#define LREV 1
#define RFWD 0
#define RREV 1
#define SCALING 0
#define CFG 1 // Activate motor out

// Variables
int lval;
int rval;

// Pipes
const uint64_t pipe_r = 0xF0F0F0F0D2LL; // Define the receive pipe
const uint64_t pipe_t = 0xF0F0F0F0E1LL; // define the transmit pipe

// Radio
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

// end
bool done;

// Joystick Values
byte joystick[4];  // 4 element array holding Joystick readings

byte processJoystick(int val) {
  byte output = 0;
  int outint = val;
  if(outint >= 512) {
    // forward
    outint = outint - 512;
    outint = outint >> 2;
  }
  else if (outint <= 480) {
    // reverse
    outint = outint >> 2;
    outint = outint + 128;
  }
  else {
    // stop
    outint = 0;
  }
  
  output = (byte) outint;
  return output;
}

// setup: Sets up system
void setup()
{
  // Start serial transmission
  Serial.begin(57600);
  
  // Wait 2 seconds
  delay(2000);
  printf_begin();
  
  // Start Radio
  done = radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(5,15);
  radio.openWritingPipe(pipe_t);
  radio.openReadingPipe(1,pipe_r);
  radio.startListening();
  
  // Initialize variables
  lval = 0;
  rval = 0;
  joystick[0] = 0;
  joystick[1] = 0;
  joystick[2] = 0;
  joystick[3] = 0;
  
  // Start Joysticks
  pinMode(INL,INPUT);
  pinMode(INR,INPUT);
}

// loop: Runs constantly
void loop()
{
  // Read Joystick Values
  lval = analogRead(INL);
  rval = analogRead(INR);
  printf("Left = %d Right = %d\n",lval,rval);
  joystick[0] = processJoystick(lval);
  joystick[1] = processJoystick(rval);
  joystick[2] = 0;
  joystick[3] = 0;
  
  // Send Joystick Values
  radio.stopListening();
  printf("Now Sending Left = %d Right = %d\n",joystick[0],joystick[1]);
  
  done = radio.write(&joystick, 4);
  if (done) { printf("SUCCESS\n"); }
  else { printf("FAILURE\n"); }
  
  radio.startListening();

  // Wait
  delay(100);
}
