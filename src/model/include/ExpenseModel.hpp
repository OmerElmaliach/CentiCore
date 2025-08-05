#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>
#include <QJsonObject>
#include <QDateTime>
#include <string>
#include "../types/include/Expense.hpp"
#include "../../utils/DebugUtils.hpp"
#define LOG_MSG_LENGTH 256
using namespace std;

// Singleton
class ExpenseModel {
private:
    QFile m_dataFile;
    DebugUtils& m_logger;
    QJsonArray m_data;

    /**
     * Constructor for the expense storage.
     */
    ExpenseModel();

public:
    /**
     * Returns the instance of the expense storage.
     */
    static ExpenseModel& getInstance();

    /**
     * Adds an expense to the db.
     */
    bool add(Expense exp);

    /**
     * removes an expense from the db.
     */
    bool remove(Expense exp, int idx);

    /**
     * Finds and returns the first index of a given expense.
     */
    int find(Expense exp);

    ExpenseModel(const ExpenseModel&) = delete;
    
    ExpenseModel& operator=(const ExpenseModel&) = delete;
};