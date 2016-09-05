/* @file   keypad-single-analog.ino
|| @version 0.1
|| @author Paul Vivier
|| @contact arduino@vivier.net

|| Inspired and heavily influenced by DynamicKeypad by Mark Stanley

*/

int keyPressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyPadValue = 0;   // value read from the keyboard

int riseThreshold = 3;  // Rise on the slope for initiating voltage ramp up when a keyPressed
int keyLastPressed = -1;

// Range for analog voltage for various keys. Adjust by modifying resistors. 
char keyNames[] = {'1'  ,'2'  ,'3'  ,'4'  ,'5'  ,'6'  ,'7'  ,'8'  ,'9'  ,'0'  ,'*'  ,'#'};
int keyLows[]  = {730  ,680  ,200  ,570  ,456  ,180  ,390  ,340  ,156  ,119  ,126  ,83};
int keyHighs[] = {890  ,702  ,213  ,588  ,485  ,189  ,402  ,349  ,163  ,125  ,131  ,89};


void setup(){
  Serial.begin(9600);  //hardware serial to PC  

}


void loop(){


//    Serial.print("keyPadValue:");
//    Serial.println(keyPadValue);

// Stabalize Analog Reading
// Quick loop to see if the keyPadValue is rising dramatically. If so, break the loop. 
   while (keyPadValue > 75) {
   keyLastPressed = keyPadValue; 
   delay (30); 
   keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
      if (keyLastPressed + riseThreshold > keyPadValue){break;}  
//      Serial.println("Still Rising");
   }

   while (keyPadValue < 75) {
   keyLastPressed = -1; 
   delay (30); 
//   Serial.println("Reset lastKeyboardValue");
   keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)

   }

// Once the number has stablized, see what the reading is. 
    for (int i = 0; i < 12; i++){
    // let the initial voltage reading stabilize, especially because of how Keypad #1 is wired.
    // If bad readings around #1 persist, you may need to time actual the ramp up and match delay.
    // Also may need a larger(?) capacitor.

//    Serial.print("keyPadValue:");
//    Serial.println(keyPadValue);
    // keyPadValue should have stabalized by now. 
    // Match number printed 
    
     
    // Take your reading now, sir
    // Find the key that was pressed by matching the range.  
        while ((keyPadValue > keyLows[i]) && (keyPadValue < keyHighs[i])){
              keyPressed = keyNames[i];

              // If it's the first time seeing this keyName, print it. 
              if (keyLastPressed != keyPressed){
                Serial.print("Key Pressed:");
                Serial.println(keyNames[i]);
              }

              // Let keyPressed reset if keyPadValue drops below 25
                while (keyPadValue > 25){
               //   Serial.print("                     key:");
               //   Serial.println(keyNames[i]);
                  keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
                }
                
              keyLastPressed = keyPressed;
        }
    
    } // int i loop
          
    keyPadValue = analogRead(keyboardPin); // See if it's time to end the loop     



                    
} // void loop

      


//wait until is no longer being pressed.   
//   while (keyPadValue > 25) {
//     delay (100);

//     Serial.print("Button being held down:");
//     Serial.println(keyPressed);
//     Serial.print("Analog value:");
//     Serial.println(keyPadValue);
//     keyPadValue = analogRead(keyboardPin); // See if it's time to end the loop
//   }          
     
   
 //  Serial.println(keyPadValue);
 //  Serial.println(keyPressed);      // print the value back to the Serial view window on your PC
//   delay(50);                     // wait 1000 milliseconds before the next loop

//}

