#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H
#include <QMainWindow>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainInterface; }
QT_END_NAMESPACE

class MainInterface : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainInterface *m_ui;

public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();
};

#endif
