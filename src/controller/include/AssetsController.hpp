#pragma once

#include <QObject>
#include <QJsonDocument>
#include <string>
#include <QTimer>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include "GeneralUtils.hpp"
#include "InvestsController.hpp"
#include "ApiServices.hpp"
#include "AssetModel.hpp"
#include "DebugUtils.hpp"

/**
 * @class AssetsController
 * @brief Singleton controller managing asset portfolio data and real-time updates.
 * 
 * AssetsController serves as the central management system for financial assets
 * including stocks and cryptocurrencies. It provides functionality for adding,
 * removing, and tracking assets with real-time price updates via API integration.
 * The controller maintains separate table models for stocks and crypto assets,
 * handles portfolio statistics calculation, and provides live market data updates
 * through a timer-based system.
 */
class AssetsController : public QObject {
    Q_OBJECT
    
private:
    AssetModel& m_model;
    DebugUtils& m_logger;
    QTimer* m_timer;
    ApiServices& m_api;
    GeneralUtils* m_utils;
    QStandardItemModel* m_stockTable;
    QStandardItemModel* m_cryptoTable;

    static const int LIVE_UPDATE_INTERVAL;
    enum AssetColumns {
        SYMBOL = 0,
        QUANTITY = 1,
        PRICE = 2,
        DAILY_CHANGE_PERCENT = 3,
        DAILY_CHANGE_DOLLAR = 4,
        TOTAL_VALUE = 5,
        COLUMN_COUNT = 6
    };
    
    /**
     * @brief Private constructor implementing singleton pattern.
     * 
     * Initializes the assets controller with necessary dependencies,
     * sets up table models, and establishes connections with other
     * system components. Called only once during singleton instantiation.
     */
    AssetsController();
    
    /**
     * @brief Establishes signal-slot connections for asset management.
     * 
     * Sets up internal connections between components, API response
     * handlers, timer events, and UI update signals. Called during
     * initialization to ensure proper communication flow.
     */
    void setupConnections();

public:
    static const QStringList ASSET_HEADERS;
    
    /**
     * @brief Returns the singleton instance of AssetsController.
     * 
     * Implements the singleton design pattern to ensure only one
     * instance of the assets controller exists throughout the application
     * lifecycle, providing centralized asset management.
     * 
     * @return Pointer to the singleton AssetsController instance.
     */
    static AssetsController* getInstance();
    
    /**
     * @brief Adds a new asset to the portfolio and database.
     * 
     * Creates a new asset entry with the specified symbol, quantity, and type.
     * Updates both the database and corresponding table model, then triggers
     * initial price fetch for the new asset.
     * 
     * @param symbol The asset symbol or ticker (e.g., "AAPL", "BTC")
     * @param quantity The quantity of the asset to add
     * @param type Integer representing asset type (stock/crypto classification)
     * 
     * @return true if the asset was successfully added, false if addition
     *         failed due to validation errors or database issues.
     */
    bool add(const QString& symbol, double quantity, int type);
    
    /**
     * @brief Updates asset data in the appropriate table model.
     * 
     * Updates the table display with current market data for the specified
     * asset, including price, daily changes, and calculated total values.
     * Automatically determines the correct table (stock/crypto) based on
     * asset type and updates the corresponding row.
     * 
     * @param symbol The asset symbol to update
     * @param price Current market price of the asset
     * @param d Daily dollar change amount
     * @param dp Daily percentage change
     * @param type Asset type determining target table
     */
    void updateTable(const QString& symbol, double price, double d, double dp, int type);
    
    /**
     * @brief Removes the specified quantity of an asset from the portfolio.
     * 
     * Reduces or completely removes an asset from the portfolio and database.
     * If the specified quantity equals or exceeds the owned quantity, the
     * asset is completely removed. Otherwise, the quantity is reduced by
     * the specified amount.
     * 
     * @param symbol The asset symbol to remove/reduce
     * @param quantity The quantity to remove from the portfolio
     * 
     * @return true if the removal was successful, false if the operation
     *         failed due to insufficient quantity or database errors.
     */
    bool remove(const QString& symbol, double quantity);
    
    /**
     * @brief Enables automatic live price updates at specified intervals.
     * 
     * Activates the timer-based system for periodic asset price updates,
     * fetching current market data at the specified time interval.
     * 
     * @param time Update interval in milliseconds between price fetches
     */
    void enableLiveUpdates(int time);
    
