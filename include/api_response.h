
#ifndef __API_RESPONSE_H__
#define __API_RESPONSE_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define OWM_NUM_HOURLY        48 // 48
#define OWM_NUM_DAILY          8 // 8

typedef struct owm_weather
{
  String  icon;             // Weather icon id.
} owm_weather_t;
/*
 * Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
 */
typedef struct owm_temp
{
  float   min;              // Min daily temperature.
  float   max;              // Max daily temperature.
} owm_temp_t;
/*
 * Current weather data API response
 */
typedef struct owm_current
{
  int64_t dt;               // Current time, Unix, UTC
  int64_t sunrise;          // Sunrise time, Unix, UTC
  int64_t sunset;           // Sunset time, Unix, UTC
  float   temp;             // Temperature. Units - default: kelvin, metric: Celsius, imperial: Fahrenheit.
  owm_weather_t         weather;
} owm_current_t;

/*
 * Hourly forecast weather data API response
 */
typedef struct owm_hourly
{
  int64_t dt;               // Time of the forecasted data, unix, UTC
  float   temp;             // Temperature. Units - default: kelvin, metric: Celsius, imperial: Fahrenheit.
  float   rain_1h;          // (where available) Rain volume for last hour, mm
  owm_weather_t         weather;
} owm_hourly_t;

/*
 * Daily forecast weather data API response
 */
typedef struct owm_daily
{
  int64_t dt;               // Time of the forecasted data, unix, UTC
  int64_t sunrise;          // Sunrise time, Unix, UTCowm_temp_t            temp;
  int64_t sunset;           // Sunset time, Unix, UTC
  owm_temp_t            temp;
  owm_weather_t         weather;
} owm_daily_t;

/*
 * Response from OpenWeatherMap's OneCall API
 *
 * https://openweathermap.org/api/one-call-api
 */
typedef struct owm_resp_onecall
{
  int     timezone_offset;  // Shift in seconds from UTC
  owm_current_t   current;
  owm_hourly_t    hourly[OWM_NUM_HOURLY];
  owm_daily_t     daily[OWM_NUM_DAILY];
} owm_resp_onecall_t;

void getData(owm_resp_onecall_t &r);

DeserializationError deserializeOneCall(WiFiClient &json, owm_resp_onecall_t &r);

#endif

