#include "ExpensesController.hpp"

ExpensesController::ExpensesController() : m_model(ExpenseModel::getInstance()), m_logger(DebugUtils::getInstance()) {
    m_list = new QStringListModel(this);
}

ExpensesController* ExpensesController::getInstance() {
    static ExpensesController* instance = new ExpensesController();
    return instance;
}

bool ExpensesController::add(const QString& category, double amount, const QString& date) {
    m_logger.debugLog("ExpensesController: Signal for add expense received", "CONTROLLER", "INFO");
    if (m_model.find(category, date) == -1 && m_model.add(category, amount, date)) {
        // Update expense list
        QStringList currList = m_list->stringList();
        currList.append(category + " " + QString::number(amount) + " $");
        m_list->setStringList(currList);

        // Signal to view
        emit expenseCreated(category, amount);
        return true;
    }

    m_logger.debugLog("ExpensesController: Expense with given category and date already exists", "CONTROLLER", "WARN");
    return false;
}

bool ExpensesController::remove(const QString& category, double amount, const QString& date) {
    m_logger.debugLog("ExpensesController: Signal for removing expense received", "CONTROLLER", "INFO");
    int idx = m_model.find(category, date);
    if (idx != -1)
        return m_model.remove(category, date, idx);

    m_logger.debugLog("ExpensesController: Couldn't find given expense", "CONTROLLER", "WARN");
    return false;
}

QStringListModel* ExpensesController::getList() {
    return m_list;
}

void ExpensesController::loadExpenses() {
    double totalExp = 0;
    QJsonArray data = getExpenses();
    QStringList curr = m_list->stringList();

    // Add each monthly expense
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        curr.append(item["category"].toString() + " " + QString::number(item["amount"].toDouble()) + " $");
        totalExp += item["amount"].toDouble();
    }

    m_list->setStringList(curr);
    m_logger.debugLog("ExpensesController: Loaded previous monthly expenses", "CONTROLLER", "INFO");

    emit expensesLoaded(totalExp);
}

QJsonArray ExpensesController::getExpenses() {
    return m_model.getExpenses();
}