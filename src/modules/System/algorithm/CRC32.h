#ifndef CRC32_H
#define CRC32_H

//CRC-16/XMODEM x16+x12+x5+1

#include "Arduino.h"


class CRC32 {
  private:
    uint32_t crc= ~0L;
    const uint32_t crc_table[16] PROGMEM = {
       0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
       0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
       0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
       0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };
    void update(uint8_t data);

  public:
    void clear();

    uint32_t checksum(uint8_t data[],int start,int end);
    uint32_t checksum(String &data,int start=0,int end=-1);
    String checksumToHexStr(String &data);
    String toHexStr(uint32_t result);
};
#endif
