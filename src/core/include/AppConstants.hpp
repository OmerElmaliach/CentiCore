#pragma once

#include <QString>
#include <QStringList>

namespace AppConstants {
    namespace Colors {
        extern const QString POSITIVE_COLOR;
        extern const QString NEGATIVE_COLOR;
    }

    namespace Ui {
        extern const QString MAIN_PAGE_UI;
        extern const QString ASSET_PAGE_UI;
        extern const QString TOPBAR_UI;
        extern const QString PAGES_WIDGET_UI;
        extern const QString LEAD_STOCKS_UI;
        extern const QString DIALOG_UI;
        enum ASSET_COLUMNS {
            SYMBOL = 0,
            QUANTITY = 1,
            PRICE = 2,
            DAILY_CHANGE_PERCENT = 3,
            DAILY_CHANGE_DOLLAR = 4,
            TOTAL_VALUE = 5,
            COLUMN_COUNT = 6
        };
    }

    namespace Pages {
        extern const int MAIN_PAGE;
        extern const int STOCKS_PAGE;
        extern const int LIVE_UPDATE_INTERVAL;
        extern const QStringList ASSET_HEADERS;
        extern const QStringList EXPENSE_CATEGORIES;
    }

    namespace Utils {
        extern const QString LOG_PATH;
    }

    namespace Config {
        extern const QString ENV_FILE_PATH;
        extern const QString GITHUB_URL;
    }
}