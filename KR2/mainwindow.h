#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    static void logOutput(const QString& text);

private slots:
    void onRunTask1();
    void onRunTask2();
    void onRunTask3();
    void onRunScenario1();
    void onRunScenario2();
    void onRunScenario3();
    void onRunScenario4();
    void onRunScenario5();
    void onRunAll();
    void onClearLog();

private:
    void setupUI();
    static QTextEdit* s_logViewer;
};

#endif // MAINWINDOW_H