#include "AssetPage.hpp"
#include "../../ui/ui_asset_page.h"

AssetPage::AssetPage(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::AssetPage),
        m_logger(Logger::getInstance()),
        m_asset_cont(AssetsController::getInstance()),
        m_invest_cont(InvestsController::getInstance()) {
    m_logger.debugLog("AssetPage: Performing UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Setup models
    m_asset_cont->setupAssetTable(m_asset_cont->getStockTable(), m_ui->stocksView);
    m_asset_cont->setupAssetTable(m_asset_cont->getCryptoTable(), m_ui->cryptoView);
    m_ui->investsView->setModel(m_invest_cont->getInstance()->getList());

    // Load connections and styles
    if (!Utils::loadStyles(this, AppConstants::Ui::ASSET_PAGE_UI))
        m_logger.debugLog("AssetPage: Failed to load style file stocks.ui", "VIEW", "ERR");
    if (!Utils::loadStyles(m_ui->topbarWidget, AppConstants::Ui::TOPBAR_UI))
        m_logger.debugLog("AssetPage: Failed to load style for topbar", "VIEW", "ERR");
    if (!Utils::loadStyles(m_ui->pageWidget, AppConstants::Ui::PAGES_WIDGET_UI))
        m_logger.debugLog("AssetPage: Failed to load style for pages widget", "VIEW", "ERR");
    
    setupConnections();
    loadTotalInvests();

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("AssetPage: UI setup completed", "VIEW", "INFO");
}

AssetPage::~AssetPage() {
    m_asset_cont->disableLiveUpdates();
}

void AssetPage::setupConnections() {
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
        emit switchPage(AppConstants::Pages::MAIN_PAGE);
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
        dialog.exec();
    });

    connect(m_asset_cont, &AssetsController::updatedAsset, this, &AssetPage::onAssetUpdate);
    connect(m_asset_cont, &AssetsController::updatedStats, this, &AssetPage::onUpdateStats);
    connect(m_invest_cont, &InvestsController::investCreated, this, &AssetPage::onInvestCreate);
}

void AssetPage::onAssetUpdate() {
    // TODO: Add animation
}

void AssetPage::onUpdateStats(double pvalue, double dchange, double invests) {
    m_ui->valueNum->setText("$" + Utils::formatNumberWithCommas(pvalue, 2));
    m_ui->balanceNum->setText("$" + Utils::formatNumberWithCommas(pvalue - invests, 2));
    m_ui->changeNum->setText("$" + Utils::formatNumberWithCommas(dchange, 2));

    double balance = pvalue - invests;
    m_ui->valueNum->setStyleSheet("color: " + ((pvalue > 0) ? AppConstants::Colors::POSITIVE_COLOR : AppConstants::Colors::NEGATIVE_COLOR));
    m_ui->balanceNum->setStyleSheet("color: " + ((balance > 0) ? AppConstants::Colors::POSITIVE_COLOR : AppConstants::Colors::NEGATIVE_COLOR));
    m_ui->changeNum->setStyleSheet("color: " + ((dchange > 0) ? AppConstants::Colors::POSITIVE_COLOR : AppConstants::Colors::NEGATIVE_COLOR));
}

void AssetPage::onInvestCreate(double amount) {
    m_ui->investsNum->setText("$" + QString::number(m_ui->investsNum->text().remove('$').toDouble() + amount));
    m_logger.debugLog("AssetPage: Updated total sum of investments", "VIEW", "INFO");
}

void AssetPage::loadTotalInvests() {
    m_ui->investsNum->setText("$" + QString::number(m_invest_cont->getTotal()));
}