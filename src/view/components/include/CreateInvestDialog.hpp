#pragma once

#include <QDialog>
#include <QDate>
#include "DebugUtils.hpp"
#include "WindowDragFilter.hpp"
#include "InvestsController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateInvestDialog; }
QT_END_NAMESPACE

class CreateInvestDialog : public QDialog {
    Q_OBJECT

private:
    const char* DIALOG_UI = ":/styles/qss/dialog_box.qss";
    Ui::CreateInvestDialog *m_ui;
    DebugUtils& m_logger;

public:
    /**
     * @brief Constructor function for qdialog.
     */
    explicit CreateInvestDialog(QWidget *parent = nullptr);

    /**
     * @brief Deconstructor function for qdialog.
     */
    ~CreateInvestDialog();

    /**
     * @brief Loads the qss into the ui file.
     */
    void loadStyles(const char* stylePath);

    /**
     * @brief Handles expense creation upon accept.
     */
    void accept() override;

signals:
    void investCreated(double amount);
};
