#include "ExpensesController.hpp"

ExpensesController::ExpensesController() : m_model(ExpenseModel::getInstance()), m_logger(DebugUtils::getInstance()) {}

bool ExpensesController::add(Expense exp) {
    m_logger.debugLog("Signal for add expense received", "CONTROLLER", "INFO");
    if (m_model.find(exp) == -1)
        return m_model.add(exp);

    m_logger.debugLog("Expense with given name and date already exists", "CONTROLLER", "WARNING");
    return false;
}

bool ExpensesController::remove(Expense exp) {
    m_logger.debugLog("Signal for removing expense received", "CONTROLLER", "INFO");
    int idx = m_model.find(exp);
    if (idx != -1)
        return m_model.remove(exp, idx);

    m_logger.debugLog("Couldn't find given expense", "CONTROLLER", "WARNING");
    return false;
}