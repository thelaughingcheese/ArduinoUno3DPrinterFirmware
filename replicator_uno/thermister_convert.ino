/*--------------------------
convert 10 bit analog read to remperature value
now uses a lookup table to suite the thermister
--------------------------*/
#define NUMTEMPS 20
short temptable[NUMTEMPS][2] = {
  {1, 916},
  {54, 265},
  {107, 216},
  {160, 189},
  {213, 171},
  {266, 157},
  {319, 146},
  {372, 136},
  {425, 127},
  {478, 118},
  {531, 110},
  {584, 103},
  {637, 95},
  {690, 88},
  {743, 80},
  {796, 71},
  {849, 62},
  {902, 50},
  {955, 34},
  {1008, 2}
};
/*
int thermister_convert(int RawADC) {
  float Temp;
  // See http://en.wikipedia.org/wiki/Thermistor for explanation of formula
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;           // Convert Kelvin to Celcius
  return round(Temp);
}*/

int thermister_convert(int rawtemp) {
   int current_celsius = 0;

   byte i;
   for (i=1; i<NUMTEMPS; i++)
   {
      if (temptable[i][0] > rawtemp)
      {
         int realtemp  = temptable[i-1][1] + (rawtemp - temptable[i-1][0]) * (temptable[i][1] - temptable[i-1][1]) / (temptable[i][0] - temptable[i-1][0]);

         if (realtemp > 255)
            realtemp = 255;

         current_celsius = realtemp;

         break;
      }
   }

   // Overflow: We just clamp to 0 degrees celsius
   if (i == NUMTEMPS)
   current_celsius = 0;

   return current_celsius;
}

