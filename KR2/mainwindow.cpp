#include "mainwindow.h"
#include "uav.h"
#include "sensor.h"
#include "navigation.h"
#include "controller.h"
#include "autopilot.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFont>

QTextEdit* MainWindow::s_logViewer = nullptr;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    s_logViewer = findChild<QTextEdit*>("logViewer");
}

MainWindow::~MainWindow() {
    s_logViewer = nullptr;
}

void MainWindow::logOutput(const QString& text) {
    if (s_logViewer) {
        s_logViewer->append(text);
    }
}

void MainWindow::setupUI() {
    setWindowTitle("Контрольная работа №2 — Вариант 1 (БПЛА)");
    resize(900, 680);

    auto* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto* mainLayout = new QHBoxLayout(centralWidget);

    // Панель кнопок слева
    auto* leftPanel = new QVBoxLayout();

    // Группа базовых заданий
    auto* tasksGroup = new QGroupBox("Базовые модули", this);
    auto* tasksLayout = new QVBoxLayout(tasksGroup);

    auto* btnTask1 = new QPushButton("Задание 1: Тест БПЛА", this);
    auto* btnTask2 = new QPushButton("Задание 2: Сенсоры контроллера", this);
    auto* btnTask3 = new QPushButton("Задание 3: Навигация (GPS/Vis)", this);

    tasksLayout->addWidget(btnTask1);
    tasksLayout->addWidget(btnTask2);
    tasksLayout->addWidget(btnTask3);
    leftPanel->addWidget(tasksGroup);

    // Группа сценариев Автопилота
    auto* autopilotGroup = new QGroupBox("Тестовые сценарии Autopilot", this);
    auto* apLayout = new QVBoxLayout(autopilotGroup);

    auto* btnScen1 = new QPushButton("Сценарий 1: Штатный цикл (150м)", this);
    auto* btnScen2 = new QPushButton("Сценарий 2: Отказ сенсора", this);
    auto* btnScen3 = new QPushButton("Сценарий 3: Навигация невалидна", this);
    auto* btnScen4 = new QPushButton("Сценарий 4: Контроллер nullptr", this);
    auto* btnScen5 = new QPushButton("Сценарий 5: Отрицательная высота", this);

    apLayout->addWidget(btnScen1);
    apLayout->addWidget(btnScen2);
    apLayout->addWidget(btnScen3);
    apLayout->addWidget(btnScen4);
    apLayout->addWidget(btnScen5);
    leftPanel->addWidget(autopilotGroup);

    auto* btnRunAll = new QPushButton("Запустить ВСЕ тесты", this);
    btnRunAll->setStyleSheet("font-weight: bold; padding: 6px; background-color: #2b5c8f; color: white;");
    auto* btnClear = new QPushButton("Очистить вывод", this);

    leftPanel->addWidget(btnRunAll);
    leftPanel->addWidget(btnClear);
    leftPanel->addStretch();

    // Консоль вывода справа
    auto* rightPanel = new QVBoxLayout();
    auto* logLabel = new QLabel("Журнал выполнения (qDebug output):", this);
    auto* logViewer = new QTextEdit(this);
    logViewer->setObjectName("logViewer");
    logViewer->setReadOnly(true);
    logViewer->setFont(QFont("Consolas", 10));
    logViewer->setStyleSheet("background-color: #1e1e1e; color: #dcdcdc; border-radius: 4px; padding: 8px;");

    rightPanel->addWidget(logLabel);
    rightPanel->addWidget(logViewer);

    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(rightPanel, 2);

    // Связывание сигналов
    connect(btnTask1, &QPushButton::clicked, this, &MainWindow::onRunTask1);
    connect(btnTask2, &QPushButton::clicked, this, &MainWindow::onRunTask2);
    connect(btnTask3, &QPushButton::clicked, this, &MainWindow::onRunTask3);
    connect(btnScen1, &QPushButton::clicked, this, &MainWindow::onRunScenario1);
    connect(btnScen2, &QPushButton::clicked, this, &MainWindow::onRunScenario2);
    connect(btnScen3, &QPushButton::clicked, this, &MainWindow::onRunScenario3);
    connect(btnScen4, &QPushButton::clicked, this, &MainWindow::onRunScenario4);
    connect(btnScen5, &QPushButton::clicked, this, &MainWindow::onRunScenario5);
    connect(btnRunAll, &QPushButton::clicked, this, &MainWindow::onRunAll);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearLog);
}

void MainWindow::onRunTask1() {
    qDebug() << "\n>>> [ЗАДАНИЕ 1: ИСПЫТАНИЯ БПЛА] <<<";
    Quadcopter quad;
    FixedWingUAV plane;
    run_flight_test(quad);
    run_flight_test(plane);
}

