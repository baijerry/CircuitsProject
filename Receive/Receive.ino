#include <SoftwareSerial.h>

//pin stuff
int pin_channel1 = A1;
int pin_channel2 = A2;
int pin_null= 10;
int pin_URL = 11;
SoftwareSerial serial_URL (pin_URL, pin_null); //Rx, Tx (TX not used)

//defs
enum MODE {URL, CHANNEL} mode;
bool count_ch1 = false;
bool count_ch2 = false;
bool printflag = false;
int trig_v = 900;

int start_time = 0;
int ch1_lastTrig = 0;
int ch2_lastTrig = 0;
int ch1_length = 0;
int ch2_length = 0;


//func declares

void setup() {
    Serial.begin(4800); //local
    serial_URL.begin(9600); //for URL transmission
    
    Serial.println("Mode: URL");
    mode = URL; //default
}

void loop() {
    //settings change
    if (Serial.available()){
        String input = Serial.readString();
        input.toLowerCase();

        if (input.equals("url")) {
            Serial.println("");
            Serial.println("Mode: URL");
            mode = URL;
        }

        else if (input.equals("channel")) {
            Serial.println("");
            Serial.println("Mode: Channel");
            mode = CHANNEL;
        } 

        else {
            Serial.println("Invalid input, please choose URL or CHANNEL");
        } 
    }
    
    //URL mode
    if (mode == URL) {
        if (serial_URL.available()) {
            Serial.write(serial_URL.read());
        }
    }
    
    //CHANNEL mode
    if (mode == CHANNEL) {
        if (!count_ch1 && !count_ch2 && analogRead(pin_channel1) < trig_v && analogRead(pin_channel2) < trig_v) {
          //start count
          Serial.println(analogRead(pin_channel1));
          start_time = micros();
          count_ch1= true;
          count_ch2 = true;
          printflag = true;
        }

        if (count_ch1 && analogRead(pin_channel1) > trig_v ) { //no signal
          ch1_lastTrig = micros();
        }

        if (count_ch2 && analogRead(pin_channel2) > trig_v ) { //no signal
          ch2_lastTrig = micros();
        }

        if (count_ch1 && (micros() - ch1_lastTrig) > 1000 ) { //last time triggered was more than 1000 microseconds
          ch1_length = start_time - ch1_lastTrig;
          count_ch1 = false;
        }

        if (count_ch2 && (micros() - ch2_lastTrig) > 1000 ) { //last time triggered was more than 1000 microseconds
          ch2_length = start_time - ch2_lastTrig;
          count_ch2 = false;
        }

        if (printflag && !count_ch1 && !count_ch2) { //both signals done sending
          if (ch1_length > ch2_length) {
            Serial.println("Channel 1 received A.");
            Serial.println("Channel 2 received B.");
            Serial.println("");
          }
          else 
          {
            Serial.println("Channel 1 received B.");
            Serial.println("Channel 2 received A.");
            Serial.println("");
          }
          printflag = false;
        }
    }




    
}

