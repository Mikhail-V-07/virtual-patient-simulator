//Toxir
#pragma once

#include <vector>
#include "Parameter.h"
#include "DiseaseEffect.h"

class Disease {
protected:
	std::string id;
	std::string name;
	float severity;
	float growthRate;
	std::vector <DiseaseStage> stages;

public:
	Disease(std::string id, std::string name, float severity, float growthRate, std::vector <DiseaseStage> stages)
		:id(id), name(name), severity(severity), growthRate(growthRate), stages(stages) {};

	virtual ~Disease() = default;

	void growSeverity();

	virtual void applyStages(std::vector<Parameter>& params);

	virtual void step(std::vector<Parameter>& params);

	void showSymptoms();

	float getSev() { return severity; }
	std::string getName() { return name; }
};