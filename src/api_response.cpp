#include "api_response.h"
#include "config.h"


void getData(owm_resp_onecall_t &r){
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
    
    http.begin(endpoint + key); //Specify the URL
    int httpCode = http.GET();  //Make the request

    
    if (httpCode > 0) { //Check for the returning code
        Serial.println(httpCode);  
        
        DeserializationError error = deserializeOneCall(http.getStream(), r);
        if(error){
            Serial.println("An error occured when deserializing the HTTPS stream");
            return;
          }
        
      }else {
      Serial.println("Error on HTTP request");
    }
    http.end(); //Free the resources
  }
}

DeserializationError deserializeOneCall(WiFiClient &json, owm_resp_onecall_t &r){
  int i;
  
  // Stream& input;
  StaticJsonDocument<416> filter;
  filter["timezone_offset"] = true;

  JsonObject filter_current = filter.createNestedObject("current");
  filter_current["dt"] = true;
  filter_current["sunrise"] = true;
  filter_current["sunset"] = true;
  filter_current["temp"] = true;
  filter_current["weather"][0]["icon"] = true;

  JsonObject filter_hourly_0 = filter["hourly"].createNestedObject();
  filter_hourly_0["dt"] = true;
  filter_hourly_0["temp"] = true;
  filter_hourly_0["rain"]["1h"] = true;

  JsonObject filter_daily_0 = filter["daily"].createNestedObject();
  filter_daily_0["dt"] = true;
  filter_daily_0["sunrise"] = true;
  filter_daily_0["sunset"] = true;

  JsonObject filter_daily_0_temp = filter_daily_0.createNestedObject("temp");
  filter_daily_0_temp["min"] = true;
  filter_daily_0_temp["max"] = true;
  filter_daily_0["weather"][0]["icon"] = true;

  DynamicJsonDocument doc(4096);

  DeserializationError error = deserializeJson(doc, json, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return error;
  }

  r.timezone_offset = doc["timezone_offset"].as<int>();

  JsonObject current = doc["current"];
  r.current.dt = current["dt"]            .as<int64_t>(); // 1697363789
  r.current.sunrise = current["sunrise"]  .as<int64_t>(); // 1697350243
  r.current.sunset = current["sunset"]    .as<int64_t>(); // 1697390615
  r.current.temp = current["temp"]        .as<float>(); // 24.7

  r.current.weather.icon = current["weather"][0]["icon"].as<const char *>(); // 801

  i = 0;
  for (JsonObject hourly : doc["hourly"].as<JsonArray>())
  {
    r.hourly[i].dt         = hourly["dt"]        .as<int64_t>();
    r.hourly[i].temp       = hourly["temp"]      .as<float>();
    r.hourly[i].rain_1h    = hourly["rain"]["1h"].as<float>();

    if (i == OWM_NUM_HOURLY - 1)
    {
      break;
    }
    ++i;
  }

  i = 0;
  for (JsonObject daily: doc["daily"].as<JsonArray>()) {
    r.daily[i].dt         = daily["dt"]        .as<int64_t>();
    r.daily[i].sunrise    = daily["sunrise"]   .as<int64_t>();
    r.daily[i].sunset     = daily["sunset"]    .as<int64_t>();

    JsonObject daily_temp = daily["temp"];
    r.daily[i].temp.min   = daily_temp["min"]  .as<float>();
    r.daily[i].temp.max   = daily_temp["max"]  .as<float>();

    JsonObject daily_weather = daily["weather"][0];
    r.daily[i].weather.icon        = daily_weather["icon"]       .as<const char *>();

    if (i == OWM_NUM_DAILY - 1)
    {
      break;
    }
    ++i;
  }
  
  return error;
}