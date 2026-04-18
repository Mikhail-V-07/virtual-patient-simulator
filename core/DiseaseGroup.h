//Toxir
#pragma once
#include "disease.h"

class AllergyGroup : public Disease {
private:
	float reactionIntensity;
public:
	AllergyGroup(float reactionIntensity, std::string id, std::string name, float severity, float growthRate, std::vector <DiseaseStage> stages) 
		: reactionIntensity(reactionIntensity), Disease(id, name, severity, growthRate, stages) {};

	void applyStages(std::vector<Parameter>& params) override;
};

class RespiratoryGroup : public Disease {
public:
	RespiratoryGroup(std::string id, std::string name, float severity, float growthRate, std::vector <DiseaseStage> stages)
		: Disease(id, name, severity, growthRate, stages) {
	};

	void step(std::vector<Parameter>& params) override;
};

class CardiacGroup : public Disease {
public:
	CardiacGroup(std::string id, std::string name, float severity, float growthRate, std::vector <DiseaseStage> stages)
		: Disease(id, name, severity, growthRate, stages) {
	};

	void step(std::vector<Parameter>& params) override;
};