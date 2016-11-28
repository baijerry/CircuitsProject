#include <SoftwareSerial.h>

//pin stuff
int pin_channel1 = A1;
int pin_channel2 = A2;
int pin_null= 10;
int pin_URL = 11;
SoftwareSerial serial_URL (pin_URL, pin_null); //Rx, Tx (TX not used)

//defs
enum MODE {URL, CHANNEL} mode;

unsigned int analog1;
unsigned int analog2;
bool readflag = false;

int trigV = 900; //trigger analog reading
int trigTime = 500; //trigger time length since last trigger reading

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
       analog1 = analogRead(1);
       analog2 = analogRead(2);

        if (1){ //find when signal starts sending
          Serial.print(micros());
          Serial.print("\t\t");
          Serial.print(analog1);
          Serial.print("\t");
          Serial.print(analog2);
          Serial.println();
          delayMicroseconds(100);
        }
    }




    
}

