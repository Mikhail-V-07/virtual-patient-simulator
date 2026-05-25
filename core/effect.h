#pragma once
#include "parameter.h"

class Patient;

struct Effect {
	int parameterID;
	float coefficient;

    void apply(Patient& patient, float strength, float severity) {
        Parameter* param = patient.getParamByID(parameterID);

        if (!param) return;

        float factor = severity * severity;
        float delta = coefficient * strength * factor;

        param->applyDelta(delta);
    }
};

struct EffectRecord {
    int parameterID;
    float coefficient;
};