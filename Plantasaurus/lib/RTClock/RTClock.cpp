/*
Writen by Orlando Diaz
*/
#include <RTClock.h>

/*
Constructor
*/
RTClock::RTClock(PinName _SDAPIN, PinName _SLKPIN):rtc(_SDAPIN,_SLKPIN){
    SDAPIN = _SDAPIN;
    SLKPIN = _SLKPIN;
}

uint16_t RTClock::ReadDate(void){
    /*
    If the RTC is connected, the date is filled. otherwise returns 1
    */
    //The DS1307 accepts only int as arguments, so some temporary variables will be created to parse as arguments
    int secs,mins,hour,date,day,month,year;
    if(!rtc.gettime(&secs, &mins, &hour, &date, &day, &month, &year)){
        time.secs = secs;
        time.mins = mins;
        time.hour = hour;
        time.date = date;
        time.day = day ; 
        time.month = month; 
        time.year = year; 
        return 0;
    }
else{
        return 1;
    }
}

StructTime RTClock::GetDate(void){
    return time;
}

void RTClock::GetDatestr(char* datestr){
    sprintf(datestr,"%d-%d-%d-%02d:%02d:%02d", year, month, day, hour, mins, secs);   
}    

 uint16_t RTClock::SetRTClock(int _sec, int _mins, int _hour, int _day, int _date, int _month, int _year){
     if(!rtc.settime(_sec,_mins,_hour,_day,_date,_month,_year)){
            return 0;      
        }
        else{
            return 1;
        } 
    }