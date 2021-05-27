#include "simcontrol.h"
#include "ui_simcontrol.h"

SimControl::SimControl(QWidget *parent)
    : QWidget(parent), ui(new Ui::SimControl) {
  ui->setupUi(this);
}

SimControl::~SimControl() { delete ui; }

void SimControl::on_buttonStopClock_clicked() { emit signalStopClock(); }

void SimControl::on_buttonStartClock_clicked() { emit signalStartClock(); }
