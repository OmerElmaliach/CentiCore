#include "include/debug_utils.h"

DebugUtils::DebugUtils() : DebugUtils("logs/") {}

DebugUtils::DebugUtils(QString filepath) {
    // Creates directory if doesnt exist.
    QDir dir(filepath);
    if (!dir.exists())
        dir.mkpath(".");

    m_logfile.setFileName(filepath + QDateTime::currentDateTime().toString("hh-mm-ss") + ".txt");
    if (!m_logfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Failed to open log file.");
    }

    // Log starting message
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "=            Version %s | Build %s              =", CENTICORE_VERSION,
         QDateTime::currentDateTime().toString("yyyy-MM-d").toLocal8Bit().constData());

    qDebug("============================================================");
    qDebug("=           CentiCore Personal Finance Tracker             =");
    qDebug("=               Initialization Started...                  =");
    qDebug("%s", buff);
    qDebug("============================================================");

    m_logfile.write("============================================================\n");
    m_logfile.write("=           CentiCore Personal Finance Tracker             =\n");
    m_logfile.write("=               Initialization Started...                  =\n");
    m_logfile.write(buff);
    m_logfile.write("\n");
    m_logfile.write("============================================================\n");
    m_logfile.flush();
}

DebugUtils::~DebugUtils() {
    m_logfile.close();
}

void DebugUtils::debugLog(string info, string type) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "[%s][CENTICORE-UI][%s] %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(), type.c_str(), info.c_str());

    // Write to CLI
    qDebug("%s", buff);

    // Write to log
    m_logfile.write(buff);
    m_logfile.write("\n");
    m_logfile.flush();
}