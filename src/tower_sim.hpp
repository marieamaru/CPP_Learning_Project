#pragma once

#include "aircraft_manager.hpp"

class Airport;
struct AircraftType;
class Aircraft;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager manager;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void delete_aircraft(const Aircraft& aircraft) const;

    void create_keystrokes();
    void display_help() const;
    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
