int keyPressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard

int padname = 0 ;
int intLOW = 0;
int intHIGH = 0;

// Range for analog voltage for various keys. Adjust by modifying resistors. 
char keyNames[] = {'1'  ,'2'  ,'3'  ,'4'  ,'5'  ,'6'  ,'7'  ,'8'  ,'9'  ,'0'  ,'*'  ,'#'};
int keyLows[]  = {790  ,680  ,200  ,570  ,465  ,180  ,390  ,340  ,156  ,119  ,126  ,83};
int keyHighs[] = {890  ,689  ,210  ,575  ,475  ,189  ,399  ,349  ,163  ,124  ,129  ,89};


void setup(){
  Serial.begin(9600);  //hardware serial to PC  

}


void loop(){
    keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)

   while (keyboardValue > 25) {

    for (int i = 0; i < 12; i++){
    // let the initial voltage reading stabilize, especially because of how Keypad #1 is wired.
    // If bad readings around #1 persist, you may need to time actual the ramp up and match delay.
    // Also may need a larger(?) capacitor.
         delay(50);

     // Find the range of the actual value that has pressed.  
       if ((keyboardValue > keyLows[i]) && (keyboardValue < keyHighs[i])){
        keyPressed = keyNames[i];
        Serial.print("key:");
        Serial.println(keyNames[i]);
        delay(100);
        
        }
      //   delay(100);
      }
    keyboardValue = analogRead(keyboardPin); // See if it's time to end the loop     

    }          

                                 

//wait until is no longer being pressed.   
   while (keyboardValue > 25) {
//     delay (100);

     Serial.print("Button being held down:");
//     Serial.println(keyPressed);
//     Serial.print("Analog value:");
//     Serial.println(keyboardValue);
     keyboardValue = analogRead(keyboardPin); // See if it's time to end the loop
   }          
     
   
 //  Serial.println(keyboardValue);
 //  Serial.println(keyPressed);      // print the value back to the Serial view window on your PC
   delay(50);                     // wait 1000 milliseconds before the next loop

}

