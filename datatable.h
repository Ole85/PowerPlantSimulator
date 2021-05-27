#ifndef DATATABLE_H
#define DATATABLE_H

#include "myEnums.h"
#include <QTableWidgetItem>
#include <QWidget>

namespace Ui {
class DataTable;
}

class DataTable : public QWidget {
  Q_OBJECT
  friend class MainWindow;

public:
  explicit DataTable(QWidget *parent = nullptr);
  ~DataTable();

  std::array<oneRow_, 10> myData;

  //  void fUpdatePumpsCW(std::array<Pump, 2> &);

public slots:
  void slotUpdatePumpsCW(std::array<Pump, 2> &);

private:
  Ui::DataTable *ui;
};

#endif // DATATABLE_H
