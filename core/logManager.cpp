#include "logManager.h"

LogManager::LogManager() {

    logFile.open("simulation_log.txt",ios::app);
}

LogManager::~LogManager() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void LogManager::addImportant(const string& message) {

    importantEvents.push_back(message);

    *this << ("[IMPORTANT] " + message);
}

vector<string> LogManager::getImportantEvents() const {

    return importantEvents;
}

void LogManager::clearImportantEvents() {

    importantEvents.clear();
}


LogManager& LogManager::operator<<(const Important& imp) {
    importantEvents.push_back(imp.message);

    if (logFile.is_open()) {
        logFile << "[IMPORTANT] " << imp.message << endl;
    }
    return *this;
}

LogManager& LogManager::operator<<(ostream& (*manip)(ostream&)) {
    if (logFile.is_open()) {
        manip(logFile);
    }
    return *this;
}