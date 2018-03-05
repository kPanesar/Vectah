//
// Created by karan on 4/3/18.
//

#ifndef VECTAH_VECTAH_H
#define VECTAH_VECTAH_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Vectah : public Gtk::Window
{

public:
    Vectah();
    virtual ~Vectah();

protected:
    //Signal handlers:
    void OnButtonClicked();

    //Member widgets:
    Gtk::Button m_button;
};

#endif //VECTAH_VECTAH_H
