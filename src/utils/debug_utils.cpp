#include "debug_utils.hpp"

DebugUtils::DebugUtils() : DebugUtils("cc_" + QDateTime::currentDateTime().toString("dd-MM-yyyy") + ".log") {}

DebugUtils::DebugUtils(QString filepath) {
    // Creates directory if doesnt exist.
    QDir dir(logFolder);
    if (!dir.exists())
        dir.mkpath(".");

    m_logfile.setFileName(logFolder + filepath);
    bool pathExists = !m_logfile.exists();
    if (!m_logfile.open(QIODevice::WriteOnly | QIODevice::Text))
        qWarning("Failed to open log file.");

    if (pathExists)
        initMessage();
}

DebugUtils::~DebugUtils() {
    m_logfile.close();
}

void DebugUtils::debugLog(string info, string origin, string type) {
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "[%s][CENTICORE-%s][%s] %s", QDateTime().currentDateTime().toString("hh:mm:ss").toLocal8Bit().constData(), 
        origin.c_str(), type.c_str(), info.c_str());

    // Write to log
    m_logfile.write(buff);
    m_logfile.write("\n");
    m_logfile.flush();
}

void DebugUtils::initMessage() {
    // Log starting message
    char buff[LOG_MSG_LENGTH];
    sprintf(buff, "=            Version %s | Build %s              =", CENTICORE_VERSION,
         QDateTime::currentDateTime().toString("dd-MM-yyyy").toLocal8Bit().constData());

    m_logfile.write("============================================================\n");
    m_logfile.write("=           CentiCore Personal Finance Tracker             =\n");
    m_logfile.write("=               Initialization Started...                  =\n");
    m_logfile.write(buff);
    m_logfile.write("\n");
    m_logfile.write("============================================================\n");
    m_logfile.flush();
}