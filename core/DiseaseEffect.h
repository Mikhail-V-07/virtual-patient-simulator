//Toxir or Misha
#pragma once

#include <string>
#include <vector>

struct DiseaseEffect {
	std::string paramId;
	float delta;
};

struct DiseaseStage {
	float threshold;
	std::string complaint;
	std::string description;
	std::vector<DiseaseEffect> effects;
	bool triggered = false;
};
