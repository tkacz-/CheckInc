#include "coloredprogressbar.h"

#include <QPainter>
#include <QBrush>
#include <QStyle>
#include <QPen>
#include <QColor>

ColoredProgressBar::ColoredProgressBar(QWidget *parent) : QProgressBar(parent)
{

}

ColoredProgressBar::~ColoredProgressBar()
{

}

void ColoredProgressBar::paintEvent(QPaintEvent*)
{
    int val = value();

    int pos = QStyle::sliderPositionFromValue(minimum(), maximum(), val, width());
    int posB, posE;

    QPainter p(this);

    int pos_draw = 0;
    if (!errors.empty())
    {
        for (quint64 i = 0; i < errors.size(); i++)
        {
            if (val >= 0 && val < errors[i].first)
            {
                p.setPen(Qt::green);
                p.setBrush(QBrush(Qt::green));
                p.drawRect(pos_draw, 0, pos, height());
                break;
            }
            else if (val >= errors[i].first && val <= errors[i].second)
            {
                posB = QStyle::sliderPositionFromValue(minimum(), maximum(), errors[i].first, width());

                p.setPen(Qt::green);
                p.setBrush(QBrush(Qt::green));
                p.drawRect(pos_draw, 0, posB, height());

                p.setPen(Qt::red);
                p.setBrush(QBrush(Qt::red));
                p.drawRect(posB, 0, pos - posB, height());
                break;
            }
            else
            {
                posB = QStyle::sliderPositionFromValue(minimum(), maximum(), errors[i].first, width());
                posE = QStyle::sliderPositionFromValue(minimum(), maximum(), errors[i].first + errors[i].second, width());

                p.setPen(Qt::green);
                p.setBrush(QBrush(Qt::green));
                p.drawRect(pos_draw, 0, posB, height());

                p.setPen(Qt::red);
                p.setBrush(QBrush(Qt::red));
                p.drawRect(posB, 0, posE, height());

                pos_draw = posE;
            }
        }
    }
    else
    {
        p.setPen(Qt::green);
        p.setBrush(QBrush(Qt::green));
        p.drawRect(0, 0, pos, height());
    }

    p.setPen(Qt::lightGray);
    p.setBrush(QBrush(Qt::lightGray));
    p.drawRect(pos, 0, width(), height());

    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));
    p.drawText(0, 0, width(), height(), Qt::AlignCenter, QString::number(val) + " Bytes");
}

void ColoredProgressBar::setErrPos(int err_pos, int err_dis)
{
    this->err_pos = err_pos;
    this->err_dis = err_dis;
    errors.push_back(std::make_pair(this->err_pos, this->err_dis));
}
