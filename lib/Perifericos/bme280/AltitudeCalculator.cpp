#include "AltitudeCalculator.hpp"

float AltitudeCalculator::calculateAltitude(float temperatureCelsius, float pressureHpa)
{
    const float P0 = 1013.25; // Pressão ao nível do mar em hPa
    const float n = 5.255;    // Constante para modelo atmosférico
    const float temperatureKelvin = temperatureCelsius + 273.15;
    const float gradient = 0.0065; // Gradiente de temperatura em K/m

    float altitude = (1 - pow(pressureHpa / P0, 1 / n)) * (temperatureKelvin / gradient);
    return altitude;
}

float AltitudeCalculator::calculateAltitudeWithHumidity(float temperatureCelsius, float pressureHpa, float relativeHumidity)
{
    const float P0 = 1013.25; // Pressão ao nível do mar em hPa
    const float n = 5.255;    // Constante para o modelo atmosférico
    const float temperatureKelvin = temperatureCelsius + 273.15;
    const float gradient = 0.0065; // Gradiente de temperatura em K/m
    const float humidityAdjustmentFactor = 1.0 - (relativeHumidity / 100.0) * 0.02;
    float altitude = (1 - std::pow(pressureHpa / P0, 1 / n)) * (temperatureKelvin / gradient);
    altitude *= humidityAdjustmentFactor; // Ajustando a altitude com base na umidade.
    return altitude;
}
