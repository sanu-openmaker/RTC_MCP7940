
/*
   TO DO: total code uses 12KB memory . Hve to reconsider Date time class and MCP functions to redice progmem
   Reduced db to 1 year for replication - SAVED 4KB totoal usage wo Serial= 7308B
*/
#include "MCP7940.h"
#include "database.h"
#include <avr/sleep.h>


uint8_t *pTime;
bool isAlarmed =0;
DateTime dt(18, 2, 28, 0, 0, 0,1);
RTC_MCP7940 rtc;

#define intPin  2

void alarm() {
  dt = rtc.now();
  for (uint8_t i = 0; i <= isha; i++) {
    pTime = prayerTime(dt.yOff, dt.m, dt.d, i);
    if ((*pTime >= dt.hh) && (*(pTime + 1) > dt.mm)) {  // nearest upcoming prayer time
      rtc.setAlarm(dt);
      break;
    }
  }
}

void intFunc()        // here the interrupt is handled after wakeup
{
  sleep_disable();         // first thing after waking from sleep:
  // disable sleep...
  detachInterrupt(0);      // disables interrupt 0 on pin 2 so the wakeUpNow code will not be executed
  isAlarmed=1;
  alarm();

}

void sleepNow()         // here we put the arduino to sleep
{
  /* The 5 different modes are:
         SLEEP_MODE_IDLE         -the least power savings
         SLEEP_MODE_ADC
         SLEEP_MODE_PWR_SAVE
         SLEEP_MODE_STANDBY
         SLEEP_MODE_PWR_DOWN     -the most power savings
  */
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here

  sleep_enable();          // enables the sleep bit in the mcucr register

  attachInterrupt(0, intFunc, LOW); // use interrupt 0 (pin 2) and run function
  sleep_mode();            // here the device is actually put to sleep!

}

void setup() {
  //Serial.begin(9600);
  pinMode(intPin, INPUT);
  attachInterrupt(0, intFunc, LOW);
  rtc.begin();
  rtc.configure(0x98);
  while (!rtc.isset());//wait till clock starts ticking

  //rtc.adjust(DateTime(__DATE__, __TIME__)); //sets RTC time to time program was compiled

  alarm();


}

void loop() {
  if(isAlarmed){
    isAlarmed=0;
    //turn on lights
  }
  sleepNow();
}


