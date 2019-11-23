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

    View *view = new View("Main Icon view");
    scene = new QGraphicsScene(this);
    view->view()->setScene(scene);
    vSplitter->addWidget(view);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);

    setWindowTitle(tr("Icon Example"));
    showMaximized();

    populateScene();
}

void Vectah::populateScene()
{
    QSize icon_size(100,100);
    QSize margin(icon_size*0.4);
    int row = 1;
    int column = 1;

//    scene->setBackgroundBrush(QBrush(QColor(Qt::GlobalColor::black)));

    QDir dir("../assets/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QDirIterator it(dir.path(), QStringList() << "*.svg", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        QGraphicsItem *item = new Icon(it.next(), icon_size);
        item->setPos(QPointF(column*(icon_size.width() + margin.width()), row*(icon_size.height() + margin.height())));
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        scene->addItem(item);

        if(column > 50) {
            column = 0;
            row++;
        }
        column++;
    }

    // Populate scene
    for (int i = 0; i < 0; i += icon_size.width() + margin.width()) {
        for (int j = 0; j < 24000; j += icon_size.height() + margin.height()) {
            QGraphicsItem *item = new Icon(":/Versions.svg", icon_size);
            item->setPos(QPointF(i, j));
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            scene->addItem(item);
        }
    }
}
