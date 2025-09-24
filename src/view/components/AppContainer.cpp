#include "AppContainer.hpp"

AppContainer::AppContainer(QWidget *parent) : QMainWindow(parent), m_logger(Logger::getInstance()) {
    setWindowFlags(Qt::FramelessWindowHint);
    setupConnections();
}

void AppContainer::setupConnections() {
    MainPage* mainPage = new MainPage(this);
    AssetPage* stocksPage = new AssetPage(this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(mainPage);
    m_stack->addWidget(stocksPage);
    setCentralWidget(m_stack);

    connect(mainPage, &MainPage::switchPage, this, &AppContainer::switchPage);
    connect(stocksPage, &AssetPage::switchPage, this, &AppContainer::switchPage);
}

void AppContainer::switchPage(int index) {
    try {
        if (index < 0 || index >= m_stack->count()) {
            m_logger.debugLog("AppContainer: Invalid page index: " + to_string(index), "VIEW", "ERR");
            return;
        }
        m_stack->setCurrentIndex(index);
    } catch(const std::exception& err) {
        m_logger.debugLog("AppContainer: Failed to switch page, index: " + to_string(index) + ", error: " + err.what(), "VIEW", "ERR");
    }
}