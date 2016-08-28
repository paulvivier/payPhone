/*

Since the behavior is to mimic a standard landline as much as possible, 
We're goint to start with a basic switch. 

On = ready to dial
Off = ready to recieve a call

 */

 /* Defects:
  *  - Should stop and tell me if the battery is disconnected or low. 
  *  - Microphone is not active when picking up
  * 
  *
  * 
  * */

  

// Define the FONA libraries and inputs
#include "Adafruit_FONA.h"

#define FONA_RX 2
#define FONA_TX 9
#define FONA_RST 4

// Note you need to map interrupt number to pin number
// for your board.  On an Uno & Mega interrupt 0 is
// digital pin 2, and on a Leonardo interrupt 0 is
// digital pin 3.  See this page for a complete table:
//   http://arduino.cc/en/Reference/attachInterrupt
// Make sure this interrupt pin is connected to FONA RI!
// #define FONA_RI_INTERRUPT  0

// FONA default to using software serial. If you want to use hardware serial
// (because softserial isnt supported) comment out the following three lines 
// and uncomment the HardwareSerial line
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Hardware serial is also possible!
//  HardwareSerial *fonaSerial = &Serial1;

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

uint8_t type;



// Digital Input for Receiver switch 
const int  receiverPin = 12;    // the pin that the receiver is attached to
const int ledPin = 13;       // the pin that the LED is attached to
int receiverState = 0;         // current state of the receiver

// Variables will change:
// int buttonPushCounter = 0;   // counter for the number of button presses
// int receiverState = 0;         // current state of the button
// int lastreceiverState = 0;     // previous state of the button

void setup() {
  // initialize the receiver pin as a input:
  pinMode(receiverPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);

 // Initialize FONA
     fonaSerial->begin(4800);
      if (! fona.begin(*fonaSerial)) {
        Serial.println(F("Couldn't find FONA"));
        while (1);
      }
      type = fona.type();
      Serial.println(F("FONA is OK"));
      Serial.print(F("Found "));
      switch (type) {
        case FONA800H:  // There is a larger list in 'FONAtest' if you want to add more cases.
          Serial.println(F("FONA 800H")); break;
        default: 
          Serial.println(F("???")); break; // Just in case its not recognized.
      }

  
}

void loop() {

  
  // read the receiver input pin:
      receiverState = digitalRead(receiverPin);
      
  // compare the receiverState to its previous state
      if (receiverState == HIGH) {
        // if the current state is HIGH then the reciver
        // went from off to on:
        Serial.println("on");
        digitalWrite(ledPin, HIGH);
      }


// FONA Setup


 
// Stop everything and tell me to plug the battery in. 
 uint16_t vbat;
 if (! fona.getBattPercent(&vbat)) {
          Serial.println(F("Failed to read Batt"));
        } else {
          Serial.print(F("VPct = ")); Serial.print(vbat); Serial.println(F("%"));
        }  
    while (vbat < 2) {
      Serial.println("Battery not connected. Continue ? [Y]"); 
      char command = Serial.read();
        Serial.println(command);
      
        switch (command) {
          case 'Y': {
              Serial.println("Its your call ... Pun intended");
              break;
            }
          case 'N': {
              Serial.println("Its your call ... Pun intended");
              break;
            }
         }
    }      
// Main Loop - Call Status . 
// Each Case should check the Reciever switch. 
//      receiverState = ON  - Handset has been removed
//      receiverState = OFF - Handset has been placed

// I decided to make the main loop around the FONA status.
// This way we always start with the state of the phone call
// whether its ready to dial, in progress or waiting for a call. 


int8_t callstat = fona.getCallStatus();
  char callerID[32] = {0};


// *** Defect: New state of the button isn't getting read inside the loop. (fixed)
// *** Defect: Set external audio when picked up. 

while (! callstat) {
 
  // Turn the LED on and off based on the switch state
      if (receiverState == HIGH) {
        // if the current state is HIGH then the reciver
        // went from off to on:
        Serial.println("RECEIVER ON");
        digitalWrite(ledPin, HIGH);
        }
      else {
        // if the current state is HIGH then the reciver
        // went from off to on:
        Serial.println("RECEIVER OFF");
        digitalWrite(ledPin, LOW);
        }

  
        // get call status
        Serial.println("*** ******** ******* ");
//        Serial.println("Call Status: ");
        int8_t callstat = fona.getCallStatus();
        receiverState = digitalRead(receiverPin);
//        Serial.println("Receiver Status: ");
//        Serial.print(receiverPin);
        switch (callstat) {
          case 0: Serial.println(F("Ready")); 
                // wait for the receiverState to change. 

                if (receiverState == HIGH) {
                  Serial.println("RECEIVER ON");
                  digitalWrite(ledPin, HIGH);
                }
                else if (receiverState == LOW) {
                  Serial.println("RECEIVER OFF");
                  digitalWrite(ledPin, LOW);
                }
              
                
                break;
          
          case 1: Serial.println(F("Could not get status")); break;
          case 3: Serial.println(F("Ringing (incoming)")); 

                // Set External output
                if (! fona.setAudio(FONA_EXTAUDIO)) {
                  Serial.println(F("Failed to set external audio"));
                } else {
                  Serial.println(F("Set external audio"));
                }

                // While incoming call is being made sit here 
                // and wait for the receiver to be picked up. 
                do
                {
                  delay(50);          // wait for sensors to stabilize  
                  Serial.println("Incoming call ... ");
                  receiverState = digitalRead(receiverPin);
                } while (receiverState == LOW);

              
                if (receiverState == HIGH) {
                  // Handset has been picked up):

                    // Tell FONA to pick up the call.
                    if (! fona.pickUp()) {
                      Serial.println(F("Failed to pickup"));
                    } else {
                      Serial.println(F("Call picked up"));
                    }
          
                  digitalWrite(ledPin, HIGH);
                }              
 /* 
                  
                
                else if (receiverState == LOW) {
                  // LOW = OFF:
                  Serial.println("OFF");
                  digitalWrite(ledPin, LOW);

                }
*/
                  // check the state before looping again.
                  receiverState = digitalRead(receiverPin);

                break; 

                
          case 4: Serial.println(F("Ringing/in progress (outgoing)")); 
               
                // While a call is in progress 
                // wait for the receiver to be put down. 
                do
                {
                  delay(100);          // wait for sensors to stabilize  
                  Serial.println("Call in progress");
                  // check the state before looping again.
                  receiverState = digitalRead(receiverPin);                  
                } while (receiverState == HIGH);
                
                  // when the reciverPin reads LOW then do this:
                if (! fona.hangUp()) {
                    Serial.println(F("Failed"));
                  } else {
                    Serial.println(F("OK!"));
                  }
                  
                break;
          
          default: Serial.println(F("Unknown")); break;
        }
      delay(1000);
     
      }


    // Delay a little bit to avoid bouncing
    delay(50);
//  }
  // save the current state as the last state,
  //for next time through the loop
  // lastreceiverState = receiverState;



}

