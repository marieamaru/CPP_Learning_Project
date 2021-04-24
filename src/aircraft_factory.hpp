#pragma once

#include <string>
#include <set>
#include "aircraft.hpp"
#include "tower.hpp"
class AircraftFactory {

    private :
        const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
        std::set<std::string> flight_numbers;
    public : 
        std::string get_airline(int i){ return airlines[i]; }
        [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Tower& tower);
        [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Tower& tower);
}; 