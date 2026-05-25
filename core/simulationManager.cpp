#include "simulationManager.h"


SimulationManager::SimulationManager(const string& patientName) : patient(patientName), activeDisease(nullptr), step(0), simulationOver(false), diagnosisCorrect(false) {
	logger << ("Simulation started for patient: " + patientName);
};


void SimulationManager::nextStep() {

	if (!activeDisease || simulationOver) {
		logger << Important(
			"No active disease."
		);
		return;
	}


	step++;

	activeDisease->grow();

	activeDisease->applyEffects(patient);

	logger << ("[STEP " + to_string(step) + "] Disease progression.");

	if (activeDisease->getSeverity() > 0.7f) {

		logger << Important(
			"Patient condition worsening."
		);
	}

	if (activeDisease->getSeverity() >= 1.0f) {

		simulationOver = true;

		logger << Important(
			"Patient died."
		);
	}
}

bool SimulationManager::isSimulationOver() const {
	return simulationOver;
}

int SimulationManager::getStep() const {
	return step;
}


void SimulationManager::setDisease(Disease* disease) {

	if (activeDisease) {
		delete activeDisease;
	}

	activeDisease = disease;

	if (activeDisease) {

		logger << (
			"Hidden disease selected."
		);
	}
}

string SimulationManager::getVisibleSymptoms() const {

	if (!activeDisease)
		return "No symptoms.";

	vector<string> symptoms =
		activeDisease->getSymptoms();

	if (symptoms.empty())
		return "No visible symptoms.";

	string result;

	for (const auto& s : symptoms) {

		result += "- ";
		result += s;
		result += "\n";
	}

	return result;
}

Parameter SimulationManager::requestAnalysis(ParameterID id) {


	Parameter* param =
		patient.getParamByID(id);

	if (!param) {

		logger << Important(
			"Invalid analysis requested."
		);

		throw runtime_error(
			"Parameter not found."
		);
	}

	logger << string("Analysis requested: ") +param->getName();

	return *param;

}


bool SimulationManager::submitDiagnosis(
	const string& diagnosisName
) {

	if (!activeDisease)
		return false;

	logger << (
		"Diagnosis submitted: " +
		diagnosisName
	);

	// правильный диагноз
	if (diagnosisName == activeDisease->getName()) {

		diagnosisCorrect = true;

		simulationOver = true;

		logger << Important(
			"Correct diagnosis."
		);

		logger << (
			"Simulation completed successfully."
		);

		return true;
	}

	//неправильный диагноз
	diagnosisCorrect = false;

	logger << Important("Wrong diagnosis.");

	logger << ("Incorrect diagnosis submitted.");

	//ухудшение состояния

	nextStep();

	//пациент может умереть
	if (activeDisease->getSeverity() >= 1.0f) {

		simulationOver = true;

		logger << Important(
			"Patient died after misdiagnosis."
		);
	}

	return false;
}

vector<string> SimulationManager::getImportantEvents() const {
	return logger.getImportantEvents();
}

SimulationManager::~SimulationManager() {
	logger << ("Simulation ended.");
	if (activeDisease) {
		delete activeDisease;
		activeDisease = nullptr;
	}
};