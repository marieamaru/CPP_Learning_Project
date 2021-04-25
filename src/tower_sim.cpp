#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
    GL::move_queue.emplace(&manager);
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}


void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { manager.add(manager.generate_aircraft(airport->get_tower())); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });

    // TASK_0 C-2: framerate control
    // Framerate cannot equal 0 or the program would get stuck / crash.
    // Also, in a "real" program, the maximal framerate should always be capped (you can see why if you do the
    // bonus part).
    GL::keystrokes.emplace('l', []() { GL::ticks_per_sec = std::max(GL::ticks_per_sec - 1u, 1u); });
    GL::keystrokes.emplace('m', []() { GL::ticks_per_sec = std::min(GL::ticks_per_sec + 1u, 180u); });

    // TASK_0 C-2: pause
    // Since the framerate cannot be 0, we introduce a new variable to manage this info.
    // Also, it would make no sense to use the framerate to simulate the pause, cause how would we unpause if
    // the program is not running anymore ?
    GL::keystrokes.emplace('p', []() { GL::is_paused = !GL::is_paused; });
    GL::keystrokes.emplace('z', [this]() { manager.get_crashes(); } );
    GL::keystrokes.emplace('0', [this]() { manager.count_airlines(0); });
    GL::keystrokes.emplace('1', [this]() { manager.count_airlines(1); });
    GL::keystrokes.emplace('2', [this]() { manager.count_airlines(2); });
    GL::keystrokes.emplace('3', [this]() { manager.count_airlines(3); });
    GL::keystrokes.emplace('4', [this]() { manager.count_airlines(4); });
    GL::keystrokes.emplace('5', [this]() { manager.count_airlines(5); });
    GL::keystrokes.emplace('6', [this]() { manager.count_airlines(6); });
    GL::keystrokes.emplace('7', [this]() { manager.count_airlines(7); });
}


void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key,value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport {one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() },manager };
    assert(airport != nullptr && "airport object cannot be null");
    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    init_aircraft_types();

    GL::loop();
}