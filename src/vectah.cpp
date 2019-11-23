#include "icon.h"
#include "vectah.h"
#include "view.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QDirIterator>

Vectah::Vectah(QWidget *parent)
    : QWidget(parent)
{
    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);

    view = new View("Main Icon view");
    scene = new QGraphicsScene(this);
    view->view()->setScene(scene);
    vSplitter->addWidget(view);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);

    setWindowTitle(tr("Icon Example"));
    showMaximized();
}

void Vectah::populateScene()
{
    QSize icon_size(100,100);
    QSize margin(icon_size*0.4);
    int row = 1;
    int column = 0;
    int max_size = view->size().width() - (icon_size.width()*2);

//    scene->setBackgroundBrush(QBrush(QColor(Qt::GlobalColor::black)));
    scene->clear();

    QDir dir("../assets");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QDirIterator it(dir.path(), QStringList() << "*.svg", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        QGraphicsItem *item = new Icon(it.next(), icon_size);
        int x = column*(icon_size.width() + margin.width());
        int y = row*(icon_size.height() + margin.height());

        if(x > max_size) {
            column = 0;
            row++;
        }
        else
        {
            item->setPos(QPointF(x, y));
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            scene->addItem(item);
            column++;
        }

    }
}

void Vectah::resizeEvent(QResizeEvent* event)
{
   QWidget::resizeEvent(event);
   this->populateScene();
}
