#include <Arduino.h>
#include "flyboard.h"

FBSerial serial;

void setup() {


    FBSerial serial1;
    serial1.bind(Serial);
    serial1.begin(115200);
    serial.println("HardwareSerial");

    FBSerial serial2(Serial);
    serial1.begin(115200);
    serial.println("HardwareSerial");


    FBSerial serial3;
    serial3.bind(3,4,9600);
    serial3.println("SoftwareSerial RX 3,TX 4");

    SoftwareSerial softs(3,4);
    softs.begin(115200);
    FBSerial serial4;
    serial4.bind(softs);
    serial4.println("SoftwareSerial");


    FBSerial serial5;
    serial5.bindAlt(9600);
    serial5.println("AltSoftSerial");


}

void loop() {

  delay(500);

}
