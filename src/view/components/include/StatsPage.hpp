#pragma once

#include <QMainWindow>
#include <QDesktopServices>
#include "Logger.hpp"
#include "Utils.hpp"
#include "WindowDragFilter.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class StatsPage; }
QT_END_NAMESPACE

class StatsPage : public QMainWindow {
    Q_OBJECT

private:
    Ui::StatsPage* m_ui;
    Logger& m_logger;

    /**
     * @brief Initializes and connects all UI signals to their respective slots
     * @details Sets up window controls, navigation buttons, dialog connections, and controller signals
     */
    void setupConnections();

public:
    // Constructor
    StatsPage(QWidget* parent = nullptr);

signals:
    /**
     * @brief Signal emitted when navigation to another page is requested.
     * 
     * Emitted when the user clicks navigation buttons (e.g., stocks button) to
     * request a page change. The AppContainer listens to this signal to perform
     * the actual page switching.
     */
    void switchPage(int index);
};