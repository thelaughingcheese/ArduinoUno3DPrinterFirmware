/*-------------------
dallas 8 bit crc used in ibutton
-------------------*/

uint8_t crc8( uint8_t addr[], uint8_t len){ //code 'stolen' from http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1279505626
	uint8_t crc=0;

	for (uint8_t i=0; i<len;i++)
	{
		uint8_t inbyte = addr[i];
		for (uint8_t j=0;j<8;j++)
		{
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix)
				crc ^= 0x8C;

			inbyte >>= 1;
		}
	}
	return crc;
} 

