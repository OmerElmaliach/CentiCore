#pragma once

#include <QObject>
#include <QStringListModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QLocale>
#include <vector>
#include "ExpenseModel.hpp"
#include "DebugUtils.hpp"

/**
 * @class ExpensesController
 * @brief Singleton controller managing expense data operations and UI synchronization.
 * 
 * ExpensesController serves as the central management hub for all expense-related
 * operations in the application. It implements the MVC (Model-View-Controller) pattern
 * by acting as an intermediary between the ExpenseModel (data layer) and UI components.
 * The controller maintains a QStringListModel that provides formatted expense data
 * suitable for direct display in UI components like QListView or QComboBox.
 */
class ExpensesController : public QObject {
    Q_OBJECT

private:
    ExpenseModel& m_model;
    DebugUtils& m_logger;
    QStringListModel* m_list;

    /**
     * @brief Private constructor implementing singleton pattern.
     * 
     * Initializes the controller with references to required dependencies
     * and creates the UI string list model.
     */
    ExpensesController();

public:
    /**
     * @brief Gets the singleton instance of ExpensesController.
     * @return Pointer to the singleton ExpensesController instance
     */
    static ExpensesController* getInstance();

    /**
     * @brief Adds a new expense to the system with duplicate checking.
     * 
     * Creates a new expense entry with the specified parameters. Performs validation
     * to prevent duplicate expenses (same category and date) and updates both the
     * persistent storage and the UI display model. Emits expenseCreated signal on success.
     * 
     * @param category The expense category (e.g., "Food", "Transportation", "Entertainment")
     * @param amount The monetary amount of the expense (must be positive)
     * @param date The date of the expense in string format (format depends on model implementation)
     * 
     * @return true if the expense was successfully added, false if duplicate exists or operation failed
     */
    bool add(const QString& category, double amount, const QString& date);

    /**
     * @brief Removes an existing expense from the system.
     * 
     * Locates and removes an expense entry matching the specified parameters.
     * The removal affects both persistent storage and the UI display model.
     * 
     * @param category The category of the expense to remove
     * @param amount The amount of the expense to remove
     * @param date The date of the expense to remove
     */
    bool remove(const QString& category, double amount, const QString& date);

    /**
     * @brief Provides access to the UI-ready expense list model.
     * 
     * Returns a pointer to the QStringListModel containing formatted expense entries
     * suitable for direct use in Qt UI components. The model is automatically updated
     * when expenses are added or removed.
     * 
     * @return Pointer to QStringListModel containing formatted expense strings
     */
    QStringListModel* getList();

    /**
     * @brief Retrieves raw expense data in JSON format.
     * Returns expense data as a JSON array containing all expense objects.
     * 
     * @return QJsonArray containing all expense data objects
     */
    QJsonArray getExpenses();

    /**
     * @brief Loads expense data from persistent storage and updates UI model.
     * 
     * Retrieves all expense data from the model, populates the UI string list model
     * with formatted entries, calculates the total expenses, and emits the
     * expensesLoaded signal with the calculated total.
     */
    void loadExpenses();

    /**
     * @brief Retrieves the total expenses for a specific month of a given year.
     * 
     * @param year The year for which expenses should be calculated.
     * @param month The month for which expenses should be calculated.
     * @return The total sum of expenses for the specified month.
     * 
     * This function queries the expense model for all entries that match the given
     * year and month, sums their values, and returns the result.
     */
    double getMonth(const QString& year, const QString& month);

    /**
     * @brief Retrieves monthly expense totals for a specific year.
     * 
     * @param year The year for which monthly expenses should be calculated.
     * @return A vector of 12 doubles, each representing the total expenses for the corresponding month (January = index 0, December = index 11).
     * 
     * This function queries the expense model for all entries in the specified year,
     * calculates the total expenses for each month, and returns them as a vector.
     */
    vector<double> getYear(const QString& year);

    ExpensesController(const ExpensesController&) = delete;
    ExpensesController& operator=(const ExpensesController&) = delete;

signals:
    /**
     * @brief Signal emitted when a new expense is successfully created.
     * 
     * This signal notifies connected UI components that a new expense has been
     * added to the system, allowing them to update displays, totals, or perform
     * other related actions.
     * 
     * @param category The category of the newly created expense
     * @param amount The amount of the newly created expense
     */
    void expenseCreated(const QString& category, double amount);

    /**
     * @brief Signal emitted when expense data loading is completed.
     * 
     * This signal is emitted after loadExpenses() completes, providing the
     * calculated total of all loaded expenses. UI components can use this
     * to update summary displays and total indicators.
     * 
     * @param totalExp The calculated total of all loaded expenses
     */
    void expensesLoaded(double totalExp);
};