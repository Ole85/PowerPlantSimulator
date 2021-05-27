#pragma once
#include "myEnums.h"
#include <QLabel>
#include <QPushButton>
enum SensorTitlesCA { PSH, PSL, PSLL };

struct CompressorSet {
  Status status;
  QPushButton *buttonOn;
  QPushButton *buttonOff;
};

struct Compressor {
  Status status;
  int flowrate;
};

struct Sensor {
  Status status;
  int limitValue;
  QString sensorOff;
  QString sensorOn;
  QLabel *labelPtr;
};
