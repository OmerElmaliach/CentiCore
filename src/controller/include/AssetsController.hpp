#pragma once

#include <QObject>
#include <QJsonDocument>
#include <string>
#include <QTimer>
#include "ApiServices.hpp"
#include "AssetModel.hpp"
#include "Asset.hpp"
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
    bool add(string symbol, double shares, double currPrice, int type);

    /**
     * @brief removes an asset.
     */
    bool remove(string symbol, double shares);

    /**
     * @brief Updates asset price and daily percentage using timer
     */
    void update();

    /**
     * @brief Returns monthly asset data
     */
    QJsonArray getAssets();

    AssetsController(const AssetsController&) = delete;
    
    AssetsController& operator=(const AssetsController&) = delete;
};