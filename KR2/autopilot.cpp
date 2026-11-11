#include "autopilot.h"

Autopilot::Autopilot(UAV* vehicle,
                     const std::vector<Sensor*>& sensors,
                     NavigationSystem* navigation,
                     FlightController* controller,
                     double target_alt)
    : vehicle(vehicle), sensors(sensors), navigation(navigation),
    controller(controller), target_altitude(target_alt) {}

bool Autopilot::run_cycle() {
    qDebug() << "Autopilot cycle started";

    // 1. Проверка наличия БПЛА
    if (vehicle == nullptr) {
        qDebug() << "Error: vehicle is not set";
        return false;
    }

    // 2. Проверка сенсоров
    if (sensors.empty()) {
        qDebug() << "Autopilot cycle aborted / Reason: sensor failure";
        return false;
    }
    for (const auto* sensor : sensors) {
        if (sensor == nullptr || !sensor->is_ready()) {
            qDebug() << "Autopilot cycle aborted / Reason: sensor failure";
            return false;
        }
    }
    qDebug() << "All sensors are ready";

    // 3. Проверка навигации
    if (navigation == nullptr || !navigation->is_valid()) {
        qDebug() << "Navigation data invalid";
        return false;
    }

    // 4. Проверка позиции
    Position pos = navigation->get_position();
    if (pos.altitude < 0.0) {
        qDebug() << "Error: invalid navigation position";
        return false;
    }

    // 5. Проверка контроллера
    if (controller == nullptr) {
        qDebug() << "Error: flight controller is not set";
        return false;
    }

    // 6. Расчет ошибки высоты
    double error = target_altitude - pos.altitude;

    // 7. Расчет управления (dt = 0.1)
    double control = controller->calculate_control(error, 0.1);

    // 8. Вывод результата
    qDebug().noquote() << "Navigation:" << navigation->system_name();
    qDebug().noquote() << QString("Current altitude: %1 m").arg(pos.altitude);
    qDebug().noquote() << QString("Target altitude: %1 m").arg(target_altitude);
    qDebug().noquote() << QString("Altitude error: %1 m").arg(error);
    qDebug().noquote() << QString("Controller output: %1").arg(control);
    qDebug() << "Autopilot cycle completed";

    return true;
}