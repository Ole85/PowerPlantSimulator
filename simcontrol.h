#ifndef SIMCONTROL_H
#define SIMCONTROL_H

#include <QWidget>

namespace Ui {
class SimControl;
}

class SimControl : public QWidget {
  Q_OBJECT

public:
  explicit SimControl(QWidget *parent = nullptr);
  ~SimControl();

private slots:

  void on_buttonStopClock_clicked();

  void on_buttonStartClock_clicked();

signals:
  void signalStopClock();
  void signalStartClock();

private:
  Ui::SimControl *ui;
};

#endif // SIMCONTROL_H
