
#include "CRC16.h"


//---------------------------------------------------
// Initialize crc calculation
//---------------------------------------------------
void CRC16::clearCrc()
{
	_crc = _xorIn;
}
//---------------------------------------------------
// Update crc with new data
//---------------------------------------------------
void CRC16::updateCrc(uint8_t data)
{
	if (_reflectIn != 0)
		data = (uint8_t) reflect(data, 8);

	int j = 0x80;

	while (j > 0)
	{
		uint16_t bit = (uint16_t)(_crc & _msbMask);

		_crc <<= 1;

		if ((data & j) != 0)
		{
			bit = (uint16_t)(bit ^ _msbMask);
		}

		if (bit != 0)
		{
			_crc ^= _polynomial;
		}

		j >>= 1;
	}
}

//---------------------------------------------------
// Get final crc value
//---------------------------------------------------
uint16_t CRC16::getCrc()
{
  if (_reflectOut != 0)
		_crc = (unsigned int)((reflect(_crc) ^ _xorOut) & _mask);

	return _crc;
}

//---------------------------------------------------
// Calculate generic crc code on data array
// Examples of crc 16:
// Kermit: 		width=16 poly=0x1021 init=0x0000 refin=true  refout=true  xorout=0x0000 check=0x2189
// Modbus: 		width=16 poly=0x8005 init=0xffff refin=true  refout=true  xorout=0x0000 check=0x4b37
// XModem: 		width=16 poly=0x1021 init=0x0000 refin=false refout=false xorout=0x0000 check=0x31c3
// CCITT-False:	width=16 poly=0x1021 init=0xffff refin=false refout=false xorout=0x0000 check=0x29b1
//---------------------------------------------------
unsigned int CRC16::fastCrc(uint8_t data[], uint8_t start, uint16_t length, uint8_t reflectIn, uint8_t reflectOut, uint16_t polynomial, uint16_t xorIn, uint16_t xorOut, uint16_t msbMask, uint16_t mask)
{
	unsigned int crc = xorIn;

	int j;
	uint8_t c;
	unsigned int bit;

	if (length == 0) return crc;

	for (int i = start; i < (start + length); i++)
	{
		c = data[i];

		if (reflectIn != 0)
			c = (uint8_t) reflect(c, 8);

		j = 0x80;

		while (j > 0)
		{
			bit = (unsigned int)(crc & msbMask);
			crc <<= 1;

			if ((c & j) != 0)
			{
				bit = (unsigned int)(bit ^ msbMask);
			}

			if (bit != 0)
			{
				crc ^= polynomial;
			}

			j >>= 1;
		}
	}

	if (reflectOut != 0)
		crc = (unsigned int)((reflect(crc) ^ xorOut) & mask);

	return crc;
}

//-------------------------------------------------------
// Reflects bit in a uint8_t
//-------------------------------------------------------
uint8_t CRC16::reflect(uint8_t data, uint8_t bits)
{
	unsigned long reflection = 0x00000000;
	// Reflect the data about the center bit.
	for (uint8_t bit = 0; bit < bits; bit++)
	{
		// If the LSB bit is set, set the reflection of it.
		if ((data & 0x01) != 0)
		{
			reflection |= (unsigned long)(1 << ((bits - 1) - bit));
		}

		data = (uint8_t)(data >> 1);
	}

	return reflection;
}
uint16_t CRC16::checksum(uint8_t data[],int start,int end){
  clearCrc();
  for(int i=start;i<end;i++){
     updateCrc(data[i]);
  }
  return getCrc();
}
uint16_t CRC16::checksum(String &data,int start,int end){
	clearCrc();
	if (end<0){
		end=data.length();
	}
	for(int i=start;i<end;i++){
		 updateCrc(data.charAt(i));
	}
	return getCrc();
}
String CRC16::checksumToHexStr(String &data){
	String res=String(checksum(data),HEX);
	res.toUpperCase();
	return res;
}
String CRC16::toHexStr(uint16_t result){
	String res=String(result,HEX);
	res.toUpperCase();
	return res;
}
