#pragma once

#include <QObject>
#include "ExpenseModel.hpp"
#include "Expense.hpp"
#include "DebugUtils.hpp"

class ExpensesController : public QObject {
    Q_OBJECT

private:
    ExpenseModel& m_model;
    DebugUtils& m_logger;

public:
    /**
     * Constructor for ExpensesController
     */
    ExpensesController();

    /**
     * Adds an expense.
     */
    bool add(Expense exp);

    /**
     * removes an expense.
     */
    bool remove(Expense exp);
};