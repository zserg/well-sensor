#include <SoftwareSerial.h>
#include <NewPing.h>

#define RS485_RI_PIN 3  // RX
#define RS485_DO_PIN 4  // TX 
#define RS485_DE_PIN 5  // DE/RE#

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define RELAY_CTRL_PIN 8 

SoftwareSerial mySerial(RS485_RI_PIN, RS485_DO_PIN); // RX, TX
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  pinMode(RS485_DE_PIN, OUTPUT);
  pinMode(RELAY_CTRL_PIN, OUTPUT);

  toRx();
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Slave started!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800); 
  Serial.print(measure()); // Send ping, get distance in cm and print result (0 = outside set distance range)

}

void loop() { // run over and over
 if(mySerial.available()){
    int rx = mySerial.read();
    if((char) rx == '1'){
      Serial.write("ON");
      digitalWrite(RELAY_CTRL_PIN, HIGH);
    }
    if((char) rx == '0'){
      Serial.write("OFF");
      digitalWrite(RELAY_CTRL_PIN, LOW);
    }
    delay(10);
    toTx();
    delay(10);
    //mySerial.write(rx);
    mySerial.print(measure());
    mySerial.print(":");
    mySerial.println(digitalRead(RELAY_CTRL_PIN));
    delay(10);
    toRx();        
  }
  toRx();    

}

int measure(){
  return sonar.ping_cm();
}

void toTx() {
  digitalWrite(RS485_DE_PIN, HIGH);
}

void toRx() {
  digitalWrite(RS485_DE_PIN, LOW);
}

