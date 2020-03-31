/*
  An example for readig data from JSN-SR04T-2.0 20-600 cm Ultrasonic Waterproof Range Finder
  through Serial port.
  Created by Hamid Saffari @ Jan 2020. https://github.com/HamidSaffari/JSN-SR04T
  Released into the public domain.
  
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // (RX-pin, TX-pin)

void setup() {
	
  Serial.begin(9600);
  mySerial.begin(9600);// 8N1 as default.
  mySerial.setTimeout(100); // 100ms is enough for the module. default is 1000 milliseconds.
  
}

void loop() {

  mySerial.write(0x55); // start ping. call before readSerial(). in R27==120Kohm mode.
  int distance = readDistance_Serial();
	
  Serial.print(distance);
  Serial.print(" mm equal to ");
  Serial.print( distance * (1/25.4) ); // convert to inches.
  Serial.println(" in.");
 
  delay(350);
}

int readDistance_Serial() {
  byte serialData[5];
  int distance=0;
  while (mySerial.available()) {
    mySerial.read(); //it flushes the receive buffer.
  }
  if( mySerial.readBytes(serialData,4) > 0) {
	int sum = (serialData[0]+serialData[1]+serialData[2]) & 0x00FF;
	if(serialData[3]==sum){
		distance = ( ((int)serialData[1] << 8 ) + serialData[2]);
    }   
  }
  return distance;
}
