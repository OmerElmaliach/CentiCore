#pragma once

#include <QObject>
#include "../../model/include/ExpenseModel.hpp"
#include "../../utils/DebugUtils.hpp"

class ExpensesController : public QObject {
    Q_OBJECT

private:
    ExpenseModel& m_model;
    DebugUtils& m_logger;
};