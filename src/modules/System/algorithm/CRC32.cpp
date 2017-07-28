
#include "CRC32.h"


void CRC32::clear(){
	crc = ~0L;
}
void CRC32::update(uint8_t data){
	byte tbl_idx;
	tbl_idx = crc ^ (data >> (0 * 4));
	crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
	tbl_idx = crc ^ (data >> (1 * 4));
	crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);

}


uint32_t CRC32::checksum(uint8_t data[],int start,int end){
  clear();
  for(int i=start;i<end;i++){
     update(data[i]);
  }
  return crc;
}
uint32_t CRC32::checksum(String &data,int start,int end){
	clear();
	if (end<0){
		end=data.length();
	}
	for(int i=start;i<end;i++){
		 update(data.charAt(i));
	}
	return crc;
}
String CRC32::checksumToHexStr(String &data){
	String res=String(checksum(data),HEX);
	res.toUpperCase();
	return res;
}
String CRC32::toHexStr(uint32_t result){
	String res=String(result,HEX);
	res.toUpperCase();
	return res;
}
