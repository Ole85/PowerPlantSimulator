#ifndef SETTINGSCA_H
#define SETTINGSCA_H

#include <QWidget>

namespace Ui {
class SettingsCA;
}

class SettingsCA : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsCA(QWidget *parent = nullptr);
    ~SettingsCA();

private:
    Ui::SettingsCA *ui;
};

#endif // SETTINGSCA_H
