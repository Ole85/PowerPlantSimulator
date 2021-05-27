
#ifndef COMPRESSEDAIR_H
#define COMPRESSEDAIR_H

#include "controlpanelca.h"
#include "enumsca.h"
#include "screenca.h"
#include "settingsca.h"
#include <QPushButton>
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CompressedAir;
}
QT_END_NAMESPACE

// using namespace CA;

class CompressedAir : public QWidget {
  Q_OBJECT

public:
  int chris = 15;
  std::array<Sensor, 3> sensors;
  explicit CompressedAir(QWidget *parent = nullptr);
  ~CompressedAir();

  ControlPanelCA *controlPanelCA;
  ScreenCA *screenCA;
  SettingsCA *settingsCA;

  // Compressor
  QList<int> compressorList = {0, 1};
  float vCompressor1FlowRate = 200; // m³/h
  float vCompressor2FlowRate = 200;

  float vVisNm3 = 50.0;
  float vPVtotalCapacityNm3 = 75;
  float vPVfillingPercent;
  float vPis;
  float vVvesselM3 = 2.5; // m³
#if !LIBMODE
  QTimer *clockTimer;
#endif
  QTimer *blinkingTimer;
  int valueIntervalTimer = 500;
  void SetValue(Status &statusCompressorNo, Status &statusbuffer);
  QString stringSystemName;
  QString stringSensorType;
  Status statusLightup = On;
  OperationMode operationMode;

  std::array<Compressor, 2> compressors;

  void fconnect();

  // values, states
  void fInitializingValues();
  void fsetStates();
  void fupdateStorage();

  // GUI
  void fGUIupdate();
  void fGUIcheckSensors();

private:
  Ui::CompressedAir *ui;
  QTimer *timerBlinking;
  bool timerBool = false;

  bool timerStatusPSLon = false;
  bool timerStatusPSLLon = false;

public slots:
  void slotCycle();
  void slotButtonClick(int, Status);
  void slotPriorityChange(int);
  void slotSpinBoxPSL(int);
  void slotSpinBoxPSLL(int);
  void slotSpinBoxPSH(int);
  void slotLightUpStatus();
  void slotMessage();
  void slotOperationMode(OperationMode);
signals:
  void signalRangeChange(Sensor);
private slots:
};
#endif // COMPRESSEDAIR_H
