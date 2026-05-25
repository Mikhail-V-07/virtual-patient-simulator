#pragma once
#include "disease.h"


class ChronicDisease : public Disease {
private:
    float organDamageRate; // slow permanent damage rate

public:
    ChronicDisease(const char* n = "", float str = 1.0f) : Disease(n, str), organDamageRate(0.1f) {}

    void grow() override {
        // slow stable progression
        severity += (strength * 0.01f) + (organDamageRate * 0.005f);
        if (severity > 1.0f) severity = 1.0f;
    }

    // returns disease type
    DiseaseType getType() const override {
        return CHRONIC;
    }


    void loadFromRecord(const DiseaseRecord& record) override {

        // load common disease data
        Disease::loadFromRecord(record);

        // load unique chronic field
        organDamageRate = record.special;
    }
};