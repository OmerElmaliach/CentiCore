#include "AppContainer.hpp"

AppContainer::AppContainer(QWidget *parent) : QMainWindow(parent), m_logger(DebugUtils::getInstance()) {
    setWindowFlags(Qt::FramelessWindowHint);

    MainInterface* mainPage = new MainInterface(this);
    StockInterface* stocksPage = new StockInterface(this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(mainPage);
    m_stack->addWidget(stocksPage);
    setCentralWidget(m_stack);

    // Setup signals
    connect(mainPage, &MainInterface::switchPage, this, &AppContainer::switchPage);
    connect(stocksPage, &StockInterface::switchPage, this, &AppContainer::switchPage);
}

AppContainer::~AppContainer() { }

void AppContainer::switchPage(int index) {
    try {
        m_stack->setCurrentIndex(index);
    } catch(exception e) {
        m_logger.debugLog("Failed to switch page, index: " + index, "VIEW", "ERR");
    }
}