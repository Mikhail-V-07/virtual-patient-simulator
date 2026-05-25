#pragma once
#include "disease.h"

class EpisodicDisease : public Disease {
private:
    float attackChance; // probability of attack each step

public:
    EpisodicDisease(const char* n = "", float str = 1.0f) : Disease(n, str), attackChance(0.2f) {}

    void grow() override {
        // random attack check
        if ((rand() % 100) < (attackChance * 100)) {

            severity += 0.25f * strength; /// sudden worsening
        }
        else {

            severity -= 0.05f; // slight recovery between attacks
        }

        // keep severity in valid range
        if (severity < 0.05f) severity = 0.05f;
        if (severity > 1.0f) severity = 1.0f;
    }

    // returns disease type
    DiseaseType getType() const override {
        return EPISODIC;
    }

    void loadFromRecord(const DiseaseRecord& record) override {

        // load common disease data
        Disease::loadFromRecord(record);

        // load unique episodic field
        attackChance = record.special;
    }
};