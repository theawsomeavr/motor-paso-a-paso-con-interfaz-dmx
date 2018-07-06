// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialRecv.ino: Sample DMX application for retrieving 3 DMX values:
// address 1 (red) -> PWM Port 9
// address 2 (green) -> PWM Port 6
// address 3 (blue) -> PWM Port 5
// 
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// 
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// 28.12.2011 changed to channels 1..3 (RGB) for compatibility with the DmxSerialSend sample.
// 10.05.2012 added some lines to loop to show how to fall back to a default color when no data was received since some time.
// - - - - -

#include <DMXSerial.h>

// Constants for demo program

#define numvueltas 11 //cambia el numero de vueltas que va a dar el motor
int motor;
int a;


void setup () {
 // 
  
  // set some default values
  //DMXSerial.write(1, 80);

   
    pinMode(5,1);
  pinMode(4,1);
  pinMode(8,1);
    pinMode(10,0);
digitalWrite(10,1);
  while(digitalRead(10)==1){
    digitalWrite(5,0);
    digitalWrite(4,1);
delayMicroseconds(700);
  digitalWrite(4,0);
delayMicroseconds(700);
  }
  DMXSerial.init(DMXReceiver);


  // put your setup code here, to run once:

}

void motorpos(byte pos){
  int movepos=map(pos,0,255,0,200*numvueltas);
  while(motor>movepos){
      digitalWrite(5,0);
    digitalWrite(4,1);
delayMicroseconds(700);
  digitalWrite(4,0);
delayMicroseconds(700);
  motor--;
  }
    while(motor<movepos){
      digitalWrite(5,1);
    digitalWrite(4,1);
delayMicroseconds(700);
  digitalWrite(4,0);
delayMicroseconds(700);
    motor++;
  }
  
}


void loop() {
  // Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();


  if (lastPacket < 5000) {
  
    motorpos(DMXSerial.read(1));//el arduino va a leer el primer slider
    

  }  
}

// End.
