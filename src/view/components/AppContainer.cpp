#include "AppContainer.hpp"

AppContainer::AppContainer(QWidget *parent) : QMainWindow(parent) {
    setWindowFlags(Qt::FramelessWindowHint);

    MainInterface* mainPage = new MainInterface(this);
    StockInterface* stocksPage = new StockInterface(this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(mainPage);
    m_stack->addWidget(stocksPage);
    // TODO: Add other pages
    setCentralWidget(m_stack);

    // Setup signals
    connect(mainPage, &MainInterface::switchPage, this, &AppContainer::switchPage);
}

AppContainer::~AppContainer() { }

void AppContainer::switchPage(int index) {
    m_stack->setCurrentIndex(index);
}