//
// Created by Karanvir Panesar on 5/3/18.
//

#ifndef VECTAH_ICONAREA_H
#define VECTAH_ICONAREA_H

#include <gtkmm/drawingarea.h>

class IconArea : public Gtk::DrawingArea {

public:
    IconArea();
    virtual ~IconArea();

protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    Glib::RefPtr<Gdk::Pixbuf> image;
    bool on_timeout();

    double m_radius;
    double m_line_width;
};

#endif //VECTAH_ICONAREA_H
