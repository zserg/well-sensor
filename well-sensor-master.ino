#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  pinMode(5, OUTPUT);
  toTx();

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");
  

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
}

void loop() { // run over and over
  if(Serial.available()){
    toTx();    
    mySerial.write(Serial.read());
    delay(10);        
    toRx();    
  }

  if(mySerial.available()){
     int rx = mySerial.read();
    Serial.write(rx);        
  }

}

void toTx() {
  digitalWrite(5, HIGH);
}

void toRx() {
  digitalWrite(5, LOW);
}
