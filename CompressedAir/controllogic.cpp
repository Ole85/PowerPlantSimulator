#include "controllogic.h"
#include <QDebug>

ControlLogic::ControlLogic(/*OperationMode _operationMode, const int _valuePSL,
                           const int _valuePSLL, const int _valuePSH,
                           */
                           QObject *parent)
    : QObject(parent) {

  mysensors = new QVector<sensor>;
  timerControlLogic = new QTimer(this);
  statusCompressor1 = Off;
  statusCompressor2 = Off;
  //  valuePSL = _valuePSL;
  //  valuePSLL = _valuePSLL;
  //  valuePSH = _valuePSH;
  stringSystemName = "Compressed Air";

  prioritySwitch = Compressor1;
  oMcompressors = automatic;

  vPVfillingPercent = vPVrightNowNm / vPVtotalCapacityNm;

  vPVBar = vPVrightNowNm / vPVcapacitym3;

  timerControlLogic->start(valueIntervalTimer);

  //  switch (_operationMode) {
  //  case automatic:
  //    operationMode = automatic;
  //    break;
  //  case manual:
  //    operationMode = manual;
  //    break;
  //  }
}

void ControlLogic::SetValue(Status &statusCompressor, Status &statusbuffer) {

  if (oMcompressors == manual) {
    if (statusCompressor != statusbuffer) {
      statusCompressor = statusbuffer;
    }
    emit signalUpdateCheckStatus();
  }
}

void ControlLogic::startCompressor() {
  if (statusCompressor1 == On || statusCompressor2 == On) {
    statusCompressor1 = On;
    statusCompressor2 = On;
  } else if (prioritySwitch == Compressor1) {
    statusCompressor1 = On;

  } else if (prioritySwitch == Compressor2) {
    statusCompressor2 = On;
  }
}

void ControlLogic::stopCompressor() {
  statusCompressor1 = Off;
  statusCompressor2 = Off;
}

// checks values and switches
void ControlLogic::stepUpdate() {

  // Adding up Pressure Vessel
  // by Compressor 1
  if (statusCompressor1 == On) {
    vPVrightNowNm +=
        (vCompressor1FlowRate / 3600) * ((float)valueIntervalTimer / 1000);
    vPVBar = vPVrightNowNm / vPVbeginningNm;
  }
  // by Compressor 2
  if (statusCompressor2 == On) {
    vPVrightNowNm +=
        (vCompressor1FlowRate / 3600) * ((float)valueIntervalTimer / 1000);
    vPVBar = vPVrightNowNm / vPVbeginningNm;
  }

  vPVfillingPercent = vPVrightNowNm / vPVtotalCapacityNm;
  // PSL switch
  if (oMcompressors == automatic) {

    if (valuePSL > vPVBar && (*mysensors)[PSL].sensorStatus == Off) {
      (*mysensors)[PSL].sensorStatus = On;
      if (statusCompressor1 == Off && statusCompressor2 == Off) {
        startCompressor();
      }
      stringSensorType = "PSL";
      emit signalAlarm(stringSystemName, stringSensorType);
    } else if (valuePSL < vPVBar && (*mysensors)[PSL].sensorStatus == On) {
      (*mysensors)[PSL].sensorStatus = Off;
    }
  }
  // PSLL switch
  if (oMcompressors == automatic) {
    if (valuePSLL > vPVBar && (*mysensors)[PSLL].sensorStatus == Off) {
      (*mysensors)[PSLL].sensorStatus = On;
      startCompressor();
      stringSensorType = "PSLL";
      emit signalAlarm(stringSystemName, stringSensorType);
    } else if (valuePSLL < vPVBar && (*mysensors)[PSLL].sensorStatus == On) {
      (*mysensors)[PSLL].sensorStatus = Off;
    }
  }

  // PSH switch
  if (oMcompressors == automatic && valuePSH < vPVBar) {
    statusCompressor1 = Off;
    statusCompressor2 = Off;
  }
  emit signalUpdateGUI();
  emit signalUpdateCheckStatus();
}

void ControlLogic::outputHello() { qDebug() << "hello World"; }

void ControlLogic::slotRadioButtonAutomatic() {
  oMcompressors = automatic;
  qDebug() << oMcompressors;
}

void ControlLogic::slotRadioButtonManual() {
  oMcompressors = manual;
  qDebug() << oMcompressors;
}
