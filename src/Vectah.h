//
// Created by Karanvir Panesar on 4/3/18.
//

#ifndef VECTAH_VECTAH_H
#define VECTAH_VECTAH_H

#include <gtkmm/image.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>

#include <librsvg/rsvg.h>
#include <vector>

#include "Icon.h"

#define ICON_PATH "../assets/sample-icons"

class Vectah : public Gtk::ScrolledWindow {

public:
    Vectah();
    ~Vectah();

private:
    //Member widgets:
    std::vector<Icon*> icons;
    Gtk::Grid iconGrid;
};

#endif //VECTAH_VECTAH_H
