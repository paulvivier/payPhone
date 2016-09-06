/* @file   keypad-single-analog.ino
|| @version 0.1
|| @author Paul Vivier
|| @contact arduino@vivier.net
*/


    int keyPressed = 0;
    int keyboardPin = 0;    // Analog input pin that the keypad is attached to
    int keyPadValue = 0;   // value read from the keyboard
    
    int riseThreshold = 3;  // Rise on the slope for initial voltage ramp up when a keyPressed
    int keyLastPressed = -1;
    
    // Range for analog voltage for various keys. Adjust by modifying resistors. 
    char keyNames[] = {'1'  ,'2'  ,'3'  ,'4'  ,'5'  ,'6'  ,'7'  ,'8'  ,'9'  ,'0'  ,'*'  ,'#'};
    int keyLows[]  = {730  ,680  ,200  ,570  ,456  ,180  ,390  ,340  ,156  ,119  ,126  ,83};
    int keyHighs[] = {890  ,702  ,213  ,588  ,485  ,189  ,402  ,349  ,163  ,125  ,131  ,89};
    
    String numberToCall = "";


void keyboardSetup(){



}

void keyboardAnalog(){

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
     
    // Take your reading now, sir
    // Find the key that was pressed by matching the range.  
        while ((keyPadValue > keyLows[i]) && (keyPadValue < keyHighs[i])){
              keyPressed = keyNames[i];

              // If it's the first time seeing this keyName, print it. 
              if (keyLastPressed != keyPressed){
         //       Serial.print("Key Pressed:");
         //       Serial.println(keyNames[i]);
                Serial.print("Dialing:");
                numberToCall.concat(keyNames[i]);
                Serial.println(numberToCall);
         //       Serial.print("Length of numberToCall: ");
         //       Serial.println(numberToCall.length());
              }
            

              // Keeps keyPressed from getting resampled while button is still pressed.
                while (keyPadValue > 75){
               //   Serial.print("                     key:");
               //   Serial.println(keyNames[i]);
                  keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
                }
                
              keyLastPressed = keyPressed;
        
        } // while loop
    
    } // int i loop

    if (numberToCall.length() == 10) {
     Serial.print("Calling: ");
     Serial.println(numberToCall);
     numberToCall = "";
     
    }
          
    keyPadValue = analogRead(keyboardPin); // See if it's time to end the loop     

 
}

