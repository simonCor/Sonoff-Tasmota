/*
  local_sensor_data.h - Locally cached sensor data

  Copyright (C) 2018  Simon Schwarz

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

/*
- temperature
- humidity
- gas
- pressure
- ambient light
- UV light
- Analog voltage value
- Current value
- CO2
- light seonsr
- particle data
*/
#ifndef LOCAL_SENSOR_DATA_H_
#define LOCAL_SENSOR_DATA_H_

#include <map>
#include "stdint.h"

/* Forward declaration of stuff in these weird .ino files */
void AddLog(uint8_t loglevel);
char* dtostrfd(double number, unsigned char prec, char *s);

class LocalSensorData {
    public:
    enum class types {temperature, humidity, pressure};
    static LocalSensorData *getInstance();

    private:
    LocalSensorData();

    private:
    float temperature;
    static LocalSensorData *inst;
    std::map<types, float> data;

    public:
    void setData(types dt, float d);
    float getData(types dt);
};

#endif // LOCAL_SENSOR_DATA_H_