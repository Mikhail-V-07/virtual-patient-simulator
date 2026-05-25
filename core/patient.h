#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "parameter.h"


using namespace std;


class Disease;

class Patient {
private:
    string name;
    vector <Parameter> params;

public:
    Patient(string n) : name(n) {}

    void loadParameters(const string& filename) {
        ifstream binFile(filename, ios::binary);

        if (!binFile) {
            cout << "Error opening binary file: " << filename << endl;
            return;
        }

        params.clear();

        int id, len, len2, len3;
        float cur, mn, mx;

        while (true) {
            if (!binFile.read((char*)&id, sizeof(id))) break;

            // Name
            binFile.read((char*)&len, sizeof(len));
            string pName;
            pName.resize(len);
            binFile.read(&pName[0], len);

            // normalRange
            binFile.read((char*)&len2, sizeof(len2));
            string pRange;
            pRange.resize(len2);
            binFile.read(&pRange[0], len2);

            binFile.read((char*)&len3, sizeof(len3));
            string pUnit;
            pUnit.resize(len3);
            binFile.read(&pUnit[0], len3);

            binFile.read((char*)&cur, sizeof(cur));
            binFile.read((char*)&mn, sizeof(mn));
            binFile.read((char*)&mx, sizeof(mx));

            Parameter p(id, pName, pRange, pUnit, mn, cur, mx);
            params.push_back(p);
        }

        cout << "Data loaded into Patient '" << name << "' successfully.\n";
    }

    Parameter* getParamByID(int id) {
        for (auto& p : params) {
            if (p.getId() == id) return &p;
        }
        return nullptr;
    }

    //для отладки
    void displayAll() {
        cout << "\n=== Состояние пациента: " << name << " ===\n";
        for (auto& p : params) {
            cout << p.getName() << " [" << p.getNormalRange() << "]: "
                << fixed << setprecision(1) << p.getCurrent() << endl;
        }
    }

};