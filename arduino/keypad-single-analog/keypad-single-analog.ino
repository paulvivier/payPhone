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

// Set up buffer to hold the number to be called and an index to track length of the array
// (I'm sure there's a better way, but I don't know it yet).
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
   while (keyPadValue < 75) { // reset values once keypad is stop being pressed
     keyLastPressed = -1; 
     delay (30);
     keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
   }

// Once the number has stablized, see what the reading is. 
    for (int i = 0; i < 12; i++){
      
    // Take your reading now
    // Find the key that was pressed by matching the range.  
        while ((keyPadValue > keyLows[i]) && (keyPadValue < keyHighs[i])){
              // Is this the same key that was pressed a few miliseconds? 
              if (keyLastPressed != keyPressed){
                // Store key pressed into next available slot for number to call
                numberToCall[numberIndex] = keyNames[i];
                Serial.print(numberToCall[numberIndex]);                               
                ++numberIndex; 
              }
              
              // Keeps keyPressed from getting resampled while button is still pressed.
                while (keyPadValue > 75){
                  keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
                }

              keyLastPressed = keyPressed; // before leaving, hold on to the last valid keyPressed
              
        } // while loop
    } // int i loop


    // Once we have 10 digits in the array, we have a valid phone number.
    // Array index starts at 0.
    if (numberToCall[9]) {
     Serial.println();
     Serial.print("Calling: ");
     Serial.println(numberToCall);
      // Clearing arrays 
      for( int i = 0; i < sizeof(numberToCall);  ++i ){
         numberToCall[i] = (char)0;  
         numberIndex = (char)0;  
        } 
      }
          
    keyPadValue = analogRead(keyboardPin); // See if it's time to end the loop     
                  
} 


