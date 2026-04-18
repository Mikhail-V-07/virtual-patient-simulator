//Toxir or Misha
#pragma once

#include <string>
#include <vector>

struct DiseaseEffect {
	std::string paramId; //What specific symptom does this effect affect?
	float instantDelta; //How much this specific parameter will increase when the stage is launched. This is optional. You can simply pass the exact parameter value at launch, but this allows for a sharp increase.
	float rateDelta; //
};

struct DiseaseStage {
	float threshold; //When the stage is activated.
	std::string complaint; //What complaints does the patient have at this stage?
	std::string description; //Description of the stage. There may be some symptoms that the person doesn't complain about, but are simply visible through observation.
	std::vector<DiseaseEffect> effects; //What effects are active at this point?
	bool triggered = false; //Whether the stage has already been activated. If so, it can't be restarted.
};
