/* @file   keypad-single-analog.ino
|| @version 0.1
|| @author Paul Vivier
|| @contact arduino@vivier.net


*/
char keyPressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyPadValue = 0;   // value read from the keyboard

int riseThreshold = 3;  // Rise on the slope for initial voltage ramp up when a keyPressed
int keyLastPressed = -1;


// Range for analog voltage for various keys. Adjust by modifying resistors. 
char keyNames[] = {'1'  ,'2'  ,'3'  ,'4'  ,'5'  ,'6'  ,'7'  ,'8'  ,'9'  ,'0'  ,'*'  ,'#'};
int keyLows[]  = {730  ,680  ,200  ,570  ,456  ,180  ,390  ,340  ,156  ,119  ,126  ,83};
int keyHighs[] = {890  ,702  ,213  ,588  ,485  ,189  ,402  ,349  ,163  ,125  ,131  ,89};

char numberToCall[11];
int numberIndex = 0;


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
     
    // Take your reading now, sir
    // Find the key that was pressed by matching the range.  
        while ((keyPadValue > keyLows[i]) && (keyPadValue < keyHighs[i])){
              numberToCall[numberIndex] = keyNames[i]; // determine what keyName in the mapping matches your volt range

    
              // Since we're making rapid loops and continuing to read the voltage
              // this checks to see if you still have the same key pressed down that you
              // had presssed a few hundred miliseconds ago. 
              if (keyLastPressed != keyPressed){

                // if it's not the same key we've seen before then this is the
                // number to use
//                numberToCall[numberIndex] = keyPressed; // take key pressed and put it into the number to call buffer
//                Serial.print("keyPressed:");
//                Serial.println(keyPressed);

//                Serial.print("numberToCall:");
                Serial.print(numberToCall[numberIndex]);
//                Serial.print("numberIndex: ");
//                Serial.println(numberIndex);
                               
                ++numberIndex;
         
         //       Serial.print("Dialing:");

         //       Serial.println(numberToCall);
         //       Serial.print("Length of numberToCall: ");
         //       Serial.println(numberToCall.length());
              }
            

              // Keeps keyPressed from getting resampled while button is still pressed.
                while (keyPadValue > 75){
               //   Serial.print("                     key:");
               //   Serial.println(keyNames[i]);
                  keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
                }

              // 
              keyLastPressed = keyPressed;
              
        
        } // while loop

    
    } // int i loop


    if (numberToCall[9]) {
     Serial.println();
     Serial.print("Calling: ");
     Serial.println(numberToCall);
//    numberToCall[0] = (char)0;
//     numberIndex = (char)0;  

//     Serial.println("Clearing numberToCall Array: ");
     // defect - numberToCall isn't getting 'zeroed'. 
      for( int i = 0; i < sizeof(numberToCall);  ++i ){
//         Serial.print("int i: ");
//         Serial.println(i);
         numberToCall[i] = (char)0;  
         numberIndex = (char)0;  
//         Serial.println(numberToCall[i]);
        } 
  
      }
          
    keyPadValue = analogRead(keyboardPin); // See if it's time to end the loop     
                  
} 


