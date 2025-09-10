#include "AssetModel.hpp"

AssetModel::AssetModel() : m_logger(DebugUtils::getInstance()) {
    QDateTime dt = QDateTime::currentDateTime();
    QString dataPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../data/");
    QDir dir(dataPath);
    if (!dir.exists())
        dir.mkpath(".");

    m_dataFile.setFileName(dataPath + "Assets.json");
    if (m_dataFile.exists()) {
        if (!m_dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
            m_logger.debugLog("Failed to open asset file", "MODEL", "ERR");
        
        // Extract available data from the json file.
        m_data = QJsonDocument().fromJson(m_dataFile.readAll()).array();
        m_dataFile.close();
    }
}

AssetModel& AssetModel::getInstance() {
    static AssetModel instance;
    return instance;
}

bool AssetModel::add(Asset item) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Appending new asset: %s, amount: %.2f", item.getSymbol().c_str(), item.getShares());
    m_logger.debugLog(buff, "MODEL", "INFO");

    int idx = find(item.getSymbol());
    if (idx == -1) {
        // Create new asset and append to array data
        QJsonObject jsonAsset;
        jsonAsset["symbol"] = QJsonValue(item.getSymbol().c_str());
        jsonAsset["shares"] = QJsonValue(item.getShares());
        jsonAsset["current_price"] = QJsonValue(item.getCurrPrice());
        jsonAsset["last_updated"] = QJsonValue(item.getLastUpdated());
        jsonAsset["type"] = QJsonValue(item.getType());
        m_data.append(jsonAsset);
    } else {
        // Update existing asset
        m_data[idx].toObject()["shares"] = QJsonValue(m_data[idx].toObject()["shares"].toDouble() + item.getShares());
    }

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open asset file", "MODEL", "ERR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

bool AssetModel::remove(string symbol, double shares, int idx) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "Removing asset: name: %s, amount: %.2f", symbol.c_str(), shares);
    m_logger.debugLog(buff, "MODEL", "INFO");

    // Check if should remove asset completely or partially
    if (m_data[idx].toObject()["shares"].toDouble() == shares) {
        m_data.removeAt(idx);
    } else {
        m_data[idx].toObject()["shares"] = QJsonValue(m_data[idx].toObject()["shares"].toDouble() - shares);
    }

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open asset file", "MODEL", "ERR");
        return false;
    }
    
    // Push into file
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

bool AssetModel::update(std::string symbol, double currPrice) {
    int idx = find(symbol);
    if (idx == -1) {
        m_logger.debugLog("Unable to find symbol: " + symbol, "MODEL", "ERR");
        return false;
    }

    QJsonObject obj = m_data[idx].toObject();
    obj["current_price"] = QJsonValue(currPrice);
    obj["last_updated"] = QJsonValue(QDateTime::currentDateTime().toString("hh:mm:ss"));
    m_data[idx] = obj;

    if (!m_dataFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        m_logger.debugLog("Failed to open asset file", "MODEL", "ERR");
        return false;
    }
    
    m_dataFile.write(QJsonDocument(m_data).toJson());
    m_dataFile.close();

    return true;
}

int AssetModel::find(string symbol) {
    // Loop and find the asset index
    for (int i = 0; i < m_data.size(); i++) {
        QJsonObject item = m_data[i].toObject();
        if (!item["symbol"].toString().toStdString().compare(symbol))
            return i;
    }

    return -1;
}

QJsonArray AssetModel::getAssets() {
    return m_data;
}

int AssetModel::getType(QString symbol) {
    for (int i = 0; i < m_data.size(); i++) {
        QJsonObject item = m_data[i].toObject();
        if (item["symbol"].toString() == symbol)
            return item["type"].toInt();
    }

    return -1;
}