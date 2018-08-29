//
// Created by Karanvir Panesar on 8/28/18.
//

#ifndef VECTAH_ICON_H
#define VECTAH_ICON_H

#include <gtkmm/image.h>
#include <iostream>

class Icon: public Gtk::Image {
public:
    explicit Icon(std::string file);
};


#endif //VECTAH_ICON_H
