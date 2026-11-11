#include "navigation.h"

// GPSNavigation
GPSNavigation::GPSNavigation(Position pos, int satellites, bool valid)
    : m_position(pos), m_satellites(satellites), m_valid(valid) {}

Position GPSNavigation::get_position() const {
    return m_position;
}

bool GPSNavigation::is_valid() const {
    return (m_satellites >= 4) && m_valid;
}

QString GPSNavigation::system_name() const {
    return "GPS";
}

void GPSNavigation::setPosition(const Position& pos) { m_position = pos; }
void GPSNavigation::setSatellites(int satellites) { m_satellites = satellites; }
void GPSNavigation::setValid(bool valid) { m_valid = valid; }

// VisualNavigation
VisualNavigation::VisualNavigation(Position pos, bool target_tracked)
    : m_position(pos), m_target_tracked(target_tracked) {}

Position VisualNavigation::get_position() const {
    return m_position;
}

bool VisualNavigation::is_valid() const {
    return m_target_tracked;
}

QString VisualNavigation::system_name() const {
    return "Visual Navigation";
}

void VisualNavigation::setPosition(const Position& pos) { m_position = pos; }
void VisualNavigation::setTargetTracked(bool tracked) { m_target_tracked = tracked; }

// Вывод статуса
void print_navigation_status(const NavigationSystem& navigation) {
    Position pos = navigation.get_position();
    qDebug().noquote() << "Navigation system:" << navigation.system_name();
    qDebug().noquote() << QString("Position: %1, %2, %3")
                              .arg(pos.latitude)
                              .arg(pos.longitude)
                              .arg(pos.altitude);
    qDebug().noquote() << "Status:" << (navigation.is_valid() ? "Valid" : "Invalid") << "\n";
}