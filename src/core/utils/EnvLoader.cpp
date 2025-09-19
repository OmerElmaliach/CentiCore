#include "EnvLoader.hpp"

namespace EnvLoader {
    QString getValue(const QString& key) {
        QFile file(AppConstants::Config::ENV_FILE_PATH);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            Logger::getInstance().debugLog("EnvLoader: Cannot open .env file: " + AppConstants::Config::ENV_FILE_PATH.toStdString(), "UTILS", "WARN");
            return "";
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty() || line.startsWith('#'))
                continue;

            int equalPos = line.indexOf('=');
            if (equalPos > 0) {
                QString env_key = line.left(equalPos).trimmed();
                QString env_value = line.mid(equalPos + 1).trimmed();
                
                if (env_value.startsWith('"') && env_value.endsWith('"'))
                    env_value = env_value.mid(1, env_value.length() - 2);
                
                if (env_key == key)
                    return env_value;
            }
        }

        Logger::getInstance().debugLog("EnvLoader: Unable to find given key in .env file: " + key.toStdString(), "UTILS", "WARN");
        return "";
    }
}