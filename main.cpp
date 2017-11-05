#include <string>
#include <iostream>
#include <cairomm/context.h>

int main()
{
    std::string filename = "image.svg";
    double width = 1920;
    double height = 1080;
    Cairo::RefPtr<Cairo::SvgSurface> surface = Cairo::SvgSurface::create(filename, width, height);

    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

    cr->save(); // save the state of the context
    cr->set_source_rgb(0.1, 0.1, 0.1);
    cr->paint(); // fill image with the color
    cr->restore(); // color is back to black now

    cr->save();
    cr->set_source_rgba(1, 1, 1, 0.7);
    // draw a circle in the center of the image
    cr->arc(width/2.0, height/2.0, height/4.0, M_PI, 0);
    cr->stroke();

    // draw a diagonal line
    double line_width = cr->get_line_width();
    cr->move_to(0, height/2 + line_width/2);
    cr->line_to(width, height/2 + line_width/2);
    cr->stroke();
    cr->restore();

    cr->show_page();

    std::cout << "Wrote SVG file \"" << filename << "\"" << std::endl;
    return 0;
}