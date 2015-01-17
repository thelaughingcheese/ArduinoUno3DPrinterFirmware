/*--------------------------
convert 10 bit analog read to remperature value
now uses a lookup table to suite the thermister
--------------------------*/

int thermister_convert(uint32_t rawtemp) {
   return rawtemp*500/1024;
}

