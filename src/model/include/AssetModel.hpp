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
class AssetModel {
private:
    QFile m_dataFile;
    DebugUtils& m_logger;
    QJsonArray m_data;

    /**
     * @brief Constructor for the asset storage.
     */
    AssetModel();

public:
    /**
     * @brief Returns the instance of the asset storage.
     */
    static AssetModel& getInstance();

    /**
     * @brief Adds an asset to the db.
     */
    bool add(const QString& symbol, double quantity, double currPrice, const QString& lastUpdated, int type);

    /**
     * @brief Removes an asset from the db.
     */
    bool remove(const QString& symbol, double quantity, int idx);

    /**
     * @brief Updates the current price of an asset
     */
    bool update(const QString& symbol, double currPrice);

    /**
     * @brief Finds and returns the first index of a given asset.
     */
    int find(const QString& symbol);

    /**
     * @brief Returns type of asset
     */
    int getType(const QString& symbol);

    /**
     * @brief Returns an array of current monthly assets.
     */
    QJsonArray getAssets();

    AssetModel(const AssetModel&) = delete;
    
    AssetModel& operator=(const AssetModel&) = delete;
};