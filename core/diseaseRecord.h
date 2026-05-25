#pragma once
#include "parameter.h"

const int NAME_LIMIT = 64;
const int MAX_EFFECTS = 16;
const int MAX_SYMPTOMS = 8;
const int MAX_STAGES = 4;
const int SYMPTOM_TEXT = 64;



enum DiseaseType {
    ACUTE,
    CHRONIC,
    EPISODIC
};

struct DiseaseRecord {
    int diseaseID;
    DiseaseType type;

    char name[NAME_LIMIT];

    float strength;

    // уникальные поля
    float special;

    // симптомы
    char symptoms[MAX_STAGES][MAX_SYMPTOMS][SYMPTOM_TEXT];

    // эффекты
    EffectRecord effects[MAX_EFFECTS];
    int effectCount;
};