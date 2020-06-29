/*
Writen by Orlando Diaz
Wrapping library that uses the DS1307 library
*/
#ifndef RTCLOCK_H
#define RTCLOCK_H

#include "mbed.h"
#include <ds1307.h>

/*
RTC Date data structure
*/
struct StructTime{
    uint16_t secs;
    uint16_t mins;
    uint16_t hour;
    uint16_t day;
    uint16_t date;
    uint16_t month;
    uint16_t year;
};

class RTClock{
private:
    char datestr[20];
    PinName SDAPIN;
    PinName SLKPIN;
    int year, month, day, date, hour, mins, secs;
    DS1307 rtc;
    StructTime time; 

public:
    /*
    Constructor
     Arguments:
        _SDAPIN:
        _SLKPIN:   
    */
    RTClock(PinName _SDAPIN, PinName _SLKPIN);

    /*
    reads the date from the RTC and and update the time structure.
    Arguments:
        None
    Output:
         0 if rtc is read is succesfull
         1 if fails finding an RTC
    */
    uint16_t ReadDate(void);

    /*
    Returns the structure Structtime. 
    */
    StructTime GetDate(void);

    /*
    Fills a char array with the stored date in the following format:
    yyyy-mm-dd-hh:mm:ss
    Returns:
        None
    */
    void GetDatestr(char* datestr);

    /*
    sets the RTC clock with the desired date
        Information tacking from ds1307 library. 
        @param _sec the seconds value (0 - 59)
        @param _min the minute value (0 - 59)
        @param _hour the hour value (0 - 23) always in 24 hour
        @param _day the day value ( sunday is 1 )
        @param _date the date value (1 - 31)
        @param _month the month value (1-12)
        @param _year the year value (00 - 99) this is for 2000 to 2099 only as i 
    */
    uint16_t SetRTClock(int _sec,
                        int _mins,
                        int _hour,
                        int _day,
                        int _date,
                        int _month,
                        int _year);
};
#endif