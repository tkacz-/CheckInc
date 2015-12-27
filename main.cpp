/*
 * Copyright 2015 Andrei Tkachenko(@tkacz-) include.free@gmail.com
 *
 * This program check increment at the files (.dat) and write into the log.txt
 * position of the errors. It's working for data of 2 or 4 bytes.
 *
 *
 */

#include "CheckInc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CheckInc w;
    w.show();

    return a.exec();
}
