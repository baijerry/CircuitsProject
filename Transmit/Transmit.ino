#include <SoftwareSerial.h>

//Pin stuff
int pin_masterTX = 11;
int pin_slaveRX = 10;
int pin_URL = 6;
int pin_null = 5;
int pin_waveAB = 3;
SoftwareSerial serial_MasterSlave(pin_slaveRX, pin_masterTX); //RX, TX
SoftwareSerial serial_URL (pin_null, pin_URL); //Rx, Tx (RX not used)

//defs
enum MODE {MASTER, SLAVE} mode;
int channel1 = 5425; //Hz
int channel2 = 420; //Hz

//function declares
void sendWaveA(int freq);
void sendWaveB(int freq);

void setup() {
  Serial.begin(4800); //local
  serial_URL.begin(9600); //for URL transmission
  serial_MasterSlave.begin(11920); //to ping slave (needs to be fast)

  pinMode(pin_waveAB, OUTPUT);
  
  mode = SLAVE; //default
  Serial.println("Mode: Slave");
}

void loop() {
   //settings change
    if (Serial.available()){
        String input = Serial.readString();
        input.toLowerCase();

        if (input.equals("master")) {
            Serial.println("Mode: Master");
            mode = MASTER;
        }

        if (input.equals("slave")) {
            Serial.println("Mode: Slave");
            mode = SLAVE;
        }   

        if (mode==MASTER){
            if (input.equals("url")){
                Serial.print("Input Url: ");
                while (!Serial.available()) {
                    //wait
                }
                String url = Serial.readString();
                Serial.print("Sending Url: ");
                Serial.println(url);

                char buf[50];
                url.toCharArray(buf, 50); 
                
                for (int i = 0; i < 120; i++){ //sends url 10 times, once a second
                    serial_URL.write(buf); 
                    delay(1000);
                }
                
            } else if  (input.equals("ab")){
                //ping slave to run B
                serial_MasterSlave.write('b');
                //run A on channel 1
                sendWaveA(channel1);
            } else if  (input.equals("ba")){
                //ping slave to run A
                serial_MasterSlave.write('a');
                //run B on channel 1
                sendWaveB(channel1);

            } else if (!input.equals("master")){
                Serial.println("Not valid. Please enter MASTER, SLAVE, URL, AB, or BA");
            }
        }
    }

    if (mode==SLAVE){
        //slave
        if (serial_MasterSlave.available()){
      
            //read letter
            char letter = serial_MasterSlave.read();
            Serial.print("Received letter ");
            Serial.println(letter);
      
            //send on channel2
            if (letter == 'a') {
                sendWaveA(channel2);
            }
            if (letter == 'b') {
                sendWaveB(channel2);
            }
        }
    }
}

void sendWaveA(int freq) {
    Serial.print("Sending wave A at ");
    Serial.print(freq);
    Serial.println(" Hz");
    
    tone(pin_waveAB, freq, 2000); //todo make it into pattern A
}

void sendWaveB(int freq){
    Serial.print("Sending wave B at ");
    Serial.print(freq);
    Serial.println(" Hz");

    tone(pin_waveAB, freq, 1000); //todo make it into pattern B
}
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
