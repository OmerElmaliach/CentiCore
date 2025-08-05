#pragma once

#include <QObject>
#include "../../model/include/ExpenseModel.hpp"
#include "../../model/types/include/Expense.hpp"
#include "../../utils/DebugUtils.hpp"

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