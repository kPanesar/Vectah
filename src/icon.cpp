#include "icon.h"

#include <QtWidgets>

Icon::Icon(const QString &fileName, const QSize &size) : QGraphicsSvgItem(fileName)
{
    this->color = QColor(Qt::GlobalColor::blue);
    this->size = QSize(size);
    margin = 20;
}

QRectF Icon::boundingRect() const
{
    return QRectF(0, 0, size.width() + margin, size.height() + margin);
}

void Icon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* unused */)
{
    if((option->state & QStyle::State_Selected))
    {
        QPen pen = painter->pen();
        pen.setColor(color);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->setBrush(QBrush(QColor(230,230,230)));
        painter->drawRect(boundingRect());
    }

    this->renderer()->render(painter, QRectF(margin/2, margin/2, size.width(), size.height()));

}

void Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Icon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void Icon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
