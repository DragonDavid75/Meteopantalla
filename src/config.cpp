#include <Arduino.h>
#include "config.h"

//Wifi configuration
const char* ssid = "OnePlus 8T";
const char* password =  "undostres";

//API Configuration
const String endpoint = "http://api.openweathermap.org/data/3.0/onecall?lat=39.4893&lon=0.36486&exclude=minutely,alerts&appid="; //https://api.openweathermap.org/data/3.0/onecall?lat={lat}&lon={lon}&exclude={part}&appid={API key};
const String key = "d1b5b9973d1fabd293ad06fcc273ff8c"; //abcdefghijklmnopqrstuvwxyz012345;