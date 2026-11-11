#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QString>
#include <QDebug>

struct Position {
    double latitude;
    double longitude;
    double altitude;
};

// Базовый класс навигационной системы
class NavigationSystem {
public:
    virtual Position get_position() const = 0;
    virtual bool is_valid() const = 0;
    virtual QString system_name() const = 0;
    virtual ~NavigationSystem() = default;
};

// GPS навигация
class GPSNavigation : public NavigationSystem {
private:
    Position m_position;
    int m_satellites;
    bool m_valid;

public:
    GPSNavigation(Position pos, int satellites, bool valid);
    Position get_position() const override;
    bool is_valid() const override; // satellites >= 4 && valid
    QString system_name() const override;

    void setPosition(const Position& pos);
    void setSatellites(int satellites);
    void setValid(bool valid);
};

// Визуальная навигация
class VisualNavigation : public NavigationSystem {
private:
    Position m_position;
    bool m_target_tracked;

public:
    VisualNavigation(Position pos, bool target_tracked);
    Position get_position() const override;
    bool is_valid() const override; // target_tracked
    QString system_name() const override;

    void setPosition(const Position& pos);
    void setTargetTracked(bool tracked);
};

// Функция вывода статуса навигации
void print_navigation_status(const NavigationSystem& navigation);

#endif // NAVIGATION_H