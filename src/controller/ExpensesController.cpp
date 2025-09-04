#include "ExpensesController.hpp"

ExpensesController::ExpensesController() : m_model(ExpenseModel::getInstance()), m_logger(DebugUtils::getInstance()) {}

ExpensesController& ExpensesController::getInstance() {
    static ExpensesController instance;
    return instance;
}

bool ExpensesController::add(string date, string category, double amount) {
    m_logger.debugLog("Signal for add expense received", "CONTROLLER", "INFO");
    Expense exp(date, category, amount);
    if (m_model.find(exp) == -1)
        return m_model.add(exp);

    m_logger.debugLog("Expense with given category and date already exists", "CONTROLLER", "WARN");
    return false;
}

bool ExpensesController::remove(string date, string category, double amount) {
    m_logger.debugLog("Signal for removing expense received", "CONTROLLER", "INFO");
    Expense exp(date, category, amount);
    int idx = m_model.find(exp);
    if (idx != -1)
        return m_model.remove(exp, idx);

    m_logger.debugLog("Couldn't find given expense", "CONTROLLER", "WARN");
    return false;
}

QJsonArray ExpensesController::getExpenses() {
    return m_model.getExpenses();
}