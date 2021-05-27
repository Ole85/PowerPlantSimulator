#include "compressedair.h"
#include "myEnums.h"

#include "ui_compressedair.h"
#include "ui_controlpanelca.h"
#include "ui_screenca.h"
#include <QDebug>

CompressedAir::CompressedAir(QWidget *parent)
    : QWidget(parent), controlPanelCA(new ControlPanelCA),
      screenCA(new ScreenCA), settingsCA(new SettingsCA),
      ui(new Ui::CompressedAir) {
  ui->setupUi(this);
#if !LIBMODE
  clockTimer = new QTimer(this);
  clockTimer->start(valueIntervalTimer);
#endif

  blinkingTimer = new QTimer(this);
  blinkingTimer->start(1000);

  fInitializingValues();
  slotCycle();
  //  fGUIupdate();
  fconnect();

  // SpinBoxValues
  //  controlPanelCA->ui->spinBoxPSH->setValue(sensors[0].limitValue);
  //  controlPanelCA->ui->spinBoxPSL->setValue(sensors[1].limitValue);
  //  controlPanelCA->ui->spinBoxPSLL->setValue(sensors[2].limitValue);
}

CompressedAir::~CompressedAir() { delete ui; }

void CompressedAir::slotCycle() {
  fupdateStorage();

  fsetStates();
  fGUIupdate();
}

void CompressedAir::fsetStates() {

  // vPis < PSL =>Kompressor Prioritaet 1einschalten
  if (vPis < sensors[PSL].limitValue) {
    sensors[PSL].status = On;
    if (operationMode == automatic) {
      compressors[compressorList[0]].status = On;
    }
  } else if (vPis > sensors[PSL].limitValue) {
    //    if (operationMode == automatic) {
    //      compressors[compressorList[0]].status = Off;
    //    }
    sensors[PSL].status = Off;
  }

  // vPis < PSLL => Kompressor Prioriortaet 2 einschalten
  if (vPis < sensors[PSLL].limitValue) {
    if (operationMode == automatic) {
      compressors[compressorList[1]].status = On;
    }
    sensors[PSLL].status = On;

  } else if (vPis > sensors[2].limitValue) {
    if (operationMode == automatic) {
      compressors[compressorList[1]].status = Off;
    }
    sensors[PSLL].status = Off;
  }

  if (vPis > sensors[PSH].limitValue) {
    if (operationMode == automatic) {
      compressors[0].status = Off;
      compressors[1].status = Off;
    }
    sensors[PSH].status = On;
  } else {
    sensors[PSH].status = Off;
  }
}

void CompressedAir::fupdateStorage() {

  // Aktuellen Volumenstrom abfragen
  float vGes = 0; // Nm³/h
  for (int i = 0; i < (int)compressors.size(); i++) {
    if (compressors[i].status == On) {
      vGes += compressors[i].flowrate; // Nm³/h
    }
  }

  // Produzierte Menge aufaddieren
  float t = valueIntervalTimer / (1000.0 * 3600);
  vVisNm3 += vGes * t; // Vneu = Valt + Volumenstrom * t

  // Fuellung und Druck anhand des neuen
  vPVfillingPercent = vVisNm3 / vPVtotalCapacityNm3;
  vPis = vVisNm3 / vVvesselM3;
}

void CompressedAir::fGUIcheckSensors() {
  //  if (vPis > sensors[1].limitValue) {
  //    screenCA->ui->labelSensorPSL->setPixmap(QPixmap(":/sensorPSLoff.png"));
  //  } else if (vPis < sensors[1].limitValue) {
  //    screenCA->ui->labelSensorPSL->setPixmap(QPixmap(":/sensorPSLon.png"));
  //  }

  for (int i = 0; i < (int)sensors.size(); i++) {
    if (sensors[i].status == On && statusLightup == On) {
      sensors[i].labelPtr->setPixmap(QPixmap(sensors[i].sensorOn));
    } else {
      sensors[i].labelPtr->setPixmap(QPixmap(sensors[i].sensorOff));
    }
  }
}

void CompressedAir::fGUIupdate() {
  fGUIcheckSensors();
  // Control Panel
  controlPanelCA->fGUIupdateButtonsAll(compressors);

  // Screen Compressed Air
  screenCA->fGUIupdateCompressorAll(compressors);

  // Filling
  int value = vPVfillingPercent * 100;
  screenCA->ui->progressBar->setValue(value);
  screenCA->ui->labelValueAirAmountNm->setText(
      QString::number(vVisNm3, 'f', 2));
  screenCA->ui->labelPI->setText(QString::number(vPis, 'f', 1));
}

void CompressedAir::fInitializingValues() {
  //  compressorStates[0] = Off;
  //  compressorStates[1] = Off;

  if (controlPanelCA->ui->radioButtonAutomatic->isChecked()) {
    operationMode = automatic;
  } else if (controlPanelCA->ui->radioButtonManual->isChecked()) {
    operationMode = manual;
  }

  // Compressor Init Values
  compressors[0].status = Off;
  compressors[0].flowrate = 200;
  compressors[1].status = Off;
  compressors[1].flowrate = 200;

  // Sensor InitValues
  sensors[0].status = Off;
  sensors[0].sensorOff = ":/sensorPSHoff.png";
  sensors[0].sensorOn = ":/sensorPSHon.png";
  sensors[0].limitValue = controlPanelCA->ui->spinBoxPSH->value();
  sensors[0].labelPtr = screenCA->ui->labelSensorPSH;

  sensors[1].status = Off;
  sensors[1].sensorOff = ":/sensorPSLoff.png";
  sensors[1].sensorOn = ":/sensorPSLon.png";
  sensors[1].limitValue = controlPanelCA->ui->spinBoxPSL->value();
  sensors[1].labelPtr = screenCA->ui->labelSensorPSL;

  sensors[2].status = Off;
  sensors[2].sensorOff = ":/sensorPSLLoff.png";
  sensors[2].sensorOn = ":/sensorPSLLon.png";
  sensors[2].limitValue = controlPanelCA->ui->spinBoxPSLL->value();
  sensors[2].labelPtr = screenCA->ui->labelSensorPSLL;
}

void CompressedAir::slotButtonClick(int id, Status status) {
  compressors[id].status = status;
  controlPanelCA->fGUIupdateButton(id, status);
  screenCA->fGUIupdateCompressor(id, status);
}

void CompressedAir::slotPriorityChange(int index) {
  for (int i = 0; i < compressorList.size(); i++) {
    if (compressorList[i] == index) {
      compressorList.move(i, 0);
    }
  }

  for (int i = 0; i < compressorList.size(); i++) {
  }
}

void CompressedAir::slotSpinBoxPSL(int value) {

  bool b = ((value - 1) > sensors[2].limitValue);
  qDebug() << b;
  if (b == true) {
    sensors[1].limitValue = value;
    qDebug() << "LimitVAlue" << sensors[1].limitValue;
  }
}

void CompressedAir::slotSpinBoxPSLL(int value) {
  sensors[2].limitValue = value;
}

void CompressedAir::slotSpinBoxPSH(int value) { sensors[0].limitValue = value; }

void CompressedAir::slotLightUpStatus() {
  if (statusLightup == Off) {
    statusLightup = On;
  } else {
    statusLightup = Off;
  }
}

void CompressedAir::slotMessage() {}

void CompressedAir::slotOperationMode(OperationMode operationMode_) {
  if (operationMode_ == manual) {
    operationMode = manual;
  } else if (operationMode_ == automatic) {
    operationMode = automatic;
  }
}
