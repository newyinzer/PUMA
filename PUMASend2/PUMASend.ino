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
  outint = outint - 512;
  outint = outint / 4;
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
  joystick[0] = processJoystick(lval);
  joystick[1] = processJoystick(rval);
  joystick[2] = 0;
  joystick[3] = 0;
  /*
  if ( radio.available() )
  {
    Serial.println("Radio Available");
    i = 0;
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
    
    if(joystick[0] > 127) { 
      ldirection = LREV; 
      lspeed = (255 - joystick[0]) << 1;
    }
    else { 
      ldirection = LFWD; 
      lspeed = joystick[0] << 1;
    }
    if(joystick[1] > 127) { 
      rdirection = RREV; 
      rspeed = (255 - joystick[1]) << 1;
    }
    else { 
      rdirection = RFWD; 
      rspeed = joystick[1] << 1;
    }
  }
  else
  {   
    if(i >= TIMEOUT) {
      // If we hit the timeout, stop moving
      ldirection = LFWD;
      rdirection = RFWD;
      lspeed = 0;
      rspeed = 0;
      i = TIMEOUT;
    }
    else {
      // Maintain current speed and direction for the time being
      ldirection = ldirection;
      rdirection = rdirection;
      lspeed = lspeed;
      rspeed = rspeed;
      i = i + 1;
    }
  }
  
  // Print Left
  if(ldirection == LREV) { 
    Serial.print("Left Reverse "); 
    digitalWrite(IN1,LOW); 
    digitalWrite(IN2,HIGH);
  }
  else { 
    Serial.print("Left Forward "); 
    digitalWrite(IN1,HIGH); 
    digitalWrite(IN2,LOW);
  }
  if(CFG == 1) {
    Serial.print(" ACTIVE ");
    analogWrite(ENA,lspeed);
  } 
  else {
    Serial.print(" NOT ACTIVE ");
    analogWrite(ENA,0);
  }
  Serial.println(lspeed);
  
  // Print Right
  if(rdirection == RREV) { 
    Serial.print("Right Reverse "); 
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }
  else { 
    Serial.print("Right Forward "); 
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  }
  if(CFG == 1) {
    Serial.print(" ACTIVE ");
    analogWrite(ENB,rspeed);
  } 
  else {
    Serial.print(" NOT ACTIVE ");
    analogWrite(ENB,0);
  }
  Serial.println(rspeed);
  */
  // Wait
  delay(100);
}
