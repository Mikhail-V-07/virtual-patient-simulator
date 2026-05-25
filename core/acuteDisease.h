#pragma once
#include "disease.h"

class AcuteDisease : public Disease {
private:
    float aggression; // progression acceleration multiplier

public:
    AcuteDisease(const char* n = "", float str = 1.0f) : Disease(n, str), aggression(1.2f) {}

    void grow() override {
        /// fast exponential progression
        severity += (strength * aggression) * (severity + 0.1f) * 0.1f;
        if (severity > 1.0f) severity = 1.0f;
    }

    // returns disease type
    DiseaseType getType() const override {
        return ACUTE;
    }

    void loadFromRecord(const DiseaseRecord& record) override {

        // load common disease data
        Disease::loadFromRecord(record);

        // load unique acute field
        aggression = record.special;
    }
};