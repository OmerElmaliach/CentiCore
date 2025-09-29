#include "AppConstants.hpp"

namespace AppConstants {
    namespace Colors {
        const QString POSITIVE_COLOR = "#28a745";
        const QString NEGATIVE_COLOR = "#dc3545";
    }

    namespace Ui {
        const QString MAIN_PAGE_UI = ":/styles/qss/main_page.qss";
        const QString ASSET_PAGE_UI = ":/styles/qss/asset_page.qss";
        const QString STATS_PAGE_UI = ":/styles/qss/stats_page.qss";
        const QString TOPBAR_UI = ":/styles/qss/topbar.qss";
        const QString PAGES_WIDGET_UI = ":/styles/qss/page_widget.qss";
        const QString LEAD_STOCKS_UI = ":/styles/qss/leading_stocks.qss";
        const QString DIALOG_UI = ":/styles/qss/dialog_box.qss";
    }

    namespace Pages {
        const int LIVE_UPDATE_INTERVAL = 10000;
        const QStringList ASSET_HEADERS = {"Symbol", "Quantity", "Price per Unit", "Daily change (%)", "Daily change ($)", "Total Value"};
        const QStringList EXPENSE_CATEGORIES = {"Personal Care", "Transportation", "Food", "Utilities", "Entertainment", "Miscellaneous"};
    }

    namespace Utils {
        const QString LOG_PATH = "logs/";
    }

    namespace Config {
        const QString ENV_FILE_PATH = ":/config/config/app.env";
        const QString GITHUB_URL = "https://github.com/OmerElmaliach/CentiCore";
    }
}
