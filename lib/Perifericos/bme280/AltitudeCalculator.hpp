#pragma once
#include <cmath>

class AltitudeCalculator
{
public:
    static float calculateAltitude(float temperatureCelsius, float pressureHpa);
    static float calculateAltitudeWithHumidity(float temperatureCelsius, float pressureHpa, float relativeHumidity);
};