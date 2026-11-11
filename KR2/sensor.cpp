#include "sensor.h"

// Gyroscope
Gyroscope::Gyroscope(double value, bool ready) : m_value(value), m_ready(ready) {}
double Gyroscope::read() { return m_value; }
bool Gyroscope::is_ready() const { return m_ready; }
QString Gyroscope::name() const { return "Gyroscope"; }
void Gyroscope::setValue(double value) { m_value = value; }
void Gyroscope::setReady(bool ready) { m_ready = ready; }

// Accelerometer
Accelerometer::Accelerometer(double value, bool ready) : m_value(value), m_ready(ready) {}
double Accelerometer::read() { return m_value; }
bool Accelerometer::is_ready() const { return m_ready; }
QString Accelerometer::name() const { return "Accelerometer"; }
void Accelerometer::setValue(double value) { m_value = value; }
void Accelerometer::setReady(bool ready) { m_ready = ready; }

// Barometer
Barometer::Barometer(double value, bool ready) : m_value(value), m_ready(ready) {}
double Barometer::read() { return m_value; }
bool Barometer::is_ready() const { return m_ready; }
QString Barometer::name() const { return "Barometer"; }
void Barometer::setValue(double value) { m_value = value; }
void Barometer::setReady(bool ready) { m_ready = ready; }

// Полиморфный обход сенсоров
bool check_sensors(const std::vector<Sensor*>& sensors) {
    qDebug() << "Checking sensors...";
    bool all_ready = true;

    for ( auto* sensor : sensors) {
        if (!sensor) {
            qDebug() << "Error: null sensor pointer encountered!";
            all_ready = false;
            continue;
        }

        if (sensor->is_ready()) {
            qDebug().noquote() << QString("%1: Ready, value = %2")
            .arg(sensor->name())
                .arg(sensor->read());
        } else {
            qDebug().noquote() << QString("%1: NOT Ready (failure)")
            .arg(sensor->name());
            all_ready = false;
        }
    }

    if (all_ready && !sensors.empty()) {
        qDebug() << "All sensors are ready";
        return true;
    } else {
        qDebug() << "sensor failure";
        return false;
    }
}