#include "FBSerial.h"

FBSerial::FBSerial() {

}
FBSerial::FBSerial(SoftwareSerial &_S) {
  bind(_S);
}
FBSerial::FBSerial(HardwareSerial &_S) {
  bind(_S);
}
FBSerial::FBSerial(AltSoftSerial &_S) {
  bind(_S);
}
FBSerial::FBSerial(int RX,int TX,long baudrate) {
  bind(RX,TX,baudrate);
}
FBSerial::FBSerial(long baudrate) {
  bind(baudrate);
}
FBSerial::~FBSerial() {
  // delete SS;
  // SS=NULL;
  // delete HS;
  // HS=NULL;
}

void FBSerial::bind(SoftwareSerial &_S) {
  SS=&_S;
  type=Soft;
}
void FBSerial::bind(HardwareSerial &_S) {
  HS=&_S;
  type=Hard;
}
void FBSerial::bind(AltSoftSerial &_S) {
  AS=&_S;
  type=Alt;
}
void FBSerial::bind(int RX,int TX,long baudrate) {
  SS=new SoftwareSerial(RX,TX);
  SS->begin(baudrate);
  type=Soft;
}
void FBSerial::bind(long baudrate) {
  HS=&Serial;
  type=Hard;
  begin(baudrate);
}
void FBSerial::bindAlt() {
  AS=new AltSoftSerial();
  type=Alt;
}
void FBSerial::bindAlt(long baudrate) {
  bindAlt();
  AS->begin(baudrate);
}
void FBSerial::begin(long speed) {
  switch (type) {
    case Hard:
      HS->begin(speed);
      break;
    case Soft:
      SS->begin(speed);
      break;
    case Alt:
      AS->begin(speed);
      break;
  }

}
bool FBSerial::listen() {
  switch (type) {
    case Hard:
      return false;
      break;
    case Soft:
      return SS->listen();
      break;
    case Alt:
      return AS->listen();
      break;
  }

}
void FBSerial::end() {
  switch (type) {
    case Hard:
      HS->end();
      break;
    case Soft:
      SS->end();
      break;
    case Alt:
      AS->end();
      break;
  }
}
bool FBSerial::isListening() {
  switch (type) {
    case Hard:
      return true;
      break;
    case Soft:
      return SS->isListening();
      break;
    case Alt:
      return AS->isListening();
      break;
  }
}
bool FBSerial::stopListening() {
  switch (type) {
    case Hard:
      return true;
      break;
    case Soft:
      return SS->stopListening();
      break;
    case Alt:
      return true;
      break;
  }

}
bool FBSerial::overflow() {
  switch (type) {
    case Hard:
      return true;
      break;
    case Soft:
      return SS->overflow();
      break;
    case Alt:
      return AS->overflow();
      break;
  }

}
int FBSerial::peek() {
  switch (type) {
    case Hard:
      return HS->peek();
      break;
    case Soft:
      return SS->peek();
      break;
    case Alt:
      return AS->peek();
      break;
  }

}
size_t FBSerial::write(uint8_t byte) {
  switch (type) {
    case Hard:
      return HS->write(byte);
      break;
    case Soft:
      return SS->write(byte);
      break;
    case Alt:
      return AS->write(byte);
      break;
  }

}
int FBSerial::read() {
  switch (type) {
    case Hard:
      return HS->read();
      break;
    case Soft:
      return SS->read();
      break;
    case Alt:
      return AS->read();
      break;
  }
}
int FBSerial::available() {
  switch (type) {
    case Hard:
      return HS->available();
      break;
    case Soft:
      return SS->available();
      break;
    case Alt:
      return AS->available();
      break;
  }
}
void FBSerial::flush() {
  switch (type) {
    case Hard:
      return HS->flush();
      break;
    case Soft:
      return SS->flush();
      break;
    case Alt:
      return AS->flush();
      break;
  }
}
//print
size_t FBSerial::print(const __FlashStringHelper *ifsh) {
  switch (type) {
    case Hard:
      return HS->print(ifsh);
      break;
    case Soft:
      return SS->print(ifsh);
      break;
    case Alt:
      return AS->print(ifsh);
      break;
  }
}
size_t FBSerial::print(const String &s) {
  switch (type) {
    case Hard:
      return HS->print(s);
      break;
    case Soft:
      return SS->print(s);
      break;
    case Alt:
      return AS->print(s);
      break;
  }
}
size_t FBSerial::print(const char str[]) {
  switch (type) {
    case Hard:
      return HS->print(str);
      break;
    case Soft:
      return SS->print(str);
      break;
    case Alt:
      return AS->print(str);
      break;
  }
}
size_t FBSerial::print(const char str) {
  switch (type) {
    case Hard:
      return HS->print(str);
      break;
    case Soft:
      return SS->print(str);
      break;
    case Alt:
      return AS->print(str);
      break;
  }
}
size_t FBSerial::print(unsigned char c, int f) {
  switch (type) {
    case Hard:
      return HS->print(c,f);
      break;
    case Soft:
      return SS->print(c,f);
      break;
    case Alt:
      return AS->print(c,f);
      break;
  }
}
size_t FBSerial::print(int c, int f) {
  switch (type) {
    case Hard:
      return HS->print(c,f);
      break;
    case Soft:
      return SS->print(c,f);
      break;
    case Alt:
      return AS->print(c,f);
      break;
  }
}
size_t FBSerial::print(unsigned int c, int f) {
  switch (type) {
    case Hard:
      return HS->print(c,f);
      break;
    case Soft:
      return SS->print(c,f);
      break;
    case Alt:
      return AS->print(c,f);
      break;
  }
}
size_t FBSerial::print(long c, int f) {
  switch (type) {
    case Hard:
      return HS->print(c,f);
      break;
    case Soft:
      return SS->print(c,f);
      break;
    case Alt:
      return AS->print(c,f);
      break;
  }
}
size_t FBSerial::print(unsigned long c, int f) {
  switch (type) {
    case Hard:
      return HS->print(c,f);
      break;
    case Soft:
      return SS->print(c,f);
      break;
    case Alt:
      return AS->print(c,f);
      break;
  }
}
size_t FBSerial::print(double c, int f) {
  switch (type) {
    case Hard:
      return HS->print(c,f);
      break;
    case Soft:
      return SS->print(c,f);
      break;
    case Alt:
      return AS->print(c,f);
      break;
  }
}
size_t FBSerial::print(const Printable &c) {
  switch (type) {
    case Hard:
      return HS->print(c);
      break;
    case Soft:
      return SS->print(c);
      break;
    case Alt:
      return AS->print(c);
      break;
  }
}
//println
size_t FBSerial::println(const __FlashStringHelper *ifsh) {
  switch (type) {
    case Hard:
      return HS->println(ifsh);
      break;
    case Soft:
      return SS->println(ifsh);
      break;
    case Alt:
      return AS->println(ifsh);
      break;
  }
}
size_t FBSerial::println(const String &s) {
  switch (type) {
    case Hard:
      return HS->println(s);
      break;
    case Soft:
      return SS->println(s);
      break;
    case Alt:
      return AS->println(s);
      break;
  }
}
size_t FBSerial::println(const char str[]) {
  switch (type) {
    case Hard:
      return HS->println(str);
      break;
    case Soft:
      return SS->println(str);
      break;
    case Alt:
      return AS->println(str);
      break;
  }
}
size_t FBSerial::println(const char str) {
  switch (type) {
    case Hard:
      return HS->println(str);
      break;
    case Soft:
      return SS->println(str);
      break;
    case Alt:
      return AS->println(str);
      break;
  }
}
size_t FBSerial::println(unsigned char c, int f) {
  switch (type) {
    case Hard:
      return HS->println(c,f);
      break;
    case Soft:
      return SS->println(c,f);
      break;
    case Alt:
      return AS->println(c,f);
      break;
  }
}
size_t FBSerial::println(int c, int f) {
  switch (type) {
    case Hard:
      return HS->println(c,f);
      break;
    case Soft:
      return SS->println(c,f);
      break;
    case Alt:
      return AS->println(c,f);
      break;
  }
}
size_t FBSerial::println(unsigned int c, int f) {
  switch (type) {
    case Hard:
      return HS->println(c,f);
      break;
    case Soft:
      return SS->println(c,f);
      break;
    case Alt:
      return AS->println(c,f);
      break;
  }
}
size_t FBSerial::println(long c, int f) {
  switch (type) {
    case Hard:
      return HS->println(c,f);
      break;
    case Soft:
      return SS->println(c,f);
      break;
    case Alt:
      return AS->println(c,f);
      break;
  }
}
size_t FBSerial::println(unsigned long c, int f) {
  switch (type) {
    case Hard:
      return HS->println(c,f);
      break;
    case Soft:
      return SS->println(c,f);
      break;
    case Alt:
      return AS->println(c,f);
      break;
  }

}
size_t FBSerial::println(double c, int f) {
  switch (type) {
    case Hard:
      return HS->println(c,f);
      break;
    case Soft:
      return SS->println(c,f);
      break;
    case Alt:
      return AS->println(c,f);
      break;
  }
}
size_t FBSerial::println(const Printable &c) {
  switch (type) {
    case Hard:
      return HS->println(c);
      break;
    case Soft:
      return SS->println(c);
      break;
    case Alt:
      return AS->println(c);
      break;
  }

}
size_t FBSerial::println(void) {
  switch (type) {
    case Hard:
      return HS->println();
      break;
    case Soft:
      return SS->println();
      break;
    case Alt:
      return AS->println();
      break;
  }

}
