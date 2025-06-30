#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE

namespace Ui { class MainInterface; }
QT_END_NAMESPACE

class MainInterface : public QMainWindow {
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();

private:
    Ui::MainInterface *ui;
};

#endif
