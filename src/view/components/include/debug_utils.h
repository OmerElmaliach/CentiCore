#ifndef DEBUG_UTILS
#define DEBUG_UTILS
#include <iostream>
#include <string>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include "version.h"
#define LOG_MSG_LENGTH 256
using namespace std;

class DebugUtils {
private:
    QFile m_logfile;
    
public:
    /**
     * Default constructor for DebugUtils
     */
    DebugUtils();

    /**
     * Constructor for DebugUtils
     */
    DebugUtils(QString filepath);

    /**
     * @brief Deconstructor function for DebugUtils.
     */
    ~DebugUtils();

    /**
     * @brief Logs activity to the CLI and log file.
     */
    void debugLog(string info, string type);
};

#endif