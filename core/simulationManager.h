#pragma once
#include <fstream>
#include "patient.h"
#include "disease.h"
#include "logManager.h"

using namespace std;

class SimulationManager {
private:

	Patient patient;
	
	Disease* activeDisease;
	
	int step;
	
	bool simulationOver;
	bool diagnosisSubmitted;
	bool diagnosisCorrect;

    vector<ParameterID> unlockedAnalyses;

	LogManager logger;

public:
    SimulationManager(const string& patientName);

    ~SimulationManager();

    void nextStep();

    bool isSimulationOver() const;

    int getStep() const;

    void setDisease(Disease* disease);

    string getVisibleSymptoms() const;


    Parameter requestAnalysis(ParameterID id);


    bool submitDiagnosis(const string& diagnosisName);

    vector<string> getImportantEvents() const;
};

