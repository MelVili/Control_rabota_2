#include "controller.h"

SimpleController::SimpleController(double coefficient) : m_coefficient(coefficient) {}

double SimpleController::calculate_control(double error, double dt) {
    Q_UNUSED(dt);
    return m_coefficient * error;
}

QString SimpleController::controller_name() const {
    return "Simple";
}

PIDController::PIDController(double kp, double ki, double kd)
    : m_kp(kp), m_ki(ki), m_kd(kd), m_integral(0.0), m_previous_error(0.0) {}

double PIDController::calculate_control(double error, double dt) {
    if (dt <= 0.0) return 0.0;
    m_integral += error * dt;
    double derivative = (error - m_previous_error) / dt;
    double output = m_kp * error + m_ki * m_integral + m_kd * derivative;
    m_previous_error = error;
    return output;
}

QString PIDController::controller_name() const {
    return "PID";
}