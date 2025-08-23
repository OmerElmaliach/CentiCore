#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>
#include <QJsonObject>
#include <QDateTime>
#include <string>
#include "Expense.hpp"
#include "DebugUtils.hpp"
#define LOG_MSG_LENGTH 256
using namespace std;

// Singleton
class ExpenseModel {
private:
    QFile m_dataFile;
    DebugUtils& m_logger;
    QJsonArray m_data;

    /**
     * @brief Constructor for the expense storage.
     */
    ExpenseModel();

public:
    /**
     * @brief Returns the instance of the expense storage.
     */
    static ExpenseModel& getInstance();

    /**
     * @brief Adds an expense to the db.
     */
    bool add(Expense exp);

    /**
     * @brief removes an expense from the db.
     */
    bool remove(Expense exp, int idx);

    /**
     * @brief Finds and returns the first index of a given expense.
     */
    int find(Expense exp);

    /**
     * @brief Returns an array of current monthly expenses.
     */
    QJsonArray getExpenses();

    ExpenseModel(const ExpenseModel&) = delete;
    
    ExpenseModel& operator=(const ExpenseModel&) = delete;
};