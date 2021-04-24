#pragma once

#include "GL/texture.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <array>

struct AircraftType
{
    const float max_ground_speed;
    const float max_air_speed;
    const float max_accel;
    const GL::Texture2D texture;

    AircraftType(const float max_ground_speed_, const float max_air_speed_, const float max_accel_,
                 const MediaPath& sprite, const size_t num_tiles = NUM_AIRCRAFT_TILES) :
        max_ground_speed { max_ground_speed_ },
        max_air_speed { max_air_speed_ },
        max_accel { max_accel_ },
        texture { new img::Image { sprite.get_full_path() }, num_tiles }
    {
        assert(max_ground_speed >=0.f && "cannot create AircraftType with negative ground speed");
        assert(max_air_speed >= 0.f && "cannot create AircraftType with negative max air speed");
        assert(max_accel >= 0.f && "cannot create AircraftType with negative acceleration");
    }
};

constexpr int NUM_AIRCRAFT_TYPES = 3;
inline AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

inline void init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .08f, .03f, MediaPath { "concorde_af.png" } };
}