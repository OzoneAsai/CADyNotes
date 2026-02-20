#include "mainwindow.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), runBackendButton(new QPushButton("Run Rust backend", this)),
      outputArea(new QTextEdit(this)) {
    setWindowTitle("CADyNotes - Rust + Qt starter");
    resize(720, 480);

    outputArea->setReadOnly(true);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(runBackendButton);
    layout->addWidget(outputArea);
    setCentralWidget(central);

    connect(runBackendButton, &QPushButton::clicked, this, &MainWindow::callBackend);

    outputArea->append("Click \"Run Rust backend\" to test communication.");
}

void MainWindow::callBackend() {
    QString backendPath = qEnvironmentVariable("CADYNOTES_BACKEND_BIN");
    if (backendPath.isEmpty()) {
#ifdef Q_OS_WIN
        backendPath = QStringLiteral("..\\rust-backend\\target\\debug\\cadynotes-backend.exe");
#else
        backendPath = QStringLiteral("../rust-backend/target/debug/cadynotes-backend");
#endif
    }

    QProcess backend;
    backend.start(backendPath, QStringList() << "hello-from-qt");
    if (!backend.waitForFinished(3000)) {
        outputArea->append(QString("[%1] Backend start failed: %2")
                               .arg(QDateTime::currentDateTime().toString(Qt::ISODate),
                                    backend.errorString()));
        return;
    }

    const QByteArray stdoutData = backend.readAllStandardOutput().trimmed();
    const QByteArray stderrData = backend.readAllStandardError().trimmed();

    if (!stderrData.isEmpty()) {
        outputArea->append(QString("stderr: %1").arg(QString::fromUtf8(stderrData)));
    }

    const QJsonDocument jsonDoc = QJsonDocument::fromJson(stdoutData);
    if (!jsonDoc.isObject()) {
        outputArea->append(QString("[%1] Non-JSON response: %2")
                               .arg(QDateTime::currentDateTime().toString(Qt::ISODate),
                                    QString::fromUtf8(stdoutData)));
        return;
    }

    const QJsonObject obj = jsonDoc.object();
    outputArea->append(QString("[%1] %2 (%3): %4")
                           .arg(QDateTime::currentDateTime().toString(Qt::ISODate),
                                obj.value("app").toString(), obj.value("version").toString(),
                                obj.value("message").toString()));
}
