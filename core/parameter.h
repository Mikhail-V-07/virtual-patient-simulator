//Yana
//Toxir
#pragma once 
#include <string> 
class Parameter {
private:
	std::string id;
	std::string name;
	float minV, maxV;
	float current;
	float normal;
	float drift = 0.0f;
public: 
	Parameter(std::string id, std::string name, float minV, float maxV, float current, float normal) 
		:id(id), name(name), normal(normal), current(normal), minV(minV), maxV(maxV) {}; 

	float getValue() const { return current; }
	std::string getName() const { return name; }
	std::string getId() const { return id; }

	void set(float value) {
		if (value < minV) current = minV;
		else if (value > maxV) current = maxV;
		else current = value;
	}



	void applyInstantChange(float value) {
		set(current + value);
	}

	void addDrift(float d) {
		drift += d;
	}

	void resetDrift() {
		drift = 0.0;
	}

	void step(strength) {
		set(current + drift);
		applyHomeostasis(0.01);
	}

	void applyHomeostasis(float strength = 0.01f) {
		current += (normal - current) * strength;
	}
};