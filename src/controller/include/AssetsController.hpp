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
     * @brief Constructor for AssetsController
     */
    AssetsController();

    /**
     * @brief Once time setup of connections
     */
    void setupConnections();

public:
    static const QStringList ASSET_HEADERS;

    static AssetsController* getInstance();

    /**
     * @brief Adds an asset to the db and table
     */
    bool add(const QString& symbol, double quantity, int type);

    /**
     * @brief Updates the asset table
     */
    void updateTable(const QString& symbol, double price, double d, double dp, int type);

    /**
     * @brief removes an asset from the db
     */
    bool remove(const QString& symbol, double quantity);

    /**
     * @brief Enable dynamic updating of assets
     */
    void enableLiveUpdates(int time);

    /**
     * @brief Disable dynamic updating of assets
     */
    void disableLiveUpdates();

    // Getters
    
    QStandardItemModel* getStockTable();
    QStandardItemModel* getCryptoTable();
    QJsonArray getAssets();

    /**
     * @brief Returns type of asset
     */
    int getType(const QString& symbol);

    /**
     * @brief Fetches asset data from api
     */
    void fetchAssets();

    /**
     * @brief utility function to setup tables
     */
    void setupAssetTable(QStandardItemModel* model, QTableView* view);

    /**
     * @brief Calculates stats and sends signal to view
     */
    void updateStats();

    /**
     * @brief Loads up existing assets to the table list
     */
    void loadAssets();

    AssetsController(const AssetsController&) = delete;
    AssetsController& operator=(const AssetsController&) = delete;

signals:
    void updatedAsset(const QString& symbol, double currPrice, double d, double dp, int type);
    void updatedStats(double pvalue = 0, double dchange = 0, double invests = 0);
};