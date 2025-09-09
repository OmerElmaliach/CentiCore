#include "AssetsController.hpp"

AssetsController::AssetsController() : m_model(AssetModel::getInstance()), m_logger(DebugUtils::getInstance()) {}

AssetsController& AssetsController::getInstance() {
    static AssetsController instance;
    return instance;
}

bool AssetsController::add(string symbol, double shares, double currPrice, int type) {
    m_logger.debugLog("Signal for add asset shares received", "CONTROLLER", "INFO");
    // TODO: Add symbol verifier
    Asset item(symbol, shares, currPrice, type);
    return m_model.add(item);
}

bool AssetsController::remove(string symbol, double shares) {
    m_logger.debugLog("Signal for removing asset shares received", "CONTROLLER", "INFO");
    int idx = m_model.find(symbol);
    if (idx != -1)
        return m_model.remove(symbol, shares, idx);

    m_logger.debugLog("Couldn't find given asset: " + symbol, "CONTROLLER", "WARN");
    return false;
}

void AssetsController::update() {
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, [&]() {
        ApiServices* api = new ApiServices();
        connect(api, &ApiServices::assetDataReceived, this, [](const QString& symbol, const QJsonDocument& data) {
            qDebug() << "Received data for" << symbol << ":" << data;
        });

        api->getAsset("AAPL");
    });

    timer->start(2000);
}

QJsonArray AssetsController::getAssets() {
    return m_model.getAssets();
}