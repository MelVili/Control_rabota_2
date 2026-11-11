#include "uav.h"

// Quadcopter
void Quadcopter::takeoff() {
    qDebug() << "Quadcopter: vertical takeoff";
}

void Quadcopter::land() {
    qDebug() << "Quadcopter: vertical landing";
}

QString Quadcopter::type() const {
    return "Quadcopter";
}

// FixedWingUAV
void FixedWingUAV::takeoff() {
    qDebug() << "Fixed-wing UAV: runway takeoff";
}

void FixedWingUAV::land() {
    qDebug() << "Fixed-wing UAV: gliding landing";
}

QString FixedWingUAV::type() const {
    return "Fixed-wing UAV";
}

// Полиморфный запуск испытаний
void run_flight_test(UAV& vehicle) {
    qDebug() << "=== Starting flight test for:" << vehicle.type() << "===";
    vehicle.takeoff();
    vehicle.land();
    qDebug() << "Flight test completed for:" << vehicle.type() << "\n";
}