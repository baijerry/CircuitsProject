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

#include <SoftwareSerial.h>

SoftwareSerial serial_MasterSlave(10, 11); //RX, TX
SoftwareSerial serial_URL (5, 6); //Rx, Tx (5 not used)

enum MODE {MASTER, SLAVE};
MODE mode = SLAVE; //default

void setup() {
  Serial.begin(4800);
  mySerial.begin(9600); //for URL transmission
}

void loop() {
}
  //settings change
  if (Serial.available()){
    string input = Serial.readString();
    input.toLowerCase();
    
    if (input.equals("master")
      mode = MASTER;

    if (input.equals("slave")
      mode = SLAVE;
  }
  
  //main
  if (mode=MASTER)
    
  {
  } else {
    //slave
    if
  }
}

