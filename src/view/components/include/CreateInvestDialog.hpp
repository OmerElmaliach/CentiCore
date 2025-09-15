#pragma once

#include <QDialog>
#include <QDate>
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "InvestsController.hpp"
#include "GeneralUtils.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateInvestDialog; }
QT_END_NAMESPACE

/**
 * @class CreateInvestDialog
 * @brief Modal dialog for creating new investment records within the application.
 * 
 * CreateInvestDialog provides a user interface for recording and creating new
 * investment entries. The dialog includes date handling, investment amount
 * error handling, and integrates with the application's investment management system.
 */
class CreateInvestDialog : public QDialog {
    Q_OBJECT
    
private:
    const char* DIALOG_UI = ":/styles/qss/dialog_box.qss";
    Ui::CreateInvestDialog *m_ui;
    DebugUtils& m_logger;

public:
    /**
     * @brief Constructs a new investment creation dialog.
     * 
     * Initializes the dialog for creating new investment records. Sets up the
     * user interface with current date defaults, applies custom styling,
     * configures window properties, and establishes necessary connections.
     * The dialog is prepared with appropriate input fields for investment data
     * entry including amount, investment type, portfolio allocation, and date
     * information.
     * 
     * @param parent Optional parent widget for proper dialog positioning
     *               and memory management. Defaults to nullptr for
     *               application-level modal behavior.
     */
    CreateInvestDialog(QWidget *parent = nullptr);
    
    /**
     * @brief Handles dialog acceptance and initiates investment creation.
     * 
     * Overrides QDialog::accept() to perform custom validation and investment
     * creation logic before closing the dialog. Validates user input including
     * investment amounts, dates, investment types, and required fields, then
     * creates the investment record through InvestsController.
     */
    void accept() override;
};