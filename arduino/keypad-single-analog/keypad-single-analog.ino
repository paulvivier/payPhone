/* @file   keypad-single-analog.ino
|| @version 0.1
|| @author Paul Vivier
|| @contact arduino@vivier.net

|| Inspired and heavily influenced by DynamicKeypad by Mark Stanley

*/

int keyPressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard

int padname = 0 ;
int intLOW = 0;
int intHIGH = 0;

// Range for analog voltage for various keys. Adjust by modifying resistors. 
char keyNames[] = {'1'  ,'2'  ,'3'  ,'4'  ,'5'  ,'6'  ,'7'  ,'8'  ,'9'  ,'0'  ,'*'  ,'#'};
int keyLows[]  = {730  ,680  ,200  ,570  ,456  ,180  ,390  ,340  ,156  ,119  ,126  ,83};
int keyHighs[] = {890  ,702  ,213  ,588  ,479  ,189  ,402  ,349  ,163  ,125  ,131  ,89};


void setup(){
  Serial.begin(9600);  //hardware serial to PC  

}


void loop(){
    keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)

   while (keyboardValue > 75) {

    for (int i = 0; i < 12; i++){
    // let the initial voltage reading stabilize, especially because of how Keypad #1 is wired.
    // If bad readings around #1 persist, you may need to time actual the ramp up and match delay.
    // Also may need a larger(?) capacitor.

    Serial.print("keyboardValue:");
    Serial.println(keyboardValue);
     // Find the range of the actual value that has been pressed.  
       if ((keyboardValue > keyLows[i]) && (keyboardValue < keyHighs[i])){
          keyPressed = keyNames[i];
//          int keyPressedLast = keyPressed;
          Serial.print("                              key:");
          Serial.println(keyNames[i]);
//          delay(50);
          }          
        }
      //   delay(100);

    keyboardValue = analogRead(keyboardPin); // See if it's time to end the loop     
      
      }

    }          



//wait until is no longer being pressed.   
//   while (keyboardValue > 25) {
//     delay (100);

//     Serial.print("Button being held down:");
//     Serial.println(keyPressed);
//     Serial.print("Analog value:");
//     Serial.println(keyboardValue);
//     keyboardValue = analogRead(keyboardPin); // See if it's time to end the loop
//   }          
     
   
 //  Serial.println(keyboardValue);
 //  Serial.println(keyPressed);      // print the value back to the Serial view window on your PC
//   delay(50);                     // wait 1000 milliseconds before the next loop

//}

