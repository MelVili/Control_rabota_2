#ifndef UAV_H
#define UAV_H

#include <QString>
#include <QDebug>

// Абстрактный базовый класс БПЛА
class UAV {
public:
    virtual void takeoff() = 0;
    virtual void land() = 0;
    virtual QString type() const = 0;
    virtual ~UAV() = default;
};

// Квадрокоптер
class Quadcopter : public UAV {
public:
    void takeoff() override;
    void land() override;
    QString type() const override;
};

// БПЛА самолетного типа
class FixedWingUAV : public UAV {
public:
    void takeoff() override;
    void land() override;
    QString type() const override;
};

// Универсальная функция летных испытаний
void run_flight_test(UAV& vehicle);

#endif // UAV_H