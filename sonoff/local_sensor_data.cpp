#include <cstddef>
#include <cmath>
#include "local_sensor_data.h"
#include "pgmspace.h"
#include "sonoff.h"

extern char log_data[LOGSZ];

LocalSensorData *LocalSensorData::inst = NULL;

LocalSensorData::LocalSensorData() {
    
}

LocalSensorData *LocalSensorData::getInstance() {
    if(!inst) {
        inst = new LocalSensorData;
    }
    return(inst);
}

void LocalSensorData::setData(types dt, float d) {
    data[dt] = d;
}

float LocalSensorData::getData(types dt) {
    if(data.count(dt)) {
        return data[dt];
    } else {
        return NAN;
    }
}