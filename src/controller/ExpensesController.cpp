#include "ExpensesController.hpp"

ExpensesController::ExpensesController() : m_model(ExpenseModel::getInstance()), m_logger(DebugUtils::getInstance()) {}

ExpensesController& ExpensesController::getInstance() {
    static ExpensesController instance;
    return instance;
}

bool ExpensesController::add(QString category, double amount, QString date) {
    m_logger.debugLog("Signal for add expense received", "CONTROLLER", "INFO");
    if (m_model.find(category, date) == -1)
        return m_model.add(category, amount, date);

    m_logger.debugLog("Expense with given category and date already exists", "CONTROLLER", "WARN");
    return false;
}

bool ExpensesController::remove(QString category, double amount, QString date) {
    m_logger.debugLog("Signal for removing expense received", "CONTROLLER", "INFO");
    int idx = m_model.find(category, date);
    if (idx != -1)
        return m_model.remove(category, date, idx);

    m_logger.debugLog("Couldn't find given expense", "CONTROLLER", "WARN");
    return false;
}

QJsonArray ExpensesController::getExpenses() {
    return m_model.getExpenses();
}