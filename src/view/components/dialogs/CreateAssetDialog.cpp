#include "CreateAssetDialog.hpp"
#include "../../ui/ui_create_asset.h"

CreateAssetDialog::CreateAssetDialog(int type, QWidget *parent) :
        m_type(type),
        QDialog(parent),
        m_ui(new Ui::CreateAssetDialog),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Creating QDialog Asset...", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    loadStyles(DIALOG_UI);

    WindowDragFilter *dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarLabel->installEventFilter(dragFilter);
    connect(m_ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

CreateAssetDialog::~CreateAssetDialog() {
    delete m_ui;
}

void CreateAssetDialog::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);  
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file for Asset Dialog", "VIEW", "ERR");
    }
}

void CreateAssetDialog::accept() {
    // Send a request to add an asset
    bool isNumber;
    QString symbol = m_ui->symbolInput->text(), quant = m_ui->quantInput->text();
    quant.toDouble(&isNumber);

    // Check if fields are invalid
    if (symbol.isEmpty() || !isNumber) {
        m_logger.debugLog("Fields do not meet the requirements", "VIEW", "WARN");
        QDialog::accept();
        return;
    }

    bool wasAdded = AssetsController::getInstance().add(symbol, quant.toDouble(), 0, m_type);

    if (wasAdded) {
        emit assetCreated(symbol, quant, m_type); 
    }

    QDialog::accept();
}