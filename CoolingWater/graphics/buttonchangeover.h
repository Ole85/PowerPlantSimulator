#ifndef BUTTONCHANGEOVER_H
#define BUTTONCHANGEOVER_H

#include <QPushButton>

class ButtonChangeover : public QPushButton {
  Q_OBJECT
public:
  explicit ButtonChangeover(QWidget *parent = nullptr);
  void nextCheckState() override;
signals:
};

#endif // BUTTONCHANGEOVER_H
