//
// Created by Karanvir Panesar on 4/3/18.
//

#ifndef VECTAH_VECTAH_H
#define VECTAH_VECTAH_H

#include <gtkmm/window.h>
#include "IconArea.h"

class Vectah : public Gtk::Window {

public:
    Vectah();
    virtual ~Vectah();

private:
    //Member widgets:
    IconArea icon_area;
};

#endif //VECTAH_VECTAH_H
