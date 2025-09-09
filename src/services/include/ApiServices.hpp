#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include "DebugUtils.hpp"

class ApiServices : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager* m_manager;
    DebugUtils& m_logger;

public:
    /**
     * @brief Constructor for api services.
     */
    ApiServices();

    /**
     * @brief Deconstructor for api services.
     */
    ~ApiServices();

    /**
     * @brief Retrieves information regarding an asset symbol
     */
    void getAsset(const QString& symbol);

signals:
    void assetDataReceived(const QString& symbol, const QJsonDocument& data);
    void assetRequestFailed(const QString& symbol, const QString& error);
};