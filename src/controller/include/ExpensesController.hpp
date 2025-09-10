#pragma once

#include <QObject>
#include <string>
#include "ExpenseModel.hpp"
#include "DebugUtils.hpp"

class ExpensesController : public QObject {
    Q_OBJECT

private:
    ExpenseModel& m_model;
    DebugUtils& m_logger;

    /**
     * @brief Constructor for ExpensesController
     */
    ExpensesController();

public:

    static ExpensesController& getInstance();

    /**
     * @brief Adds an expense.
     */
    bool add(QString category, double amount, QString date);

    /**
     * @brief removes an expense.
     */
    bool remove(QString category, double amount, QString date);

    /**
     * @brief Returns monthly expense data.
     */
    QJsonArray getExpenses();

    ExpensesController(const ExpensesController&) = delete;
    
    ExpensesController& operator=(const ExpensesController&) = delete;
};