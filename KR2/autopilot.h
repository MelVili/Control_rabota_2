#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include <vector>
#include "uav.h"
#include "sensor.h"
#include "navigation.h"
#include "controller.h"

class Autopilot {
private:
    UAV* vehicle;
    std::vector<Sensor*> sensors;
    NavigationSystem* navigation;
    FlightController* controller;
    double target_altitude;

public:
    Autopilot(UAV* vehicle,
              const std::vector<Sensor*>& sensors,
              NavigationSystem* navigation,
              FlightController* controller,
              double target_altitude = 200.0);

    bool run_cycle();
};

#endif // AUTOPILOT_H