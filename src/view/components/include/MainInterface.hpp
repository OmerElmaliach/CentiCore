#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMouseEvent>
#include <QCursor>
#include <QPoint>
#include "DebugUtils.hpp"
class AppController;

QT_BEGIN_NAMESPACE
namespace Ui { class MainInterface; }
QT_END_NAMESPACE

class MainInterface : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainInterface *m_ui;
    QPoint m_dragPosition;
    bool m_dragging = false;
    DebugUtils& m_logger;
    AppController* m_controller;

public:
    /**
     * @brief Constructor function for main interface.
     */
    explicit MainInterface(AppController* controller, QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for main interface.
     */
    ~MainInterface();

    /**
     * @brief Loads the qss into the ui file.
     */
    void loadStyles(const char* stylePath);

    /**
     * @brief Define and load window functionality.
     */
    void loadFuncs();

    /**
     * @brief Event filter for main window.
     */
    bool eventFilter(QObject *object, QEvent *event) override;
};
