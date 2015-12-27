#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);

    ui->label->setPixmap(QIcon(":i/CheckInc.ico").pixmap(64,64));
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
