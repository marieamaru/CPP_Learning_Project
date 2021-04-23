#include "aircraft_manager.hpp"

#include <utility>
#include <algorithm>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end());

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [this](std::unique_ptr<Aircraft>& aircraft) { 
        try 
        {
            return !aircraft->update();
        } 
        catch(const AircraftCrash& e)
        {
            nb_of_crash++;                
            std::cerr << e.what() << '\n';
            return true;
        }
    }),aircrafts.end());
    return true;
}

int AircraftManager::count_airlines(int x)
{
    const auto compare = [x, this](std::unique_ptr<Aircraft>& aircraft){ return aircraft->get_flight_num().find(factory.get_airline(x))!=std::string::npos;};
    auto count = count_if(aircrafts.begin(),aircrafts.end(),compare);
    std::cout << count << std::endl;
    return count;
}

const std::string AircraftManager::get_airline(int i)
{
    return factory.get_airline(i);
}

std::unique_ptr<Aircraft> AircraftManager::generate_aircraft(Tower& tower)
{
    return factory.create_random_aircraft(tower);
}

int AircraftManager::get_crashes()
{
    std::cout << nb_of_crash << " aircrafts have crashed so far." << std::endl;
    return nb_of_crash;
}

int AircraftManager::get_required_fuel()
{
    int sum =0;
    for (const auto& aircraft : aircrafts)
    {
        if (aircraft->is_low_on_fuel() && !aircraft->is_service_done)
        {
            sum += (3000 - aircraft->fuel);
        }
    }
    return sum;
}