/* ---------------------------------------------------------------------
  Startup...
  Clear first 16bytes of RTC static ram, read back, write pattern/read back
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
   ---------------------------------------------------------------------

*/

#include <avr/pgmspace.h>
#include "MCP7940.h"
#include "database.h"


uint8_t *pTime;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pTime=prayerTime(18,2,21,fajr);
  Serial.println(*pTime);
  Serial.println(*(pTime+1));
  delay(500);
}