    /**
     * @brief Disables automatic live price updates.
     * 
     * Stops the timer-based price update system, preventing further
     * automatic API calls for market data.
     */
    void disableLiveUpdates();
        
    /**
     * @brief Returns the stock assets table model.
     * 
     * Provides access to the QStandardItemModel containing stock asset
     * data for UI binding and display purposes.
     * 
     * @return Pointer to the stock table model, or nullptr if not initialized.
     */
    QStandardItemModel* getStockTable();
    
    /**
     * @brief Returns the cryptocurrency assets table model.
     * 
     * Provides access to the QStandardItemModel containing cryptocurrency
     * asset data for UI binding and display purposes.
     * 
     * @return Pointer to the crypto table model, or nullptr if not initialized.
     */
    QStandardItemModel* getCryptoTable();
    
    /**
     * @brief Retrieves all assets as a JSON array.
     * 
     * Returns a comprehensive JSON representation of all portfolio assets
     * including symbols, quantities, types, and current market data.
     * 
     * @return QJsonArray containing all asset data in JSON format.
     */
    QJsonArray getAssets();
    
    /**
     * @brief Determines the asset type for a given symbol.
     * 
     * Looks up and returns the asset type classification for the
     * specified symbol, helping distinguish between stocks and
     * cryptocurrencies for proper handling and display.
     * 
     * @param symbol The asset symbol to classify
     * @return Integer representing the asset type, or -1 if symbol not found.
     */
    int getType(const QString& symbol);
    
    /**
     * @brief Initiates API fetch for all portfolio asset prices.
     * 
     * Triggers API calls to retrieve current market data for all assets
     * in the portfolio. Updates table models and statistics upon successful
     * data retrieval.
     */
    void fetchAssets();
    
    /**
     * @brief Configures and initializes an asset table view.
     * 
     * Sets up the provided table model and view with appropriate headers,
     * column sizing, selection behavior, and styling for asset display.
     * Utility function for consistent table configuration across the UI.
     * 
     * @param model The QStandardItemModel to configure
     * @param view The QTableView to bind and configure
     */
    void setupAssetTable(QStandardItemModel* model, QTableView* view);
    
    /**
     * @brief Calculates portfolio statistics and emits update signal.
     * 
     * Computes current portfolio value, daily changes, total investments,
     * and other performance metrics based on current asset data. Emits
     * the updatedStats signal with calculated values for UI updates.
     */
    void updateStats();
    
    /**
     * @brief Loads existing assets from database to table models.
     * 
     * Retrieves stored asset data from the database and populates
     * the appropriate table models for display. Called during
     * application startup to restore previous portfolio state.
     */
    void loadAssets();

    /**
     * @brief Retrieves the top 3 performing stocks based on daily percentage change
     * 
     * Analyzes all stocks in the stock table and returns the top 3 performers
     * sorted by their daily percentage change in descending order.
     * 
     * @return vector<QString> A vector containing 0-3 strings, each formatted as:
     *         "SYMBOL|PRICE|CHANGE_PERCENT".
     *         Returns empty vector if no valid stock data is available.
     */
    vector<QString> getLeadStocks();
    
    AssetsController(const AssetsController&) = delete;
    AssetsController& operator=(const AssetsController&) = delete;
    
signals:
    /**
     * @brief Signal emitted when an asset's market data is updated.
     * 
     * Notifies connected components when fresh market data has been
     * received and processed for a specific asset. Used to trigger
     * UI updates and dependent calculations.
     * 
     * @param symbol The updated asset symbol
     * @param currPrice Current market price
     * @param d Daily dollar change
     * @param dp Daily percentage change
     * @param type Asset type classification
     */
    void updatedAsset(const QString& symbol, double currPrice, double d, double dp, int type);
    
    /**
     * @brief Signal emitted when portfolio statistics are recalculated.
     * 
     * Provides updated portfolio-wide statistics including total value,
     * daily changes, and investment totals. Used by UI components to
     * display current portfolio performance metrics.
     * 
     * @param pvalue Total portfolio value (default: 0)
     * @param dchange Total daily change in dollars (default: 0)
     * @param invests Total invested amount (default: 0)
     */
    void updatedStats(double pvalue = 0, double dchange = 0, double invests = 0);
};