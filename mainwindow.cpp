#include "mainwindow.h"
#include "ui_datatable.h"
#include "ui_enginecontrol.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);

  dataTable = new DataTable;
  compressedAir = new CompressedAir;
  simControl = new SimControl;
  engineControl = new EngineControl;
  coolingWater = new CoolingWater;
  scrollArea = new QScrollArea;

  myActiveSystems[CA] = ui->buttonCompressedAir->isChecked();
  myActiveSystems[CW_] = ui->buttonCW->isChecked();

  myStates[CA].control = true;
  myStates[CA].settings = false;
  myStates[CW_].control = true;
  myStates[CW_].settings = false;

  this->statusBar()->hide();
  scrollArea->setWidget(dataTable);

  mySystemPtrs[CA].controlPtr = compressedAir->controlPanelCA;
  mySystemPtrs[CA].settingsPtr = compressedAir->settingsCA;
  //  mySystemPtrs[CA].settingsPtr = compressedAir
  //                                     ->setting

  mySystemPtrs[CW_].controlPtr = coolingWater->controlPanelCW;
  mySystemPtrs[CW_].settingsPtr = coolingWater->settingsCW;

  ui->leftFrame->setStyleSheet("QFrame#leftFrame {border-right-width: 3px;"
                               "border-style: solid;"
                               "border-color:darkgrey;}");
  ui->bottomFrameLayout->addWidget(scrollArea);
  ui->bottomFrameLayout->addStretch();

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->setMargin(0);
  leftLayout->setSpacing(0);

  //  compressedAir->controlPanelCA->setFixedHeight(500);
  compressedAir->controlPanelCA->setSizePolicy(QSizePolicy::Minimum,
                                               QSizePolicy::Minimum);
  compressedAir->controlPanelCA->setFixedHeight(450);
  compressedAir->controlPanelCA->setAttribute(Qt::WA_StyledBackground, true);
  leftLayout->addWidget(compressedAir->controlPanelCA);

  coolingWater->controlPanelCW->setSizePolicy(QSizePolicy::Minimum,
                                              QSizePolicy::Minimum);
  coolingWater->controlPanelCW->setFixedHeight(450);
  coolingWater->controlPanelCW->setAttribute(Qt::WA_StyledBackground, true);
  coolingWater->controlPanelCW->hide();

  coolingWater->settingsCW->setFixedHeight(450);
  coolingWater->settingsCW->hide();

  leftLayout->addWidget(coolingWater->controlPanelCW);
  leftLayout->addWidget(coolingWater->settingsCW);

  engineControl->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  leftLayout->addWidget(engineControl);

  ui->leftFrame->setLayout(leftLayout);

  QHBoxLayout *mainLayout = new QHBoxLayout;

  coolingWater->screenCW->hide();

  mainLayout->addWidget(compressedAir->screenCA);
  mainLayout->addWidget(coolingWater->screenCW);

  engineControl->ui->frame->setStyleSheet("#frame {border-top-width: 3px;"
                                          "border-style: solid;"
                                          "border-color:darkgrey;}");
  ui->mainFrame->setLayout(mainLayout);

  //  dataTable->slotUpdatePumpsCW(coolingWater->vP);
  clockTimer = new QTimer;
  clockTimer->start(1000);

  connect(clockTimer, &QTimer::timeout, this, &MainWindow::slotCycle);
  connect(clockTimer, &QTimer::timeout, compressedAir,
          &CompressedAir::slotCycle);
  connect(clockTimer, &QTimer::timeout, coolingWater, &CoolingWater::slotCycle);
  connect(simControl, &SimControl::signalStartClock, this,
          &MainWindow::slotStartClock);
  connect(simControl, &SimControl::signalStopClock, this,
          &MainWindow::slotStopClock);
  connect(engineControl->ui->sliderLoad, &QSlider::valueChanged, coolingWater,
          &CoolingWater::slotMySliderChange);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::fControlOrSettingsShow(Systems system) {

  if (myStates[system].control == true) {
    mySystemPtrs[system].settingsPtr->hide();
    mySystemPtrs[system].controlPtr->show();
  } else if (myStates[system].settings == true) {
    mySystemPtrs[system].controlPtr->hide();
    mySystemPtrs[system].settingsPtr->show();
  }
}

void MainWindow::slotCycle() {

  qDebug() << "cooooollllsadasd" << coolingWater->vTSP;
  dataTable->slotUpdatePumpsCW(coolingWater->vP);
}

void MainWindow::on_actionGraph_triggered(bool checked) {
  if (checked == true) {
    coolingWater->graphPlot->setWindowFlags(Qt::WindowStaysOnTopHint);
    coolingWater->graphPlot->show();
  } else {
    coolingWater->graphPlot->hide();
  }
}

void MainWindow::slotStopClock() { clockTimer->stop(); }

void MainWindow::slotUpdateDataPumpsCW() {}

void MainWindow::slotStartClock() { clockTimer->start(); }

void MainWindow::on_buttonCW_clicked() {

  ui->buttonCompressedAir->setChecked(false);

  coolingWater->screenCW->show();
  compressedAir->screenCA->hide();

  // alle anderen ausschalten
  mySystemPtrs[CA].controlPtr->hide();
  //  for (int i = 0; i < (int)mySystemPtrs.size(); i++) {
  //    mySystemPtrs[i].controlPtr->hide();
  //    mySystemPtrs[i].settingsPtr->hide();
  //  }

  fControlOrSettingsShow(CW_);
}

void MainWindow::on_buttonCompressedAir_clicked() {

  //  myActiveSystems[CW_] = false;
  //  myActiveSystems[CA] = true;
  ui->buttonCW->setChecked(false);

  coolingWater->screenCW->hide();
  compressedAir->screenCA->show();

  // alle anderen ausschalten

  mySystemPtrs[CW_].controlPtr->hide();
  mySystemPtrs[CW_].settingsPtr->hide();

  //  for (int i = 0; i < (int)mySystemPtrs.size(); i++) {
  //    mySystemPtrs[i].controlPtr->hide();
  //    mySystemPtrs[i].settingsPtr->hide();
  //  }

  fControlOrSettingsShow(CA);
  //  if (myActiveSystems[CW_] == true) {
  //    if (myStates[CW_].control == true) {
  //      mySystemPtrs[CW_].settingsPtr->hide();
  //      mySystemPtrs[CW_].controlPtr->show();
  //    } else if (myStates[CW_].settings == true) {
  //      mySystemPtrs[CW_].controlPtr->hide();
  //      mySystemPtrs[CW_].settingsPtr->show();
  //    }
  //  }
}

void MainWindow::on_buttonLO_clicked() {}

void MainWindow::on_actionSettingsCW_triggered() {
  myStates[CW_].control = false;
  myStates[CW_].settings = true;
  if (ui->buttonCW->isChecked() == true) {
    fControlOrSettingsShow(CW_);
  }
}

void MainWindow::on_actionControlCW_triggered() {
  myStates[CW_].control = true;
  myStates[CW_].settings = false;
  if (ui->buttonCW->isChecked() == true) {
    fControlOrSettingsShow(CW_);
  }
}
