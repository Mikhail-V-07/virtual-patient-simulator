#pragma once
#include "parameter.h"

class FileManager {
public:
    void convertToBinary() {
        ifstream txtFile("parameter.txt");
        ofstream binFile("parameter.dat", ios::binary);

        if (!txtFile || !binFile) {
            cout << "File error!" << endl;
            return;
        }

        int id;
        string name, range, unit;
        float cur, mn, mx;

        while (true) {
            if (!(txtFile >> id)) break;
            txtFile.ignore();

            getline(txtFile, name);
            getline(txtFile, range);
            getline(txtFile, unit);

            if (!(txtFile >> cur)) break;
            if (!(txtFile >> mn)) break;
            if (!(txtFile >> mx)) break;
            txtFile.ignore();

            binFile.write((char*)&id, sizeof(id));

            int len = name.size();
            binFile.write((char*)&len, sizeof(len));
            binFile.write(name.c_str(), len);

            int len2 = range.size();
            binFile.write((char*)&len2, sizeof(len2));
            binFile.write(range.c_str(), len2);

            int len3 = unit.size();
            binFile.write((char*)&len3, sizeof(len3));
            binFile.write(unit.c_str(), len3);

            binFile.write((char*)&cur, sizeof(cur));
            binFile.write((char*)&mn, sizeof(mn));
            binFile.write((char*)&mx, sizeof(mx));
        }

        cout << "Converted to binary successfully.\n";
    }


    void putToArray(vector<Parameter>& parameters) {
        ifstream binFile("parameter.dat", ios::binary);

        if (!binFile) {
            cout << "Error opening binary file!" << endl;
            return;
        }

        parameters.clear();

        int id, len, len2, len3;
        float cur, mn, mx;

        while (true) {
            if (!binFile.read((char*)&id, sizeof(id))) break;

            binFile.read((char*)&len, sizeof(len));
            string name;
            name.resize(len);
            binFile.read(&name[0], len);

            binFile.read((char*)&len2, sizeof(len2));
            string range;
            range.resize(len2);
            binFile.read(&range[0], len2);

            binFile.read((char*)&len3, sizeof(len3));
            string unit;
            unit.resize(len3);
            binFile.read(&unit[0], len3);

            binFile.read((char*)&cur, sizeof(cur));
            binFile.read((char*)&mn, sizeof(mn));
            binFile.read((char*)&mx, sizeof(mx));

            Parameter p(id, name, range, unit, mn, cur, mx);
            parameters.push_back(p);
        }

        cout << "\nData loaded into vector successfully.\n";
    }
};