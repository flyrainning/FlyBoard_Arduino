#ifndef FBSERIAL_h
#define FBSERIAL_h

/*
AltSoftSerial pins

__AVR_ATmega328P__
#define INPUT_CAPTURE_PIN		 8 // receive
#define OUTPUT_COMPARE_A_PIN		 9 // transmit
#define OUTPUT_COMPARE_B_PIN		10 // unusable PWM

__AVR_ATmega2560__
#define INPUT_CAPTURE_PIN		48 // receive
#define OUTPUT_COMPARE_A_PIN		46 // transmit
#define OUTPUT_COMPARE_B_PIN		45 // unusable PWM
#define OUTPUT_COMPARE_C_PIN		44 // unusable PWM
*/

#include "Arduino.h"
#include <SoftwareSerial.h>

#include "AltSoftSerial.h"


class FBSerial
{
	private:
    enum FBSerial_type{Hard,Soft,Alt} type=Hard;
    SoftwareSerial* SS=NULL;
    HardwareSerial* HS=NULL;
		AltSoftSerial* AS=NULL;

	public:

		FBSerial();
		~FBSerial();
		FBSerial(SoftwareSerial &_S);
		FBSerial(HardwareSerial &_S);
		FBSerial(AltSoftSerial &_S);
		FBSerial(int RX,int TX,long baudrate=9600);
		FBSerial(long baudrate);
		void bind(SoftwareSerial &_S);
		void bind(HardwareSerial &_S);
		void bind(AltSoftSerial &_S);
		void bind(int RX,int TX,long baudrate=9600);
		void bind(long baudrate=9600);
		void bindAlt();
		void bindAlt(long baudrate);




		void begin(long speed);
		bool listen();
		void end();
		bool isListening();
		bool stopListening();
		bool overflow();
		int peek();

		size_t write(uint8_t byte);
		int read();
		int available();
		void flush();

		size_t print(const __FlashStringHelper *);
		size_t print(const String &);
		size_t print(const char[]);
		size_t print(char);
		size_t print(unsigned char, int = DEC);
		size_t print(int, int = DEC);
		size_t print(unsigned int, int = DEC);
		size_t print(long, int = DEC);
		size_t print(unsigned long, int = DEC);
		size_t print(double, int = 2);
		size_t print(const Printable&);

		size_t println(const __FlashStringHelper *);
		size_t println(const String &s);
		size_t println(const char[]);
		size_t println(char);
		size_t println(unsigned char, int = DEC);
		size_t println(int, int = DEC);
		size_t println(unsigned int, int = DEC);
		size_t println(long, int = DEC);
		size_t println(unsigned long, int = DEC);
		size_t println(double, int = 2);
		size_t println(const Printable&);
		size_t println(void);


};

#endif
