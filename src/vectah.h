#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class View;

class Vectah : public QWidget
{
    Q_OBJECT
public:
    Vectah(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void populateScene();

private:
    void setupMatrix();

    QGraphicsScene *scene;
    View *view;
    QSplitter *h1Splitter;
    QSplitter *h2Splitter;
};

#endif // VECTAH_H
