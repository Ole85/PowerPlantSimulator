#ifndef SENSOR_H
#define SENSOR_H
#include "myEnums.h"
#include <QLabel>
#include <QObject>

// using namespace CA;
enum myindex { PSLL, PSL, PSH };
class sensor {
public:
  QString sourceNormal;
  QString sourceLightup;
  Status pixmapLightup;
  Status sensorStatus;
  QLabel *labelPtr;
  sensor() {
    sourceNormal = "";
    sourceLightup = "";
    pixmapLightup = Off;
    sensorStatus = Off;
    labelPtr = nullptr;
  }
  sensor(QString sourceNormalVal, QString sourceLightupVal,
         Status pixmapLightupVal, Status sensorStatusVal, QLabel *labelPtrVal) {
    sourceNormal = sourceNormalVal;
    sourceLightup = sourceLightupVal;
    pixmapLightup = pixmapLightupVal;
    sensorStatus = sensorStatusVal;
    labelPtr = labelPtrVal;
  }
signals:
};

#endif // SENSOR_H
