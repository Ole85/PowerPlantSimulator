#ifndef CONTROLLOGIC_H
#define CONTROLLOGIC_H

//#include "enums.h"
#include "myEnums.h"
#include "sensor.h"
#include <QObject>
#include <QTimer>
enum PrioritySwitch { Compressor1, Compressor2 };

class ControlLogic : public QObject {
  Q_OBJECT
public:
  explicit ControlLogic(/*OperationMode _operationMode, const int _valuePSL,
                        const int _valuePSLL, const int _valuePSH,
                        */
                        QObject *parent = nullptr);

  Status statusCompressor1;
  Status statusCompressor2;

  OperationMode oMcompressors;
  PrioritySwitch prioritySwitch;
  Status statusPSL;
  Status statusPSLL;

  QVector<sensor> *mysensors;

  float vCompressor1FlowRate = 200; // m³/h
  float vCompressor2FlowRate = 200;
  float vPVrightNowNm = 50;
  float vPVtotalCapacityNm = 75;
  float vPVfillingPercent;
  float vPVcapacitym3 = 2.5;
  float vPVBar;
  float vPVbeginningNm = 2.5;
  int valuePSL;
  int valuePSLL;
  int valuePSH;
  QTimer *timerControlLogic;
  int valueIntervalTimer = 500;
  void SetValue(Status &statusCompressorNo, Status &statusbuffer);
  QString stringSystemName;
  QString stringSensorType;

private:
  void startCompressor();
  void stopCompressor();
public slots:
  void stepUpdate();
  void outputHello();
  void slotRadioButtonAutomatic();
  void slotRadioButtonManual();
signals:
  void signalUpdateGUI();
  void signalUpdateCheckStatus();
  void signalAlarm(const QString stringSystemName, QString stringSensorType);
  void signalPSLpixmapoff();
  void signalPSLLpixmapoff();
  void signalPSLHpixmapoff();
};

#endif // CONTROLLOGIC_H
