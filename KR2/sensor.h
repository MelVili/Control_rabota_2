#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include <QDebug>
#include <vector>

// Абстрактный базовый класс сенсора
class Sensor {
public:
    virtual double read() = 0;
    virtual bool is_ready() const = 0;
    virtual QString name() const = 0;
    virtual ~Sensor() = default;
};

// Гироскоп
class Gyroscope : public Sensor {
private:
    double m_value;
    bool m_ready;

public:
    explicit Gyroscope(double value = 1.25, bool ready = true);
    double read() override;
    bool is_ready() const override;
    QString name() const override;

    void setValue(double value);
    void setReady(bool ready);
};

// Акселерометр
class Accelerometer : public Sensor {
private:
    double m_value;
    bool m_ready;

public:
    explicit Accelerometer(double value = 9.81, bool ready = true);
    double read() override;
    bool is_ready() const override;
    QString name() const override;

    void setValue(double value);
    void setReady(bool ready);
};

// Барометр
class Barometer : public Sensor {
private:
    double m_value;
    bool m_ready;

public:
    explicit Barometer(double value = 1012.8, bool ready = true);
    double read() override;
    bool is_ready() const override;
    QString name() const override;

    void setValue(double value);
    void setReady(bool ready);
};

// Функция полиморфной проверки сенсоров
bool check_sensors(const std::vector<Sensor*>& sensors);

#endif // SENSOR_H