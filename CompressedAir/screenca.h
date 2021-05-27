#ifndef SCREENCA_H
#define SCREENCA_H

#include "enumsca.h"
#include "myEnums.h"
#include <QLabel>
#include <QWidget>

namespace Ui {
class ScreenCA;
}

class ScreenCA : public QWidget {
  Q_OBJECT
  friend class CompressedAir;

public:
  explicit ScreenCA(QWidget *parent = nullptr);
  ~ScreenCA();
  std::array<QLabel *, 2> labelPtr;
  void fGUIupdateCompressor(int, Status &);
  void fGUIupdateCompressorAll(std::array<Compressor, 2> &);

private:
  Ui::ScreenCA *ui;
};

#endif // SCREENCA_H
