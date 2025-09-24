#include "ApiServices.hpp"

ApiServices::ApiServices(QObject *parent) : m_logger(Logger::getInstance()) {
    m_manager = new QNetworkAccessManager(this);
}

ApiServices& ApiServices::getInstance() {
    static ApiServices instance;
    return instance;
}

void ApiServices::getAsset(const QString& symbol) {
    QNetworkRequest request;
    request.setUrl(QUrl("https://finnhub.io/api/v1/quote?symbol=" + symbol));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Finnhub-Token", EnvLoader::getValue("FINNHUB_API_KEY").toLocal8Bit());
    
    QNetworkReply* reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            emit assetDataReceived(symbol, doc);
        } else {
            emit assetRequestFailed(symbol, reply->errorString());
        }
        reply->deleteLater();
    });
}