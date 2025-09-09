#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>
#include <QJsonObject>
#include <QDateTime>
#include <string>
#include "Asset.hpp"
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
    bool add(Asset st);

    /**
     * @brief removes an asset from the db.
     */
    bool remove(string symbol, double shares, int idx);

    /**
     * @brief Finds and returns the first index of a given asset.
     */
    int find(string symbol);

    /**
     * @brief Returns an array of current monthly assets.
     */
    QJsonArray getAssets();

    AssetModel(const AssetModel&) = delete;
    
    AssetModel& operator=(const AssetModel&) = delete;
};