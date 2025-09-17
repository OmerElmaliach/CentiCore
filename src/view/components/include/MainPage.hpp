#pragma once

#include <QMainWindow>
#include <QString>
#include <QSettings>
#include <QVBoxLayout>
#include "CreateExpenseDialog.hpp"
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "ExpensesController.hpp"
#include "AssetsController.hpp"
#include "GeneralUtils.hpp"
#include "EnvLoader.hpp"
#include "ExpenseChart.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainPage; }
QT_END_NAMESPACE

/**
 * @class MainPage
 * @brief Primary user interface page for expense tracking and application navigation.
 * 
 * MainPage serves as the main dashboard of the expense tracking application. It provides
 * a comprehensive interface for viewing monthly expenses, adding new expenses through
 * dialog interactions, and navigating to other application sections like the stocks page.
 */
class MainPage : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainPage* m_ui;
    DebugUtils& m_logger;
    ExpensesController* m_expense_cont;
    GeneralUtils* m_utils;
    static const int STOCKS_PAGE;
    static const QString POSITIVE_COLOR;
    static const QString NEGATIVE_COLOR;
    static const QString PAGE_UI;
    static const QString TOPBAR_UI;
    static const QString PAGES_WIDGET_UI;

    /**
     * @brief Initializes all UI signal-slot connections.
     * 
     * Sets up connections for:
     * - Window control buttons (exit, minimize)
     * - Expense management (add expense button)
     * - Page navigation (stocks page button)
     * - ExpensesController event handling
     */
    void setupConnections();

    /**
     * @brief Initializes and configures the expense chart.
     * 
     * Sets up the chart with:
     * - Chart title and animation options
     * - Data series and bar sets representing expenses
     * - Axes and labels for proper display
     * - Any additional styling or theme adjustments
     */
    void setupChart();

public:
    /**
     * @brief Constructs the main page with complete UI initialization.
     */
    MainPage(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Handles expense creation events and updates the total display.
     * 
     * Called when a new expense is successfully created through the ExpensesController.
     * Updates the total expense display by adding the new expense amount to the current
     * total and refreshes the UI to reflect the change.
     * 
     * @param category The category name of the created expense (for logging purposes)
     * @param amount The monetary amount of the new expense to add to the total
     */
    void onExpenseCreate(const QString category, double amount);

    /**
     * @brief Updates the total expense display when expense data is loaded.
     * 
     * Called when the ExpensesController finishes loading expense data (typically
     * during application startup or when refreshing data). Sets the total expense
     * display to show the calculated total for the current month,
     * Also updates stats regarding monthly balance.
     * 
     * @param totalExp The calculated total of all expenses for the current period
     */
    void onLoadExpenses(double totalExp);

    /**
     * @brief Updates the net worth statistics display on the main dashboard.
     * 
     * This slot function is called when portfolio statistics need to be refreshed
     * on the main page interface. It updates the net worth display widget with
     * the current total portfolio value, typically triggered by asset price updates.
     * 
     * @param pvalue The current total portfolio value in the base currency.
     *               Represents the sum of all asset values at current market.
     */
    void onUpdateStats(double pvalue);

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