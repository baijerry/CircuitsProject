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

        if (analog1 > trig && analog2 > trigV){ //find when signal starts sending
          readflag = true;
          unsigned int read1 = 0;
          unsigned int read2 = 0;
          while (readflag) {
            read1 = analogRead(1);
            read2 = analogRead(2);

            Serial.print(analog1);
            Serial.print("\t");
            Serial.print(analog2);
            Serial.println();

            if (read1 > trigV)
              Ch1LastTrig = millis();

            if (read2 > trigV)
              Ch2LastTrig = millis();

            if (millis() - Ch1LastTrig > ) {
              
            }

            if (millis() - Ch2LastTrig > ) {
            
            
            }
            
            //something something 
            readflag = false;
          }

          //process shit 
         
        }

    }




    
}

