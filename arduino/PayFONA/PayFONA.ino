/*

Since the behavior is to mimic a standard landline as much as possible, 
We're goint to start with a basic switch. 

On = ready to dial
Off = ready to recieve a call

 */

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
        // get call status
        Serial.println("*** ******** ******* ");
        Serial.println("Call Status: ");
        int8_t callstat = fona.getCallStatus();
        receiverState = digitalRead(receiverPin);
        Serial.println("Receiver Status: ");
        Serial.print(receiverPin);
        switch (callstat) {
          case 0: Serial.println(F("Ready")); 
                // wait for the receiverState to change. 

                if (receiverState == HIGH) {
                  // if the current state is HIGH then the receiver
                  // went from off to on:
                  Serial.println("ON");
                  digitalWrite(ledPin, HIGH);
                }
                else if (receiverState == LOW) {
                  // if the current state is LOW then the receiver
                  // went from on to off:
                  Serial.println("OFF");
                  digitalWrite(ledPin, LOW);

                }

                
                break;
          
          case 1: Serial.println(F("Could not get status")); break;
          case 3: Serial.println(F("Ringing (incoming)")); 

                // wait for the receiverState to change. 

                if (receiverState == HIGH) {
                  // if the current state is HIGH then the receiver
                  // went from off (handset placed) to on (handset removed):
                    // pick up!
                    if (! fona.pickUp()) {
                      Serial.println(F("Failed to pickup"));
                    } else {
                      Serial.println(F("Call picked up"));
                    }
//                  Serial.println("ON");
                  digitalWrite(ledPin, HIGH);
                  
                }
                else if (receiverState == LOW) {
                  // if the current state is LOW then the receiver
                  // went from on to off:
                  Serial.println("OFF");
                  digitalWrite(ledPin, LOW);


                }
                break; 

                
          case 4: Serial.println(F("Ringing/in progress (outgoing)")); 
          
          
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

