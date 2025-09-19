#pragma once

#include <QObject>
#include <QStringListModel>
#include <string>
#include "InvestModel.hpp"
#include "Logger.hpp"

/**
 * @class InvestsController
 * @brief Singleton controller managing investment transaction records and calculations.
 * 
 * InvestsController serves as the central management system for tracking investment
 * transactions and capital contributions to the portfolio. It provides functionality
 * for recording investment amounts with dates, calculating total invested capital,
 * and maintaining a list model for UI display. The controller integrates with the
 * investment data model for persistence and provides signals for real-time updates
 * to connected components.
 */
class InvestsController : public QObject {
    Q_OBJECT
    
private:
    InvestModel& m_model;
    Logger& m_logger;
    QStringListModel* m_investList;
    
    /**
     * @brief Private constructor implementing singleton pattern.
     * 
     * Initializes the investments controller with necessary dependencies,
     * sets up the list model, and establishes connections with data storage.
     * Called only once during singleton instantiation to ensure centralized
     * investment management.
     */
    InvestsController();

public:
    /**
     * @brief Returns the singleton instance of InvestsController.
     * 
     * Implements the singleton design pattern to ensure only one instance
     * of the investments controller exists throughout the application lifecycle,
     * providing centralized investment transaction management and preventing
     * data inconsistencies from multiple controller instances.
     * 
     * @return Pointer to the singleton InvestsController instance.
     */
    static InvestsController* getInstance();
    
    /**
     * @brief Records a new investment transaction in the system.
     * 
     * Creates a new investment record with the specified amount and date,
     * updating both the database and the display list model.
     * Emits the investCreated signal upon successful addition to notify
     * connected components of the new investment.
     * 
     * @param amount The investment amount in currency units. Must be positive.
     * @param date The investment date in string format (typically ISO format
     *             or locale-specific format as required by the system).
     * 
     * @return true if the investment was successfully recorded, false if the
     *         operation failed due to validation errors, database issues,
     *         or invalid input parameters.
     */
    bool add(double amount, QString date);
    
    /**
     * @brief Retrieves all investment transactions as a JSON array.
     * 
     * Returns a comprehensive JSON representation of all recorded investment
     * transactions including amounts, dates, and any additional metadata.
     * Useful for data export, reporting, backup operations, or API
     * communication requiring structured investment data.
     * 
     * @return QJsonArray containing all investment transaction data in
     *         JSON format with consistent structure for each record.
     */
    QJsonArray getInvestments();
    
    /**
     * @brief Returns the string list model for UI binding.
     * 
     * Provides access to the QStringListModel containing formatted investment
     * transaction data suitable for display in list views, combo boxes, or
     * other UI components requiring investment selection or display capabilities.
     * 
     * @return Pointer to the investment list model, or nullptr if not
     *         properly initialized during controller construction.
     */
    QStringListModel* getList();
    
    /**
     * @brief Calculates and returns the total of all recorded investments.
     * 
     * Computes the sum of all investment transaction amounts to provide
     * the total capital invested in the portfolio. This value represents
     * the cumulative amount of money contributed to investments over time,
     * excluding any gains, losses, or current market valuations.
     * 
     * @return The total invested amount as a double precision value
     *         representing the sum of all investment transactions.
     */
    double getTotal();
    
    /**
     * @brief Loads existing investment records from storage to the list model.
     * 
     * Retrieves all stored investment transaction data from the database
     * and populates the string list model for immediate UI display.
     */
    void loadInvests();
    
    InvestsController(const InvestsController&) = delete;
    InvestsController& operator=(const InvestsController&) = delete;
    
signals:
    /**
     * @brief Signal emitted when a new investment transaction is created.
     * 
     * Notifies connected components when a new investment has been successfully
     * recorded in the system. Used to trigger UI updates, portfolio statistics
     * recalculation, and other dependent operations that need to respond to
     * changes in invested capital.
     * 
     * @param amount The amount of the newly created investment transaction.
     *               Provides immediate access to the investment value for
     *               connected slots without requiring additional data queries.
     */
    void investCreated(double amount);
};