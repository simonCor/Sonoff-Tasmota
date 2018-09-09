/*
  xdrv_98_local_temperature_switch.ino - switches off the attached device when too warm

  Copyright (C) 2018 Thomas Herrmann
  Copyright (C) 2018 Simon Schwarz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "user_config.h"
#include "local_sensor_data.h"

#ifdef USE_LOCAL_TEMPERATURE_SWITCH
static const uint32_t minTimeBetweenSwitchStateChange_s = 5*60;

static LocalSensorData *localSensorData;
static uint32_t secondCounterSinceLastSwitch;

void Local_Temperature_Init()
{
  localSensorData = LocalSensorData::getInstance();
  snprintf_P(log_data, sizeof(log_data), "Local temperature switch Init");
  // Init with limit to allow immediate switch
  secondCounterSinceLastSwitch = minTimeBetweenSwitchStateChange_s;
  AddLog(LOG_LEVEL_INFO);
}

void Local_Temperature_Every_Second() {
  secondCounterSinceLastSwitch++;

  if(secondCounterSinceLastSwitch > minTimeBetweenSwitchStateChange_s) {
    float currentTemp = localSensorData->getData(LocalSensorData::types::temperature);  
    if(currentTemp > 5.0) {
      snprintf_P(log_data, sizeof(log_data), "Above 5 deg -> off");
      AddLog(LOG_LEVEL_INFO);
      ExecuteCommandPower(1, 0, SRC_LOCAL);
    } 

    if(currentTemp < 3.0) {
      snprintf_P(log_data, sizeof(log_data), "Below 3 deg -> on");
      AddLog(LOG_LEVEL_INFO);
      ExecuteCommandPower(1, 1, SRC_LOCAL);
    }
    secondCounterSinceLastSwitch = 0;
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

#define XDRV_98

boolean Xdrv98(byte function)
{
  boolean result = false;

  switch (function) {
  case FUNC_INIT:
    Local_Temperature_Init();
    break;
  case FUNC_EVERY_SECOND:
    Local_Temperature_Every_Second();
    break;
  }
  return result;
}

#endif // USE_LOCAL_TEMPERATURE_SWITCH
