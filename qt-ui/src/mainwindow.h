#pragma once

#include <QMainWindow>

class QPushButton;
class QTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void callBackend();

private:
    QPushButton *runBackendButton;
    QTextEdit *outputArea;
};
