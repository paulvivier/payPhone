//This sketch displays the values on a scale of 0-1023 that are generated when you press each key
//They should be similar to the values I have given in the Instructable 
//(allowing for small variations in tolerance of the resistors)




int keyboardPin = 0;    // Analog input pin that the keypad is attached to
 int keyboardValue = 0;   // value read from the keyboard


 void setup() {
   // initialize serial communications at 9600 bps:
   Serial.begin(9600); 

 }

 void loop() {
   keyboardValue = analogRead(keyboardPin); // read the pot value
  
   Serial.println(keyboardValue);      // print the value back to the serial view window on your PC
   delay(1000);                     // wait 1000 milliseconds before the next loop
 }


