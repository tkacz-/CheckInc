#ifndef CHECK
#define CHECK

#include "CheckInc.h"

void Thread2::setFile(const QString fileName)
{
    this->fileName = fileName;
}

void Thread2::setEndian(const bool endian)
{
    this->endian = endian;
}

void Thread4::setFile(const QString fileName)
{
    this->fileName = fileName;
}

void Thread4::setEndian(const bool endian)
{
    this->endian = endian;
}

/**
 * @brief Check two-bytes increments in the file
 * @param endian Flag of endian numbers (true for a big endian)
 * @param filename Name of the file
 */
void Thread2::run()
{
    QFile fin(fileName);
    fin.open(QIODevice::ReadOnly);

    if (!QDir("logs").exists())
        QDir().mkdir("logs");
    QFileInfo f(fileName);
    QFile fout("logs/log-"+f.fileName()+"-.txt");
    fout.open(QIODevice::WriteOnly | QIODevice::Text);
    fout.write("[     #][       DEC = 	         HEX]	[                                DUMP]	[  DISTANSE]	[ LEN]\n");

    QDataStream stream(&fin);

    quint64 numOfError = 0;     /**< number of increment errors */
    quint64 n = fin.size();    /**< size of file = number of bytes in file */
    emit maximum(n - 1);
    uchar buff[n];              /**< buffer of file's bytes */
    stream >> buff[0];
    stream >> buff[1];

    /**
     * @var i is count of beginner byte
     * @var count is count for reading bytes
     */
    quint64 i = 0, count = 2;

    /**
     * @var dis is number of the incorrect numbers for this error
     * @var pos is the number of the first increment error
     */
    quint64 dis = 0, pos = 0;

    quint64 countProgress = 0;

    /**
      * Read bytes from the file into the array if count of bytes < size of file.
      * Make two bytes into an integer.
      * If the incement is correct, write into the log-file "=". It means everything is right.
      * If the increment isn't correct, write into the log-file
      *     [#numOfErrors][#pos = #pos (hex)] [#first_number #second number ... ] [#dis * 2 - 2] [#dis]
      * which has these variables:
      *     - #numOfErrors is number of increment errors
      *     - #pos is the number of the first increment error
      *     - #pos(hex) is the address of the first increment error
      *     - #first_number is the first two-bytes number from the file
      *     - #second_number is the second two-bytes number from the file
      *     - (#dis * 2 - 2) is the number of the last byte of the correct number since incorrect increments
      *     - #dis is the number of the incorrect numbers for this error
      */
    while (i + 3 < n)
    {
        if (count < n)
            stream >> buff[count];
        if (count + 1 < n)
            stream >> buff[count + 1];
        quint16 first_number, second_number;
        switch (endian) {
        case true:
            first_number = qFromBigEndian<quint16>((const uchar*)buff + i);
            second_number = qFromBigEndian<quint16>((const uchar*)buff + i + 2);
            break;
        default:
            first_number = qFromLittleEndian<quint16>((const uchar*)buff + i);
            second_number = qFromLittleEndian<quint16>((const uchar*)buff + i + 2);
            break;
        }
        if (second_number - first_number == 1)
        {
            if (dis != 0)
            {
                fout.write(QString("] [%1] [%2]    ").arg(dis * 2 - 2, 10, 10, QLatin1Char('0'))
                        .arg(dis, 4, 10, QLatin1Char('0')).toUtf8());
                emit sendErr(pos, dis * 2 - 2);
            }
            else
                fout.write("=");
            countProgress = i + 3;
            emit progress(countProgress);
            dis = 0;
            i += 2;
        }
        else
        {
            if (dis == 0)
            {
                pos = i + 2;
                numOfError++;
                dis++;
                fout.write(QString("[%1][%2 = 0x%3]    [%4 %5").arg(numOfError, 6, 10, QLatin1Char('0'))
                        .arg(pos, 10, 10, QLatin1Char('0')).arg(pos, 10, 16, QLatin1Char('0'))
                        .arg(first_number).arg(second_number).toUtf8());
            }
            else
            {
                dis++;
                fout.write(QString(" %1 %2").arg(first_number).arg(second_number).toUtf8());
            }
            countProgress = i + 2;
            emit progress(countProgress);
            i++;            
        }
        count += 2;
        if (i + 3 >= n && dis > 0)
        {
            fout.write(QString("] [%1] [%2]    ").arg(dis * 2 - 2, 10, 10, QLatin1Char('0'))
                    .arg(dis, 4, 10, QLatin1Char('0')).toUtf8());
            countProgress += 2;
            emit sendErr(pos, dis * 2 - 2);
            emit progress(countProgress);
        }
    }
    emit numErr(QString::number(numOfError));
    fout.write(QString("\nNumber of errors: %1").arg(numOfError).toUtf8());
    fin.close();
    fout.close();
}

