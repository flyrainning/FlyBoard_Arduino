#include <Arduino.h>
#include "flyboard.h"

FBSerial serial;

void setup() {


  serial.bind(115200);
  serial.println("HardwareSerial");


  FBSerial serial1;
  serial1.bind(Serial);
  serial.println("HardwareSerial");

  FBSerial serial2;
  serial1.bind(3,4,9600);
  serial.println("SoftwareSerial RX 3,TX 4");

  FBSerial serial3;
  serial3.bindAlt(9600);
  serial.println("AltSoftSerial");



}

void loop() {

  delay(500);

}
