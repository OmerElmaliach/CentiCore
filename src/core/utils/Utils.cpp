#include "Utils.hpp"

namespace Utils {
    QString formatNumberWithCommas(double num, int afterDot) {
        QLocale locale(QLocale::English, QLocale::UnitedStates);
        return locale.toString(num, 'f', afterDot);
    }

    bool loadStyles(QWidget* widget, const QString stylePath) {
        QFile styleFile(stylePath);
        if (!styleFile.open(QFile::ReadOnly))
            return false;

        widget->setStyleSheet(QLatin1String(styleFile.readAll()));
        styleFile.close();
        return true;
    }
}