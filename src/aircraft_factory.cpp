#include "aircraft_factory.hpp"

#include <utility>
#include <algorithm>
#include <cassert>

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Tower& tower)
{
    //assert(airport); // make sure the airport is initialized before creating aircraft

    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();
    int fuel = rand() % 3000 + 150;
    auto new_flight_number =flight_numbers.emplace(flight_number);
    while(new_flight_number.second != true){
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        new_flight_number =flight_numbers.emplace(flight_number);
    } 
    std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft> ( type, flight_number, start, direction, tower, fuel);
    return aircraft;
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Tower& tower)
{
    return create_aircraft(*(aircraft_types[rand() % 3]),tower);
}