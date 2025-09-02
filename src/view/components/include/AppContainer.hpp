#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QStackedWidget>
#include "MainInterface.hpp"
#include "StockInterface.hpp"

class AppContainer : public QMainWindow {
    Q_OBJECT

private:
    QStackedWidget* m_stack;

public:
    /**
     * @brief Constructor function for container.
     */
    explicit AppContainer(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for container.
     */
    ~AppContainer();

    /**
     * @brief Switches between pages according to index in stack.
     */
    void switchPage(int index);
};
