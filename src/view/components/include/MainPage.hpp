#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include "CreateExpenseDialog.hpp"
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainPage; }
QT_END_NAMESPACE

class MainPage : public QMainWindow {
    Q_OBJECT

private:
    static constexpr int STOCKS_PAGE = 1;
    const char* PAGE_UI = ":/styles/qss/main_page.qss";
    Ui::MainPage *m_ui;
    DebugUtils& m_logger;
    QStringListModel *m_model;

public:
    /**
     * @brief Constructor function for main page.
     */
    explicit MainPage(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for main page.
     */
    ~MainPage();

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
