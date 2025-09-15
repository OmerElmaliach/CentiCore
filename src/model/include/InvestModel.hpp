#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>
#include <QJsonObject>
#include <QDateTime>
#include <string>
#include "DebugUtils.hpp"
#define LOG_MSG_LENGTH 256
using namespace std;

// Singleton
class InvestModel {
private:
    QFile m_dataFile;
    DebugUtils& m_logger;
    QJsonArray m_data;

    /**
     * @brief Constructor for the investment storage.
     */
    InvestModel();

public:
    /**
     * @brief Returns the instance of the investment storage.
     */
    static InvestModel& getInstance();

    /**
     * @brief Adds an investment to the db.
     */
    bool add(double amount, const QString& date);

    /**
     * @brief Returns an array of investments.
     */
    QJsonArray getInvestments();

    InvestModel(const InvestModel&) = delete;
    
    InvestModel& operator=(const InvestModel&) = delete;
};