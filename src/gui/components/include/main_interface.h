#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H
#include <QMainWindow>
#include <QDateTime>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainInterface; }
QT_END_NAMESPACE

class MainInterface : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainInterface *m_ui;

public:
    /**
     * @brief Constructor function for main interface.
     */
    explicit MainInterface(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for main interface.
     */
    ~MainInterface();

    /**
     * @brief Loads the qss into the ui file.
     */
    void loadStyles(const char* stylePath);
};

#endif
