#include "dataTest.h"

void getDataTest(owm_resp_onecall_t &r){
  //Timezone offset
  Serial.println("Timezone offset");
  Serial.println(r.timezone_offset);

  //Current data
  Serial.println();
  Serial.println("Current data: ");
  Serial.println(r.current.dt);
  Serial.println(r.current.sunrise);
  Serial.println(r.current.sunset);
  Serial.println(r.current.temp);
  Serial.println(r.current.weather.icon);
  
  //Hourly data
  Serial.println();
  Serial.println("Hourly data: ");
  for(int i; i < OWM_NUM_HOURLY; i++){
    Serial.println(i);
    Serial.println(r.hourly[i].dt);
    Serial.println(r.hourly[i].temp);
    Serial.println(r.hourly[i].rain_1h);
  }
  
  //Daily data
  Serial.println();
  Serial.println("Daily data: ");
  for(int i; i < OWM_NUM_DAILY; i++){
    Serial.println(i);
    Serial.println(r.daily[i].dt);
    Serial.println(r.daily[i].sunrise);
    Serial.println(r.daily[i].sunset);
    
    Serial.println(r.daily[i].temp.min);
    Serial.println(r.daily[i].temp.max);

    Serial.println(r.daily[i].weather.icon);
  }
}