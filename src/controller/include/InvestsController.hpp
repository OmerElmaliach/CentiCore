#pragma once

#include <QObject>
#include <QStringListModel>
#include <string>
#include "InvestModel.hpp"
#include "DebugUtils.hpp"

class InvestsController : public QObject {
    Q_OBJECT

private:
    InvestModel& m_model;
    DebugUtils& m_logger;
    QStringListModel* m_investList;

    /**
     * @brief Constructor for InvestsController
     */
    InvestsController();

public:

    static InvestsController* getInstance();

    /**
     * @brief Adds an investment.
     */
    bool add(double amount, QString date);

    /**
     * @brief Returns all investments.
     */
    QJsonArray getInvestments();

    /**
     * @brief Returns the model list
     */
    QStringListModel* getList();

    /**
     * @brief Return total of all investments
     */
    double getTotal();

    /**
     * @brief Loads up existing investments to the item list
     */
    void loadInvests();

    InvestsController(const InvestsController&) = delete;
    
    InvestsController& operator=(const InvestsController&) = delete;

signals:
    void investCreated(double amount);
};