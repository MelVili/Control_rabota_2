#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <QDebug>

class FlightController {
public:
    virtual double calculate_control(double error, double dt) = 0;
    virtual QString controller_name() const = 0;
    virtual ~FlightController() = default;
};

// Простой пропорциональный регулятор
class SimpleController : public FlightController {
private:
    double m_coefficient;

public:
    explicit SimpleController(double coefficient = 0.5);
    double calculate_control(double error, double dt) override;
    QString controller_name() const override;
};

// ПИД-регулятор
class PIDController : public FlightController {
private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_integral;
    double m_previous_error;

public:
    PIDController(double kp = 0.5, double ki = 0.0, double kd = 0.0);
    double calculate_control(double error, double dt) override;
    QString controller_name() const override;
};

#endif // CONTROLLER_H