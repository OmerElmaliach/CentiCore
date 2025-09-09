#pragma once

#include <QObject>
#include <string>
#include "InvestModel.hpp"
#include "DebugUtils.hpp"

class InvestsController : public QObject {
    Q_OBJECT

private:
    InvestModel& m_model;
    DebugUtils& m_logger;

    /**
     * @brief Constructor for InvestsController
     */
    InvestsController();

public:

    static InvestsController& getInstance();

    /**
     * @brief Adds an investment.
     */
    bool add(double amount, QString date);

    /**
     * @brief Returns all investments.
     */
    QJsonArray getInvestments();

    InvestsController(const InvestsController&) = delete;
    
    InvestsController& operator=(const InvestsController&) = delete;
};