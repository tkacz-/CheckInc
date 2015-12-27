#ifndef CHECKINC_H
#define CHECKINC_H

#include <QWidget>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDataStream>
#include <QDateTime>
#include <QtEndian>

#include "aboutdialog.h"

namespace Ui {
class CheckInc;
}

class Thread2 : public QThread
{
    Q_OBJECT

public:
    void run();

public slots:
    void setFile(const QString fileName);
    void setEndian(const bool endian);

signals:
    void progress(int i);
    void sendErr(int err_pos, int err_dis);
    void numErr(QString i);
    void maximum(int maximum);

private:
    QString fileName;
    bool endian;
};

class Thread4 : public QThread
{
    Q_OBJECT

public:
    void run();

public slots:
    void setFile(const QString fileName);
    void setEndian(const bool endian);

signals:
    void progress(int i);
    void sendErr(int err_pos, int err_dis);
    void numErr(QString i);
    void maximum(int maximum);

private:
    QString fileName;
    bool endian;
};

class CheckInc : public QWidget
{
    Q_OBJECT

public:
    explicit CheckInc(QWidget *parent = 0);
    ~CheckInc();

private slots:
    void open();

    void check();

    void openLog();

    void on_openButton_clicked();

    void on_startButton_clicked();

    void on_open_logButton_clicked();

    void on_aboutButton_clicked();

signals:
    setName(const QString name);
    setEndian(const bool endian);

private:
    Ui::CheckInc *ui;
    aboutDialog *about;
};

#endif // CHECKINC_H
