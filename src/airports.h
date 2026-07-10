#pragma once

#include <stddef.h>

struct RunwaySegment {
    const char *icao;
    float lat;
    float lon;
    float headingDeg;
    float lengthKm;
};

static const RunwaySegment kRunways[] = {
    {"LEVC", 39.4893f, -0.4816f, 120.0f, 3.2f},
    {"LEVC", 39.4893f, -0.4816f, 300.0f, 3.2f},
    {"LEAL", 38.2822f, -0.5582f, 100.0f, 3.0f},
    {"LEAL", 38.2822f, -0.5582f, 280.0f, 3.0f},
    {"LEIB", 38.8729f, 1.3731f, 60.0f, 2.8f},
    {"LEMH", 39.8626f, 4.2186f, 10.0f, 2.6f},
    {"LEAS", 43.5636f, -6.0346f, 110.0f, 2.2f},
    {"LEBB", 43.3011f, -2.9106f, 120.0f, 2.6f},
    {"LEST", 42.8963f, -8.4151f, 170.0f, 3.2f},
    {"LEXJ", 43.4271f, -3.8200f, 110.0f, 2.4f},
    {"LEZL", 37.4180f, -5.8931f, 90.0f, 3.4f},
    {"LEGR", 37.1887f, -3.7774f, 90.0f, 2.9f},
    {"GCLP", 27.9319f, -15.3866f, 30.0f, 3.1f},
    {"GCTS", 28.0445f, -16.5725f, 80.0f, 3.2f},
    {"LEBL", 41.2971f, 2.0785f, 70.0f, 3.4f},
    {"LEBL", 41.2971f, 2.0785f, 250.0f, 3.4f},
    {"LEMD", 40.4983f, -3.5676f, 140.0f, 4.1f},
    {"LEMD", 40.4983f, -3.5676f, 320.0f, 4.1f},
    {"LEPA", 39.5517f, 2.7388f, 60.0f, 3.2f},
    {"LEMG", 36.6749f, -4.4991f, 130.0f, 3.2f},
    {"LFPG", 49.0097f, 2.5479f, 80.0f, 4.2f},
    {"LFPO", 48.7233f, 2.3794f, 60.0f, 3.6f},
    {"EGLL", 51.4700f, -0.4543f, 90.0f, 3.9f},
    {"EHAM", 52.3105f, 4.7683f, 180.0f, 3.8f},
    {"EDDF", 50.0379f, 8.5622f, 70.0f, 4.0f},
    {"LIRF", 41.8003f, 12.2389f, 160.0f, 3.9f},
    {"KJFK", 40.6413f, -73.7781f, 40.0f, 4.4f},
    {"KLAX", 33.9416f, -118.4085f, 70.0f, 3.7f},
};

static constexpr size_t kRunwayCount = sizeof(kRunways) / sizeof(kRunways[0]);
