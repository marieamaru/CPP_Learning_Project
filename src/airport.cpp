#include "airport.hpp"
#include "aircraft_manager.hpp"

bool Airport::update() override
{
        if(next_refill_time == 0)
        {
            fuel_stock+=ordered_fuel;
            ordered_fuel = std::min(manager->get_required_fuel(), 5000);
            next_refill_time = 100;
            std::cout << ordered_fuel << " of fuel was ordered, there is now  " << fuel_stock << " of fuel stock" << std::endl;
        }
        else 
        {
            next_refill_time--;
            for (auto terminal : terminals)
            {
                terminal.refill_aircraft_if_needed(fuel_stock);
            }
        }
        for (auto& t : terminals)
        {
            t.update();
        }

        return true;
    }