#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;
class Parameter {
private:
    float minValue, maxValue, current;
    int ID;
    string Name;
    string normalRange;
    string unit;

public:
    Parameter(int id = 0, string name = "Unknown", string range = "N/A", string unit = "N/A", float minv = 0, float cur = 0, float maxv = 0)
        : ID(id), Name(name), normalRange(range), unit(unit), minValue(minv), current(cur), maxValue(maxv) {
    }

    float getMin() const { return minValue; }
    float getMax() const { return maxValue; }
    float getCurrent() const { return current; }
    int getId() const { return ID; }

    //operator overloading
    friend ostream& operator<<(ostream& os, const Parameter& p) {
        os << p.Name << ": " << fixed << setprecision(1) << p.current
            << " " << p.unit << " [" << p.normalRange << "]";
        return os;
    }

    string getName() const {
        return Name;
    }

    string getNormalRange() const {
        return normalRange;
    }

    void setCurrent(float value) {
        current = value;
    }

    void applyDelta(float delta) {
        float distToEdge;

        if (delta > 0)
            distToEdge = (maxValue - current);
        else
            distToEdge = (current - minValue);

        float damping = distToEdge / (maxValue - minValue);

        delta *= damping;

        current += delta;

        if (current > maxValue) current = maxValue;
        if (current < minValue) current = minValue;
    }
};

enum ParameterID {

};