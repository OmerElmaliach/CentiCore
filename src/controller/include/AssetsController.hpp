#pragma once

#include <QObject>
#include <QJsonDocument>
#include <string>
#include <QTimer>
#include "ApiServices.hpp"
#include "AssetModel.hpp"
#include "DebugUtils.hpp"

class AssetsController : public QObject {
    Q_OBJECT

private:
    AssetModel& m_model;
    DebugUtils& m_logger;

    /**
     * @brief Constructor for AssetsController
     */
    AssetsController();

public:

    static AssetsController& getInstance();

    /**
     * @brief Adds an asset
     */
    bool add(QString symbol, double quantity, double currPrice, int type);

    /**
     * @brief removes an asset.
     */
    bool remove(QString symbol, double quantity);

    /**
     * @brief Updates asset price and daily percentage using timer
     */
    void update();

    /**
     * @brief Returns monthly asset data
     */
    QJsonArray getAssets();

    /**
     * @brief Returns type of asset
     */
    int getType(QString symbol);

    AssetsController(const AssetsController&) = delete;
    
    AssetsController& operator=(const AssetsController&) = delete;

signals:
    void updateAsset(QString symbol, double currPrice, double d, double dp, int type);
    void updateStats();
};