#ifndef POT_H
#define POT_H

#include "pinout.h"

struct PotReading {
    // TODO: Define your struct here.
    // The members of the struct should be in the range [0, 1).
    double x;
    double y;
    double z;
};

void setupPot();
PotReading readPot();

#endif
