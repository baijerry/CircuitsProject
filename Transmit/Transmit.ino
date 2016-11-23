/*
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Code dump:

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

mySerial.begin(9600);
Serial.begin(4800);

loop:
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

___________________________________
char rx_byte = 0;

  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
  
  if (rx_byte == 'a'){
    tone(11, 6000);
  }
  else if (rx_byte == 'b') {
    tone(11, 600);
//  }
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/


