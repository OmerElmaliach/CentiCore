#include "StatsPage.hpp"
#include "../../ui/ui_statistics_page.h"

StatsPage::StatsPage(QWidget* parent) :
    m_ui(new Ui::StatsPage),
    m_logger(Logger::getInstance()) {
        m_ui->setupUi(this);

        // Load connections and styles
        if (!Utils::loadStyles(this, AppConstants::Ui::STATS_PAGE_UI))
            m_logger.debugLog("StatsPage: Failed to load style file statistic_page", "VIEW", "ERR");
        if (!Utils::loadStyles(m_ui->topbarWidget, AppConstants::Ui::TOPBAR_UI))
            m_logger.debugLog("StatsPage: Failed to load style for topbar", "VIEW", "ERR");
        if (!Utils::loadStyles(m_ui->pageWidget, AppConstants::Ui::PAGES_WIDGET_UI))
            m_logger.debugLog("StatsPage: Failed to load style for pages widget", "VIEW", "ERR");

        setupConnections();

        // Load events
        WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
        m_ui->topbarWidget->installEventFilter(dragFilter);
        m_ui->topbarDisplay->installEventFilter(dragFilter);
        m_logger.debugLog("StatsPage: UI setup completed", "VIEW", "INFO");
}

void StatsPage::setupConnections() {
    // Exit window button
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("StatsPage: Exit pressed, program shutdown...", "VIEW", "INFO");
        this->window()->close();
    });

    // Minimize window button
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("StatsPage: Minimizing window", "VIEW", "INFO");
        this->window()->setWindowState(Qt::WindowMinimized);
    });

    // Move to dashboard
    connect(m_ui->dashBoard_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("StatsPage: Switching to dashboard page", "VIEW", "INFO");
        emit switchPage(AppConstants::Pages::MAIN_PAGE);
    });

    // Stocks page button
    connect(m_ui->stocks_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("StatsPage: Switching to stocks page", "VIEW", "INFO");
        emit switchPage(AppConstants::Pages::STOCKS_PAGE);
    });

    // Get help button
    connect(m_ui->getHelp_btn, &QPushButton::clicked, this, [this] {
        QDesktopServices::openUrl(QUrl(AppConstants::Config::GITHUB_URL));
    });
}