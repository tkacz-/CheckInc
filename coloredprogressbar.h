#ifndef COLOREDPROGRESSBAR_H
#define COLOREDPROGRESSBAR_H


#include <QWidget>
#include <QProgressBar>
#include <QPaintEvent>
#include <vector>

class ColoredProgressBar : public QProgressBar
{
    Q_OBJECT

private:
    int err_pos, err_dis;
    std::vector<std::pair<int, int> > errors;

public:
    explicit ColoredProgressBar(QWidget *parent = 0);
    ~ColoredProgressBar();

protected:
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

signals:

public slots:
    void setErrPos(int err_pos, int err_dis);
};


#endif // COLOREDPROGRESSBAR_H
