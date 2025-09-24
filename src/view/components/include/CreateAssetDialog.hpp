#pragma once

#include <QDialog>
#include "AppConstants.hpp"
#include "Logger.hpp"
#include "WindowDragFilter.hpp"
#include "AssetsController.hpp"
#include "Utils.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateAssetDialog; }
QT_END_NAMESPACE

/**
 * @class CreateAssetDialog
 * @brief Modal dialog for creating new assets within the application.
 * 
 * CreateAssetDialog provides a user interface for creating different types of assets
 * based on the specified asset type. The dialog includes validation, error handling,
 * and integrates with the application's asset management system. It features custom
 * styling through QSS and supports window dragging functionality.
 */
class CreateAssetDialog : public QDialog {
    Q_OBJECT
    
private:
    Ui::CreateAssetDialog *m_ui;
    Logger& m_logger;
    int m_type;

public:
    /**
     * @brief Constructs a new asset creation dialog.
     * 
     * Initializes the dialog for creating assets of the specified type.
     * Sets up the user interface, applies custom styling, configures
     * window properties, and establishes necessary connections.
     * 
     * @param type Integer specifying the asset type to create. Different
     *             values determine dialog behavior and available options.
     * @param parent Optional parent widget for proper dialog positioning
     *               and memory management. Defaults to nullptr for
     *               application-level modal behavior.
     */
    CreateAssetDialog(int type, QWidget *parent = nullptr);
    
    /**
     * @brief Handles dialog acceptance and initiates asset creation.
     * 
     * Overrides QDialog::accept() to perform custom validation and asset
     * creation logic before closing the dialog. Validates user input,
     * creates the asset through AssetsController, handles errors, and
     * provides appropriate user feedback.
     */
    void accept() override;
};