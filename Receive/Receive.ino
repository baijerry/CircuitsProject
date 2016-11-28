#include <SoftwareSerial.h>

//pin stuff
int pin_channel1 = 1;
int pin_channel2 = 2;
int pin_null= 10;
int pin_URL = 11;
SoftwareSerial serial_URL (pin_URL, pin_null); //Rx, Tx (TX not used)

//defs
enum MODE {URL, CHANNEL} mode;
unsigned int Ch1LastTrig;
unsigned int Ch2LastTrig;
unsigned int Ch1FinishTime;
unsigned int Ch2FinishTime;
bool readflag = false;
bool Ch1FinishedFlag = true;
bool Ch2FinishedFlag = true;

//trigger analog reading
int trigV = 900; 
//trigger time length since last trigger reading
int trigTime = 527434; //us, determined experimentally (3*avgsteplengthof420hz)

//func declares

void setup() {
    Serial.begin(4800); //local
    serial_URL.begin(9600); //for URL transmission
    
    Serial.println("Mode: URL");
    mode = CHANNEL; //default
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
       analog1 = analogRead(pin_channel1);
       analog2 = analogRead(pin_channel2);

        if (analog1 > trigV && analog2 > trigV){ //find when signal starts sending
          readflag = true;
          unsigned int read1 = 0;
          unsigned int read2 = 0;
          Ch1LastTrig = micros();
          Ch2LastTrig = micros();
          while (readflag) {
            read1 = analogRead(1);
            read2 = analogRead(2);

            Serial.print(analog1);
            Serial.print("\t");
            Serial.print(analog2);
            Serial.println();

            if (read1 > trigV){
              Ch1LastTrig = micros();
              Serial.println("ch1 trig");
            }
            
            if (read2 > trigV){
              Ch2LastTrig = micros();
              Serial.println("ch1 trig");
            }
            
            Serial.print(">>>>");
             Serial.println(micros() - Ch1LastTrig);
             
            if (micros() - Ch1LastTrig > trigTime) {
              //channel 1 finished
              Ch1FinishedFlag = true;
              Ch1FinishTime = micros();
              Serial.println("Ch1 done");
            }

            if (micros() - Ch2LastTrig > trigTime) {
              //channel 2 finished
              Ch2FinishedFlag = true;
              Ch2FinishTime = micros();
              Serial.println("Ch2 done");
            }
            
            //exit loop
            if (Ch1FinishedFlag || Ch2FinishedFlag){
              readflag = false;
              Ch1FinishedFlag = false;
              Ch2FinishedFlag = false; 
            }
          }
/*
          //process shit 
          if (Ch2FinishTime > Ch1FinishTime) {
            //Ch1 finished first
            Serial.println("Channel_1/Master: B");
            Serial.println("Channel_2/Slave: A");
          }
          else if (Ch2FinishTime < Ch1FinishTime) {
            //Ch2 finished first
            Serial.println("Channel_1/Master: A");
            Serial.println("Channel_2/Slave: B");
          }
          else 
          {
            Serial.println("Error");  
          }
    */
        delay(3000);
        }

    }
}

