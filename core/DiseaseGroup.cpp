#include "DiseaseGroup.h"

using namespace std;

void AllergyGroup::applyStages(std::vector<Parameter>& params) {
	for (DiseaseStage& stage : stages) {
		if (stage.triggered) continue;
		if (severity >= stage.threshold) {
			stage.triggered = true;

			for (DiseaseEffect& effect : stage.effects) {
				for (auto& param : params) {
					if (param.getId() == effect.paramId) {
						param.update(effect.delta * reactionIntensity);//чем выше тяжесть, тем более непредсказуемо скачут параметры
					}
				}
			}

			cout << stage.description << endl; //вывод симптома
			cout << stage.complaint << endl;
		}
	}
}

void RespiratoryGroup::step(std::vector<Parameter>& params) {
	growSeverity();
	for (auto& p : params) {
		if (p.getId() == "oxygen" && p.getValue() < 80.0) {
			severity += 0.05; //пока условно
		}
	}
	applyStages(params);
}



void CardiacGroup::step(std::vector<Parameter>& params) {
	growSeverity();
	for (auto& p : params) {
		if (p.getId() == "pulse") {
			if (p.getValue() > 100.0) {
				severity += 0.01; // дополнительный рост тяжести из-за нагрузки на сердце
			}
		}
	}
	applyStages(params);
}