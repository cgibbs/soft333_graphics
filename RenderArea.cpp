#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    this->setBackgroundRole(QPalette::Base);
    this->setPalette(pal);
    this->setAutoFillBackground(true);
}

void RenderArea::paintEvent(QPaintEvent *event)
{

}
