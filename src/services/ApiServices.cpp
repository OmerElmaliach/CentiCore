#include "ApiServices.hpp"

ApiServices::ApiServices() : m_logger(DebugUtils::getInstance()) {
    m_manager = new QNetworkAccessManager(this);
}

ApiServices::~ApiServices() {
    free(m_manager);
}

void ApiServices::getAsset(const QString& symbol) {
    QNetworkRequest request;
    QSettings settings(":/config/config/app.conf", QSettings::IniFormat);
    request.setUrl(QUrl("https://finnhub.io/api/v1/quote?symbol=" + symbol));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Finnhub-Token", settings.value("FINNHUB_API_KEY").toString().toLocal8Bit());
    
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