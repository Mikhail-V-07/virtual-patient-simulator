#pragma once


#include <fstream>
#include <cstdlib>  // rand() for random index selection
#include "diseaseRecord.h"
#include "acuteDisease.h"
#include "chronicDisease.h"
#include "episodicDisease.h"


class DiseaseLoader {

private:

    // counts how many records are stored in file
    int getRecordCount() const {
        ifstream file("diseases.dat", ios::binary | ios::ate);  // open file and move cursor to file end

        if (!file) {
            cout << "Error opening binary file: " << endl;
            return 0;
        }

        streamsize size = file.tellg();  // get file size in bytes

        return static_cast<int>(size / sizeof(DiseaseRecord)); // calculate number of records in file
    }

    // loads one disease object by its position in file
    Disease* loadDiseaseByIndex(int index) const {
        int count = getRecordCount();

        // check if index is valid for additional safety
        if (index < 0 || index >= count) {
            return 0;
        }

        ifstream file("diseases.dat", ios::binary);

        if (!file) {
            cout << "Error opening binary file: " << endl;
            return 0;
        }


        DiseaseRecord record{};  // object that will temporarily store binary data from file

        file.seekg(static_cast<streamoff>(index) * sizeof(DiseaseRecord), ios::beg);  // move cursor to needed record position

        file.read(reinterpret_cast<char*>(&record), sizeof(DiseaseRecord));  // read one record from file into structure

        if (!file) {
            cout << "Error opening binary file: " << endl;
            return 0;
        }

        Disease* disease = 0;

        // create correct derived object depending on disease type
        switch (record.type) {

        case ACUTE:
            disease = new AcuteDisease();
            break;

        case CHRONIC:
            disease = new ChronicDisease();
            break;

        case EPISODIC:
            disease = new EpisodicDisease();
            break;

        default:
            return 0;
        }

        disease->loadFromRecord(record);  //  copy data from record into created object

        return disease;
    }

public:

    // loads random disease from file
    Disease* loadRandomDisease() const {
        int count = getRecordCount();

        if (count <= 0) {
            return 0;
        }

        int index = rand() % count;  // generate random record index

        return loadDiseaseByIndex(index);  // load disease from random position
    }
};



//Minimal correct main.cpp
//#include <cstdlib>
//#include <ctime>
//
//#include "DiseaseLoader.h"
//
//int main() {
//
//    srand(static_cast<unsigned>(time(0)));
//
//    DiseaseLoader loader;
//
//    Disease* d = loader.loadRandomDisease();
//
//    if (d) {
//        d->print();   // or whatever you implemented
//
//        delete d;
//    }
//
//    return 0;
//}