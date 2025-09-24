#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QStackedWidget>
#include <stdexcept>
#include "MainPage.hpp"
#include "AssetPage.hpp"
#include "Logger.hpp"

/**
 * @class AppContainer
 * @brief Main application window container that manages multi-page navigation.
 * 
 * AppContainer serves as the root window of the application, providing a frameless
 * main window that contains a QStackedWidget for managing different application pages.
 * It handles page switching through signals and slots, and provides error logging.
 */
class AppContainer : public QMainWindow {
    Q_OBJECT

private:
    QStackedWidget* m_stack;
    Logger& m_logger;

public:
    /**
     * @brief Constructs the application container.
     * 
     * Initializes the main window with frameless appearance and sets up
     * the internal page management system. The constructor automatically
     * calls setupConnections() to initialize the UI components.
     * 
     * @param parent Optional parent widget. Defaults to nullptr for top-level window.
     * 
     * @note The window is created with Qt::FramelessWindowHint for custom styling.
     */
    AppContainer(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Switches the currently displayed page.
     * 
     * Changes the active page in the stacked widget to the specified index.
     * Provides error handling and logging for invalid indices.
     * 
     * @note This slot is connected to signals from child pages for navigation.
     */
    void switchPage(int index);

private:
    /**
     * @brief Initializes UI components and signal-slot connections.
     * 
     * Creates the page instances, sets up the QStackedWidget,
     * and establishes signal-slot connections for page navigation. This method
     * is called automatically during construction.
     */
    void setupConnections();
};