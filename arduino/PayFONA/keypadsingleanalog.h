/* @file   keypad-single-analog.ino
|| @version 1.0
|| @author Paul Vivier
|| @contact arduino@vivier.net

  The purpose of this partcular sketch was to integrate a keypad
  pulled from a payphone and use it again to integrated back into
  the PayFONA project.

  This sketch to main functions: 
    - Reads the voltage values from a 12 key keypad as it registers into a single analog input
    - Creates a buffer to store a 10 digit number with the intention of calling it.
      (I can probably break that function out later).
*/

char keyPressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyPadValue = 0;   // value read from the keyboard

int riseThreshold = 3;  // Rise on the slope for initial voltage ramp up when a keyPressed
int keyLastPressed = -1;

// Range for analog voltage for various keys. Adjust by modifying resistors. 
char keyNames[] = {'1'  ,'2'  ,'3'  ,'4'  ,'5'  ,'6'  ,'7'  ,'8'  ,'9'  ,'0'  ,'*'  ,'#'};
int keyLows[]  = {730  ,680  ,200  ,570  ,456  ,180  ,390  ,340  ,156  ,119  ,126  ,83};
int keyHighs[] = {930  ,704  ,215  ,588  ,485  ,189  ,404  ,352  ,163  ,125  ,131  ,89};

// Set up buffer to hold the number to be called and an index to track length of the array
// (I'm sure there's a better way, but I don't know it yet).
char numberToCall[11];
int numberIndex = 0;

/*  Uncomment to use as an .ino instaed of a .h
void setup(){
  Serial.begin(9600);  //hardware serial to PC  

}
void loop(){
  keyboardAnalog();  
}
*/

void keyboardAnalog(){

   while (keyPadValue > 75) {
//     This stabalizes the analog reading in the microseconds that it takes to press a button. 
//     Quick loop to see if the keyPadValue is rising dramatically. If so, break the loop and start over.

//     Serial.print("keyPadValue:");  // Uncomment to debug actual voltage value
//     Serial.println(keyPadValue);   // Uncomment to debug actual voltage value
       keyLastPressed = keyPressed; 
       delay (30); 
       keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
          if (keyLastPressed + riseThreshold > keyPadValue){Serial.println("Break these chains!"); break;}  
//     Serial.println("Still Rising");
   }


   
   while (keyPadValue < 75) { 
//    Reset values once keypad button has been released
//    Serial.print("keyPadValue:");  // Uncomment to debug actual voltage value
//    Serial.println(keyPadValue);  // Uncomment to debug actual voltage value
      keyLastPressed = -1; // reset the key last pressed
      delay (30);
      keyPadValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
   }

 
    for (int i = 0; i < 12; i++){
    // Once the number has stablized, lets Take a Reading! 
    // Find the key that was pressed by matching the volt range to the configuration mapped above.  
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
        } // while keypad volt range
    } // for number of keys to check

/* Put this in your main .ino file
   OR uncomment this in addition to loop above to 
   run this on it's own (as an .ino file). 

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
*/

          
    keyPadValue = analogRead(keyboardPin); // See if it's time to end the loop     
                  
} 


