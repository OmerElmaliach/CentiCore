#include "AssetPage.hpp"
#include "../ui/ui_asset_page.h"

AssetPage::AssetPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::AssetPage),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Performing AssetPage UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup assets model
    QStringList headers = {"Symbol", "Quantity", "Price per Unit", "Daily change (%)", "Daily change ($)", "Total Value"};

    m_stock_model = new QStandardItemModel();
    m_ui->stocksView->setModel(m_stock_model);
    m_stock_model->setHorizontalHeaderLabels(headers);
    m_ui->stocksView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_crypto_model = new QStandardItemModel();
    m_ui->cryptoView->setModel(m_crypto_model);
    m_crypto_model->setHorizontalHeaderLabels(headers);
    m_ui->cryptoView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Load functions and styles
    loadBtns();
    loadStyles(INTERFACE_UI);
    loadAssets();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("AssetPage UI setup completed", "VIEW", "INFO");
}

AssetPage::~AssetPage() {
    delete m_ui;
}

void AssetPage::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file stocks.ui", "VIEW", "ERR");
    }
}

void AssetPage::loadBtns() {
    // Exit window button
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Exit pressed, program shutdown...", "VIEW", "INFO");
        this->window()->close();
    });

    // Minimize window button
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Minimizing window", "VIEW", "INFO");
        this->window()->setWindowState(Qt::WindowMinimized);
    });

    // Move to dashboard
    connect(m_ui->dashBoard_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Switching to dashboard page", "VIEW", "INFO");
        emit switchPage(0);
    });

    // Add stock button
    connect(m_ui->addStock_btn, &QPushButton::clicked, this, [this] {
        CreateAssetDialog* dialog = new CreateAssetDialog(0);
        connect(dialog, &CreateAssetDialog::assetCreated, this, &AssetPage::onAssetCreate);
        dialog->exec();
    });

    // Add crypto button
    connect(m_ui->addCrypto_btn, &QPushButton::clicked, this, [this] {
        CreateAssetDialog* dialog = new CreateAssetDialog(1);
        connect(dialog, &CreateAssetDialog::assetCreated, this, &AssetPage::onAssetCreate);
        dialog->exec();
    });
}

void AssetPage::onAssetCreate(const QString symbol, QString shares, int type) {
    // Update assets list
    QStandardItemModel* model = (type) ? m_crypto_model : m_stock_model;
    int currRow = model->rowCount();
    model->setItem(currRow, 0, new QStandardItem(symbol));
    model->setItem(currRow, 1, new QStandardItem(shares));

    m_logger.debugLog("Added asset to list", "VIEW", "INFO");
}

void AssetPage::loadAssets() {
    QJsonArray data = AssetsController::getInstance().getAssets();

    // Add each asset
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        QStandardItemModel* model = (item["type"].toInt()) ? m_crypto_model : m_stock_model;
        int currRow = model->rowCount();
        model->setItem(currRow, 0, new QStandardItem(item["symbol"].toString()));
        model->setItem(currRow, 1, new QStandardItem(QString::number(item["shares"].toDouble())));
        // TODO: ADD VALUES WITH JSON REQUEST
        model->setItem(currRow, 2, new QStandardItem("N/A"));
        model->setItem(currRow, 3, new QStandardItem("N/A"));
        model->setItem(currRow, 4, new QStandardItem("N/A"));
        model->setItem(currRow, 5, new QStandardItem("N/A"));
    }

    m_logger.debugLog("Loaded previous assets", "VIEW", "INFO");
}