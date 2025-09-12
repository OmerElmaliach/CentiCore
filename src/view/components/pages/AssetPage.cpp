#include "AssetPage.hpp"
#include "../../ui/ui_asset_page.h"

AssetPage::AssetPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::AssetPage),
        m_logger(DebugUtils::getInstance()),
        m_asset_cont(AssetsController::getInstance()),
        m_utils(GeneralUtils::getInstance()) {
    m_logger.debugLog("AssetPage: Performing UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup assets model
    m_asset_cont->setupAssetTable(m_asset_cont->getStockTable(), m_ui->stocksView);
    m_asset_cont->setupAssetTable(m_asset_cont->getCryptoTable(), m_ui->cryptoView);

    m_invest_model = new QStringListModel(this);
    m_ui->investsView->setModel(m_invest_model);

    // Load functions and styles
    loadBtns();
    loadStyles(PAGE_UI);
    loadInvests();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("AssetPage: UI setup completed", "VIEW", "INFO");

    connect(m_asset_cont, &AssetsController::updatedAsset, this, &AssetPage::onAssetUpdate);
    connect(m_asset_cont, &AssetsController::updatedStats, this, &AssetPage::updateStats);

    // Start dynamically updating data
    m_asset_cont->enableLiveUpdates(6000);
}

AssetPage::~AssetPage() {
    m_asset_cont->disableLiveUpdates();
}

void AssetPage::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("AssetPage: Failed to load style file stocks.ui", "VIEW", "ERR");
    }
}

void AssetPage::loadBtns() {
    // Exit window button
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("AssetPage: Exit pressed, program shutdown...", "VIEW", "INFO");
        this->window()->close();
    });

    // Minimize window button
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("AssetPage: Minimizing window", "VIEW", "INFO");
        this->window()->setWindowState(Qt::WindowMinimized);
    });

    // Move to dashboard
    connect(m_ui->dashBoard_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("AssetPage: Switching to dashboard page", "VIEW", "INFO");
        emit switchPage(0);
    });

    // Add stock button
    connect(m_ui->addStock_btn, &QPushButton::clicked, this, [this] {
        CreateAssetDialog dialog(0, this);
        dialog.exec();
    });

    // Add crypto button
    connect(m_ui->addCrypto_btn, &QPushButton::clicked, this, [this] {
        CreateAssetDialog dialog(1, this);
        dialog.exec();
    });

    // Add investment button
    connect(m_ui->addInvest_btn, &QPushButton::clicked, this, [this] {
        CreateInvestDialog dialog(this);
        connect(&dialog, &CreateInvestDialog::investCreated, this, &AssetPage::onInvestCreate);
        dialog.exec();
    });
}

void AssetPage::onAssetUpdate() {
    // TODO: Add animation
}

void AssetPage::onInvestCreate(double amount) {
    QStringList currList = m_invest_model->stringList();
    double currTot = m_ui->investsNum->text().remove('$').toDouble();

    // Update investment list
    currList.append(QString::number(amount) + "$");
    m_invest_model->setStringList(currList);
    m_ui->investsNum->setText(QString::number(currTot + amount) + "$");

    m_logger.debugLog("AssetPage: Added investment to list", "VIEW", "INFO");
}

void AssetPage::loadInvests() {
    double sumInv = 0;
    m_ui->investsNum->setText("0");
    QJsonArray data = InvestsController::getInstance().getInvestments();
    QStringList curr = m_invest_model->stringList();

    // Add each investment made
    for (int i = 0; i < data.size(); i++) {
        QJsonObject item = data[i].toObject();
        curr.append(QString::number(item["amount"].toDouble()) + "$");
        sumInv += item["amount"].toDouble();
    }

    m_ui->investsNum->setText(QString::number(sumInv) + "$");
    m_invest_model->setStringList(curr);
    m_logger.debugLog("AssetPage: Loaded previous investments", "VIEW", "INFO");
}

void AssetPage::updateStats(double pvalue, double dchange, double invests) {
    m_ui->valueNum->setText(m_utils->formatNumberWithCommas(pvalue, 2) + " $");
    m_ui->balanceNum->setText(m_utils->formatNumberWithCommas(pvalue - invests, 2) + " $");
    m_ui->changeNum->setText(m_utils->formatNumberWithCommas(dchange, 2) + " $");

    // Set appropriate colors
    QString color = (pvalue > 0) ? "#00be6f;" : "#a83420ff;";
    m_ui->valueNum->setStyleSheet("color: " + color);

    color = (dchange > 0) ? "#00be6f;" : "#a83420ff;";
    m_ui->balanceNum->setStyleSheet("color: " + color);

    color = (pvalue - invests > 0) ? "#00be6f;" : "#a83420ff;";
    m_ui->changeNum->setStyleSheet("color: " + color);
}