#include "AppContainer.hpp"

AppContainer::AppContainer(QWidget *parent) : QMainWindow(parent), m_logger(DebugUtils::getInstance()) {
    setWindowFlags(Qt::FramelessWindowHint);

    MainPage* mainPage = new MainPage(this);
    AssetPage* stocksPage = new AssetPage(this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(mainPage);
    m_stack->addWidget(stocksPage);
    setCentralWidget(m_stack);

    // Setup signals
    connect(mainPage, &MainPage::switchPage, this, &AppContainer::switchPage);
    connect(stocksPage, &AssetPage::switchPage, this, &AppContainer::switchPage);
}

AppContainer::~AppContainer() { }

void AppContainer::switchPage(int index) {
    try {
        m_stack->setCurrentIndex(index);
    } catch(exception e) {
        m_logger.debugLog("AppContainer: Failed to switch page, index: " + index, "VIEW", "ERR");
    }
}