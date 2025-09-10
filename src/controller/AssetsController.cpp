#include "AssetsController.hpp"

AssetsController::AssetsController() : m_model(AssetModel::getInstance()), m_logger(DebugUtils::getInstance()) {}

AssetsController& AssetsController::getInstance() {
    static AssetsController instance;
    return instance;
}

bool AssetsController::add(QString symbol, double quantity, double currPrice, int type) {
    m_logger.debugLog("AssetsController: Signal for add asset quantity received", "CONTROLLER", "INFO");
    // TODO: Add symbol verifier
    return m_model.add(symbol, quantity, currPrice, QDateTime::currentDateTime().toString("hh:mm:ss"), type);
}

bool AssetsController::remove(QString symbol, double quantity) {
    m_logger.debugLog("AssetsController: Signal for removing asset quantity received", "CONTROLLER", "INFO");
    int idx = m_model.find(symbol);
    if (idx != -1)
        return m_model.remove(symbol, quantity, idx);

    m_logger.debugLog("AssetsController: Couldn't find given asset: " + symbol.toStdString(), "CONTROLLER", "WARN");
    return false;
}

void AssetsController::update() {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this] {
        ApiServices& api = ApiServices::getInstance();
        connect(&api, &ApiServices::assetDataReceived, this, [this](const QString& symbol, const QJsonDocument& data) {
            // Update model
            if (!m_model.update(symbol, data["c"].toDouble()))
                m_logger.debugLog("AssetsController: Failed to update asset: " + symbol.toStdString(), "CONTROLLER", "ERR");
            
            // Update view
            int type = getType(symbol);
            if (type != -1)
                emit updateAsset(symbol, data["c"].toDouble(), data["d"].toDouble(), data["dp"].toDouble(), type);
        });

        connect(&api, &ApiServices::assetRequestFailed, this, [this](const QString& symbol, const QString& error) {
            m_logger.debugLog("AssetsController: Failed to retrieve asset: " + symbol.toStdString() + "ERROR: " + error.toStdString(), "CONTROLLER", "ERR");
        });

        QJsonArray assetArr = getAssets();
        for (int i = 0; i < assetArr.size(); i++) {
            api.getAsset(assetArr[i].toObject()["symbol"].toString());
        }
    });

    timer->start(5000);
}

QJsonArray AssetsController::getAssets() {
    return m_model.getAssets();
}

int AssetsController::getType(QString symbol) {
    return m_model.getType(symbol);
}