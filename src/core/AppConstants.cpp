#include "AppConstants.hpp"

namespace AppConstants {
    namespace Colors {
        const QString POSITIVE_COLOR = "#28a745";
        const QString NEGATIVE_COLOR = "#dc3545";
    }

    namespace Ui {
        const QString MAIN_PAGE_UI = ":/styles/qss/main_page.qss";
        const QString ASSET_PAGE_UI = ":/styles/qss/asset_page.qss";
        const QString TOPBAR_UI = ":/styles/qss/topbar.qss";
        const QString PAGES_WIDGET_UI = ":/styles/qss/page_widget.qss";
        const QString LEAD_STOCKS_UI = ":/styles/qss/leading_stocks.qss";
        const QString DIALOG_UI = ":/styles/qss/dialog_box.qss";
    }

    namespace Pages {
        const int MAIN_PAGE = 0;
        const int STOCKS_PAGE = 1;
        const int LIVE_UPDATE_INTERVAL = 10000;
        const QStringList ASSET_HEADERS = {"Symbol", "Quantity", "Price per Unit", "Daily change (%)", "Daily change ($)", "Total Value"};
    }

    namespace Utils {
        const QString LOG_PATH = "logs/";
    }

    namespace Config {
        const QString ENV_FILE_PATH = ":/config/config/app.env";
    }
}
