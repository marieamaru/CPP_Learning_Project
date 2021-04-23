#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft_factory.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    AircraftFactory factory; 
    int nb_of_crash;

public:
    void add(std::unique_ptr<Aircraft> aircraft);

    bool update() override;

    int count_airlines(int x);

    const std::string get_airline(int i);

    std::unique_ptr<Aircraft> generate_aircraft(Tower& tower);

    int get_crashes();

    int get_required_fuel();
};