#include "StockInterface.hpp"
#include "../ui/ui_stocks.h"

StockInterface::StockInterface(QWidget *parent) :
        QMainWindow(parent),
        m_ui(new Ui::StockInterface),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Performing StockInterface UI setup", "VIEW", "INFO");
    m_ui->setupUi(this);

    // Load functions and styles
    loadBtns();
    loadStyles(INTERFACE_UI);

    // Load events
    WindowDragFilter* dragFilter = new WindowDragFilter(parent, this);
    m_ui->topbarWidget->installEventFilter(dragFilter);
    m_ui->topbarDisplay->installEventFilter(dragFilter);
    m_logger.debugLog("StockInterface UI setup completed", "VIEW", "INFO");
}

StockInterface::~StockInterface() {
    delete m_ui;
}

void StockInterface::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file stocks.ui", "VIEW", "ERROR");
    }
}

void StockInterface::loadBtns() {
    // Exit window button.
    connect(m_ui->exit_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Exit pressed, program shutdown...", "VIEW", "INFO");
        exit(0);
    });

    // Minimize window button.
    connect(m_ui->minimize_btn, &QPushButton::clicked, this, [this] {
        m_logger.debugLog("Minimizing window", "VIEW", "INFO");
        setWindowState(Qt::WindowMinimized);
    });
}

void StockInterface::onAssetCreate(const QString sign, QString amount, QString type) {
    // TODO: IMPLEMENT
}

void StockInterface::loadAssets() {
    // TODO: IMPLEMENT
}