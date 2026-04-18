#include "Disease.h"

using namespace std;

void Disease::growSeverity() {
	severity += growthRate;
	if (severity > 1.0) severity = 1.0; //добавить смерть пациента
}

void Disease::applyStages(std::vector<Parameter>& params) {
	for (DiseaseStage& stage : stages) {
		if (stage.triggered) continue;

		if (severity >= stage.threshold) {
			stage.triggered = true;

			for (DiseaseEffect& effect : stage.effects) {
				for (auto& param : params) {
					if (param.getId() == effect.paramId) {
						param.applyInstantChange(effect.instantDelta);
						param.addDrift(effect.rateDelta);
					}
				}
			}

			cout << stage.description << endl; //вывод симптома
			cout << stage.complaint << endl;
		}
	}
}

void Disease::step(std::vector<Parameter>& params) {
	growSeverity();
	applyStages(params);
	for (auto& p : params) {
		p.step();
	}
}

void Disease::showSymptoms() {
	cout << "\n[Симптомы]\n";
	for (auto s : symptoms) {
		cout << "- " << symptomToString(s) << endl;
	}
}