void MainWindow::onRunTask2() {
    qDebug() << "\n>>> [ЗАДАНИЕ 2: ТЕСТ СЕНСОРОВ] <<<";
    Gyroscope gyro(1.25, true);
    Accelerometer acc(9.81, true);
    Barometer baro(1012.8, true);

    std::vector<Sensor*> sensors = { &gyro, &acc, &baro };

    qDebug() << "-- Тест 2.1: Все сенсоры исправны --";
    check_sensors(sensors);

    qDebug() << "\n-- Тест 2.2: Имитация отказа акселерометра --";
    acc.setReady(false);
    check_sensors(sensors);
}

void MainWindow::onRunTask3() {
    qDebug() << "\n>>> [ЗАДАНИЕ 3: СИСТЕМЫ НАВИГАЦИИ] <<<";
    Position pos{55.75, 37.61, 150.0};

    qDebug() << "-- GPS валидный (спутников >= 4) --";
    GPSNavigation gpsValid(pos, 8, true);
    print_navigation_status(gpsValid);

    qDebug() << "-- GPS невалидный (мало спутников) --";
    GPSNavigation gpsInvalid(pos, 2, true);
    print_navigation_status(gpsInvalid);

    qDebug() << "-- Визуальная навигация (захват цели есть) --";
    VisualNavigation visValid(pos, true);
    print_navigation_status(visValid);

    qDebug() << "-- Визуальная навигация (потеря цели) --";
    VisualNavigation visInvalid(pos, false);
    print_navigation_status(visInvalid);
}

void MainWindow::onRunScenario1() {
    qDebug() << "\n>>> [СЦЕНАРИЙ 1: Полный штатный цикл автопилота] <<<";
    Quadcopter quad;
    Gyroscope gyro(1.25, true);
    Accelerometer acc(9.81, true);
    Barometer baro(1012.8, true);
    std::vector<Sensor*> sensors = { &gyro, &acc, &baro };

    Position pos{55.75, 37.61, 150.0};
    GPSNavigation gps(pos, 8, true);
    SimpleController controller(0.5); // kp = 0.5 -> control = 50 * 0.5 = 25

    Autopilot ap(&quad, sensors, &gps, &controller, 200.0);
    ap.run_cycle();
}

void MainWindow::onRunScenario2() {
    qDebug() << "\n>>> [СЦЕНАРИЙ 2: Сенсор не готов] <<<";
    Quadcopter quad;
    Gyroscope gyro(1.25, true);
    Accelerometer acc(9.81, false); // Отказ!
    Barometer baro(1012.8, true);
    std::vector<Sensor*> sensors = { &gyro, &acc, &baro };

    Position pos{55.75, 37.61, 150.0};
    GPSNavigation gps(pos, 8, true);
    SimpleController controller(0.5);

    Autopilot ap(&quad, sensors, &gps, &controller, 200.0);
    ap.run_cycle();
}

void MainWindow::onRunScenario3() {
    qDebug() << "\n>>> [СЦЕНАРИЙ 3: Навигация невалидна] <<<";
    Quadcopter quad;
    Gyroscope gyro(1.25, true);
    Accelerometer acc(9.81, true);
    Barometer baro(1012.8, true);
    std::vector<Sensor*> sensors = { &gyro, &acc, &baro };

    Position pos{55.75, 37.61, 150.0};
    GPSNavigation gps(pos, 2, false); // Невалидна
    SimpleController controller(0.5);

    Autopilot ap(&quad, sensors, &gps, &controller, 200.0);
    ap.run_cycle();
}

void MainWindow::onRunScenario4() {
    qDebug() << "\n>>> [СЦЕНАРИЙ 4: Контроллер == nullptr] <<<";
    Quadcopter quad;
    Gyroscope gyro(1.25, true);
    Accelerometer acc(9.81, true);
    Barometer baro(1012.8, true);
    std::vector<Sensor*> sensors = { &gyro, &acc, &baro };

    Position pos{55.75, 37.61, 150.0};
    GPSNavigation gps(pos, 8, true);

    Autopilot ap(&quad, sensors, &gps, nullptr, 200.0);
    ap.run_cycle();
}

void MainWindow::onRunScenario5() {
    qDebug() << "\n>>> [СЦЕНАРИЙ 5: Отрицательная высота] <<<";
    Quadcopter quad;
    Gyroscope gyro(1.25, true);
    Accelerometer acc(9.81, true);
    Barometer baro(1012.8, true);
    std::vector<Sensor*> sensors = { &gyro, &acc, &baro };

    Position pos{55.75, 37.61, -15.0}; // Отрицательная высота
    GPSNavigation gps(pos, 8, true);
    SimpleController controller(0.5);

    Autopilot ap(&quad, sensors, &gps, &controller, 200.0);
    ap.run_cycle();
}

void MainWindow::onRunAll() {
    onRunTask1();
    onRunTask2();
    onRunTask3();
    onRunScenario1();
    onRunScenario2();
    onRunScenario3();
    onRunScenario4();
    onRunScenario5();
}

void MainWindow::onClearLog() {
    if (s_logViewer) {
        s_logViewer->clear();
    }
}