/**
 * @brief Check four-bytes increments in the file
 * @param endian Flag of endian numbers (true for a big endian)
 * @param filename Name of the file
 */
void Thread4::run()
{
    QFile fin(fileName);
    fin.open(QIODevice::ReadOnly);

    if (!QDir("logs").exists())
        QDir().mkdir("logs");
    QFileInfo f(fileName);
    QFile fout("logs/log-"+f.fileName()+"-.txt");
    fout.open(QIODevice::WriteOnly | QIODevice::Text);
    fout.write("[     #][       DEC = 	         HEX]	[                                DUMP]	[  DISTANSE]	[ LEN]\n");

    QDataStream stream(&fin);

    quint64 numOfError = 0;     /**< number of increment errors */
    quint64 n = fin.size();    /**< size of file = number of bytes in file */
    emit maximum(n - 1);
    uchar buff[n];              /**< buffer of file's bytes */
    stream >> buff[0];
    stream >> buff[1];
    stream >> buff[2];
    stream >> buff[3];

    /**
     * @var i is count of beginner byte
     * @var count is count for reading bytes
     */
    quint64 i = 0, count = 4;

    /**
     * @var dis is number of the incorrect numbers for this error
     * @var pos is the number of the first increment error
     */
    quint64 dis = 0, pos = 0;

    quint64 countProgress = 0;

    /**
      * Read bytes from the file into the array if count of bytes < size of file.
      * Make four bytes into an integer.
      * If the incement is correct, write into the log-file "=". It means everything is right.
      * If the increment isn't correct, write into the log-file
      *     [#numOfErrors][#pos = #pos (hex)] [#first_number #second number ... ] [#dis * 2 - 2] [#dis]
      * which has these variables:
      *     - #numOfErrors is number of increment errors
      *     - #pos is the number of the first increment error
      *     - #pos(hex) is the address of the first increment error
      *     - #first_number is the first four-bytes number from the file
      *     - #second_number is the second four-bytes number from the file
      *     - (#dis * 2 - 2) is the number of incorrect bytes
      *     - #dis is the number of the incorrect numbers for this error
      */
    while (i + 7 < n)
    {
        if (count < n)
            stream >> buff[count];
        if (count + 1 < n)
            stream >> buff[count + 1];
        if (count + 2 < n)
            stream >> buff[count + 2];
        if (count + 3 < n)
            stream >> buff[count + 3];
        quint32 first_number, second_number;
        switch (endian) {
        case true:
            first_number = qFromBigEndian<quint32>((const uchar*)buff + i);
            second_number = qFromBigEndian<quint32>((const uchar*)buff + i + 4);
            break;
        default:
            first_number = qFromLittleEndian<quint32>((const uchar*)buff + i);
            second_number = qFromLittleEndian<quint32>((const uchar*)buff + i + 4);
            break;
        }
        if (second_number - first_number == 1)
        {
            if (dis != 0)
            {
                fout.write(QString("] [%1] [%2]    ").arg(dis * 4 - 4, 10, 10, QLatin1Char('0'))
                        .arg(dis, 4, 10, QLatin1Char('0')).toUtf8());
                emit sendErr(pos, dis * 4 - 4);
            }
            else
                fout.write("=");            
            countProgress = i + 7;
            emit progress(countProgress);
            dis = 0;
            i += 4;
        }
        else
        {
            if (dis == 0)
            {
                pos = i + 4;
                numOfError++;
                dis++;
                fout.write(QString("[%1][%2 = 0x%3]    [%4 %5").arg(numOfError, 6, 10, QLatin1Char('0'))
                        .arg(pos, 10, 10, QLatin1Char('0')).arg(pos, 10, 16, QLatin1Char('0'))
                        .arg(first_number).arg(second_number).toUtf8());
            }
            else
            {
                dis++;
                fout.write(QString(" %1 %2").arg(first_number).arg(second_number).toUtf8());
            }
            countProgress = i + 6;
            emit progress(countProgress);
            i++;            
        }
        count += 2;
        if (i + 7 >= n && dis > 0)
        {
            fout.write(QString("] [%1] [%2]    ").arg(dis * 4 - 4, 10, 10, QLatin1Char('0'))
                    .arg(dis, 4, 10, QLatin1Char('0')).toUtf8());
            countProgress += 2;
            emit sendErr(pos, dis * 4 - 4);
            emit progress(countProgress);
        }
    }
    emit numErr(QString::number(numOfError));
    fout.write(QString("\nNumber of errors: %1").arg(numOfError).toUtf8());
    fin.close();
    fout.close();
}

#endif // CHECK
