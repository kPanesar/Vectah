#ifndef ICON_H
#define ICON_H

#include <QGraphicsSvgItem>
#include <QSvgRenderer>

class Icon : public QGraphicsSvgItem
{
public:
    Icon(const QString &fileName, const QSize &size);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor color;
    QSize size;
    int margin;
};

#endif // ICON_H
