#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "DebugUtils.hpp"
#include "EnvLoader.hpp"

class ApiServices : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager* m_manager;
    DebugUtils& m_logger;

    /**
     * @brief Constructor for api services.
     */
    ApiServices(QObject *parent = nullptr);

public:
    static ApiServices& getInstance();

    /**
     * @brief Retrieves information regarding an asset symbol
     */
    void getAsset(const QString& symbol);

    ApiServices(const ApiServices&) = delete;
    ApiServices& operator=(const ApiServices&) = delete;

signals:
    void assetDataReceived(const QString& symbol, const QJsonDocument& data);
    void assetRequestFailed(const QString& symbol, const QString& error);
};