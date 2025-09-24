#include "CreateAssetDialog.hpp"
#include "../../ui/ui_create_asset.h"

CreateAssetDialog::CreateAssetDialog(int type, QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateAssetDialog),
        m_logger(Logger::getInstance()), 
        m_type(type) {
    m_logger.debugLog("CreateAssetDialog: Creating QDialog Asset...", "VIEW", "INFO");
    m_ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    Utils::loadStyles(this, AppConstants::Ui::DIALOG_UI);

    WindowDragFilter *dragFilter = new WindowDragFilter(this, this);
    m_ui->topbarLabel->installEventFilter(dragFilter);
    connect(m_ui->createBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

void CreateAssetDialog::accept() {
    // Send a request to add an asset
    bool isNumber;
    QString symbol = m_ui->symbolInput->text(), quant = m_ui->quantInput->text();
    quant.toDouble(&isNumber);

    // Check if fields are invalid
    if (symbol.isEmpty() || !isNumber) {
        m_logger.debugLog("CreateAssetDialog: Fields do not meet the requirements", "VIEW", "WARN");
        QDialog::accept();
        return;
    }

    bool wasAdded = AssetsController::getInstance()->add(symbol, quant.toDouble(), m_type);
    if (!wasAdded)
        m_logger.debugLog("CreateAssetDialog: Failed to create new asset: " + symbol.toStdString(), "VIEW", "WARN");

    QDialog::accept();
}