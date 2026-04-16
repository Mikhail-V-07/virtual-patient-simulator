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
	float delta;
public: 
	Parameter(std::string id, std::string name, float minV, float maxV, float current, float normal) 
		:id(id), name(name), normal(normal), current(normal), minV(minV), maxV(maxV) {}; 
	float getValue() const { return current; }

	std::string getName() const { return name; }

	std::string getId() const { return id; }

	void set(float value) {
		if (value < minv) current = minv;
		else if (value > maxv) current = maxv;
		else current = value;
	}

	void newDelta(double d) {
		delta = d;
	}

	void update(float delta) {
		set(current + delta);
	}
};