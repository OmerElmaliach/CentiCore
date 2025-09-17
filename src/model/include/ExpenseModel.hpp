#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>
#include <QJsonObject>
#include <string>
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
    bool add(const QString& category, double amount, const QString& date);

    /**
     * @brief removes an expense from the db.
     */
    bool remove(const QString& category, const QString& date, int idx);

    /**
     * @brief Finds and returns the first index of a given expense.
     */
    int find(const QString& category, const QString& date);

    /**
     * @brief Returns an array of current monthly expenses.
     */
    QJsonArray getExpenses();

    /**
     * @brief Returns an array of a specific month.
     */
    QJsonArray getMonth(const QString& year, const QString& month);

    ExpenseModel(const ExpenseModel&) = delete;
    
    ExpenseModel& operator=(const ExpenseModel&) = delete;
};