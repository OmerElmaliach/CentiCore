#include "CreateExpenseDialog.hpp"
#include "../ui/ui_create_expense.h"

CreateExpenseDialog::CreateExpenseDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::CreateExpenseDialog),
        m_logger(DebugUtils::getInstance()) {
    m_logger.debugLog("Creating QDialog Expense...", "VIEW", "INFO");
    m_ui->setupUi(this);
    loadStyles(DIALOG_UI);
}

CreateExpenseDialog::~CreateExpenseDialog() {
    delete m_ui;
}

void CreateExpenseDialog::loadStyles(const char* stylePath) {
    QFile styleFile(stylePath);  
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
    } else {
        m_logger.debugLog("Failed to load style file for Expense Dialog", "VIEW", "ERROR");
    }
}