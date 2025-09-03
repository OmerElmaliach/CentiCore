#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include "CreateExpenseDialog.hpp"
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainInterface; }
QT_END_NAMESPACE

class MainInterface : public QMainWindow {
    Q_OBJECT

private:
    const char* INTERFACE_UI = ":/styles/qss/main_interface.qss";
    Ui::MainInterface *m_ui;
    DebugUtils& m_logger;
    QStringListModel *m_model;

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

    /**
     * @brief Define and load buttons functionality.
     */
    void loadBtns();

    /**
     * @brief Adds an expense to the display widget.
     */
    void onExpenseCreate(const QString category, QString amount);

    /**
     * @brief Loads up existing expenses to the item widget
     */
    void loadExpenses();

signals:
    void switchPage(int index);
};
