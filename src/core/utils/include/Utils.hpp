#include <QObject>
#include <QWidget>
#include <QFile>
#include <QLocale>

namespace Utils {
    /**
     * @brief Formats a given number with comma separators
     */
    QString formatNumberWithCommas(const double num, int afterDot);

    /**
     * @brief Loads the qss into the ui file
     */
    bool loadStyles(QWidget* widget, const QString stylePath);
}