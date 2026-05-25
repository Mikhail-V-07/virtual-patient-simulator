#pragma once
#include <fstream>
#include <iostream>
#include <vector>



using namespace std;

struct Important {
    string message;
    Important(const string& msg) :message(msg) {}
};


class LogManager {
private:
    ofstream logFile;
    vector<string> importantEvents;

public:
    LogManager();

    ~LogManager();

    void addImportant(const string& message);

    vector<string> getImportantEvents() const;

    void clearImportantEvents();


    template<typename T>
    LogManager& operator<<(const T& value) {

        if (logFile.is_open()) {

            logFile << value << endl;
        }

        return *this;
    }

    LogManager& operator<<(ostream& (*manip)(ostream&));
    LogManager& operator<<(const Important& imp);
};
