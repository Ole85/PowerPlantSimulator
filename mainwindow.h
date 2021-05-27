#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../ERLayout/sharedSource/enginecontrol.h"
#include "QTimer"
#include "compressedair.h"
#include "coolingwater.h"
#include "datatable.h"
#include "myEnums.h"
#include "simcontrol.h"
#include <QMainWindow>
#include <QScrollArea>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Systems { CA, CW_ };

struct leftLayoutStates {
  bool control;
  bool settings;
};

struct systemWidgetsPtr {
  QWidget *controlPtr;
  QWidget *settingsPtr;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  CoolingWater *coolingWater;
  CompressedAir *compressedAir;
  SimControl *simControl;
  EngineControl *engineControl;
  DataTable *dataTable;

  QWidget *widgetCA;
  QWidget *widgetCW;

  QStackedWidget *stackedWidget;
  QTimer *clockTimer;
  QScrollArea *scrollArea;

  std::array<leftLayoutStates, 2> myStates;
  std::array<systemWidgetsPtr, 2> mySystemPtrs;

  std::array<bool, 2> myActiveSystems;

  void fControlOrSettingsShow(Systems);

public slots:
  void slotCycle();

private slots:

  void on_actionGraph_triggered(bool checked);

  void slotStopClock();

  void slotUpdateDataPumpsCW();

  void slotStartClock();

  //  void on_actionEngineControl_triggered(bool checked);

  void on_buttonCW_clicked();

  void on_buttonCompressedAir_clicked();

  void on_buttonLO_clicked();

  void on_actionSettingsCW_triggered();

  void on_actionControlCW_triggered();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
