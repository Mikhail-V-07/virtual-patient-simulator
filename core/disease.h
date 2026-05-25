#pragma once
#include "parameter.h"
#include "effect.h"
#include "diseaseRecord.h"

class Patient;

class Disease {
protected:
    string name; // disease name
    float severity; // current progression (0.0 - 1.0)
    float strength; // progression speed multiplier


    // data loaded from file after object creation
    vector<vector<string>> symptomsByStage;  // symptoms grouped by stages
    vector<Effect> effects;  // disease effects

public:
    Disease(const char* n = "Unknown", float stren = 1.0f, vector<vector<string>> symptoms = {}) :
        name(n),
        severity(0.1f),  // disease starts at low severity
        strength(stren),
        symptomsByStage(symptoms) {
    }


    virtual ~Disease() = 0;

    virtual void grow() = 0; // pure virtual function, each disease type progresses differently

    virtual DiseaseType getType() const = 0;  // pure virtual function, returns exact disease type


    // applies all disease effects to patient
    void applyEffects(Patient& patient) {
        for (auto& e : effects) {
            e.apply(patient, strength, severity);
        }
    }

    // manually adds one effect by id
    void addEffect(ParameterID id, float coeff) {
        effects.push_back({ id, coeff });
    }

    // calculates current symptom stage from severity
    int getStage() const {
        if (symptomsByStage.empty()) return 0;

        int stage = static_cast<int>(severity * symptomsByStage.size());

        // prevents index overflow
        if (stage >= symptomsByStage.size())
            stage = symptomsByStage.size() - 1;

        return stage;
    }

    vector<string> getSymptoms() const {

        if (symptomsByStage.empty())
            return {};

        return symptomsByStage[getStage()];
    }

    // loads common disease data from binary record
    virtual void loadFromRecord(const DiseaseRecord& record) {
        name = record.name;
        strength = record.strength;

        // load symptoms
        symptomsByStage.clear();

        // go through all stages
        for (int stage = 0; stage < MAX_STAGES; stage++) {

            vector<string> stageSymptoms;

            // read symptoms for this stage
            for (int i = 0; i < MAX_SYMPTOMS; i++) {

                // skip empty entries
                if (strlen(record.symptoms[stage][i]) == 0)
                    continue;

                stageSymptoms.push_back(
                    record.symptoms[stage][i]
                );
            }

            symptomsByStage.push_back(stageSymptoms);
        }

        // load effects
        effects.clear();

        // protection from invalid file data
        for (int i = 0; i < record.effectCount && i < MAX_EFFECTS; i++) {
            effects.push_back({
                record.effects[i].parameterID,
                record.effects[i].coefficient
                });
        }
    }

    // prints symptoms for current stage
    void printSymptoms() {
        int stage = getStage();
        cout << "--- Current Symptoms ---\n";

        if (symptomsByStage.empty() || symptomsByStage[stage].empty()) {
            cout << "- No visible symptoms\n";
            return;
        }

        for (const auto& s : symptomsByStage[stage]) {
            cout << " * " << s << endl;
        }
    }

    float getStrength() const { return strength; }

    float getSeverity() const { return severity; }

    string getName() const { return name; }

    // keeps severity inside valid range
    void setSeverity(float sev) {

        severity = sev;

        if (severity < 0.0f)
            severity = 0.0f;

        if (severity > 1.0f)
            severity = 1.0f;
    }
};
Disease::~Disease() {}

