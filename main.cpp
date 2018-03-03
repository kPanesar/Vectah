#include <string>
#include <iostream>
#include <cairo/cairo.h>
#include <cairomm/context.h>
#include <librsvg/rsvg.h>
#include <ctime>

using namespace std;

void testCairo(string filename);

int main()
{
    clock_t start = clock();

    string filename = "image.svg";
    string filename2 = "imageOut.svg";
    string filename3 = "imageOut.png";

    GError *error = new GError();
    GError **errorPtrPtr = &error;
    RsvgHandle* handle = rsvg_handle_new_from_file(filename.data(), errorPtrPtr);
    RsvgDimensionData *dimension_data = new RsvgDimensionData();
    rsvg_handle_get_dimensions(handle, dimension_data);

    int width = dimension_data->width;
    int height = dimension_data->height;
    cairo_surface_t * csurface = cairo_svg_surface_create(filename2.data(), width, height);
    cairo_t *cr = cairo_create (csurface);

    if(handle)
    {
        rsvg_handle_render_cairo(handle, cr);
//        cairo_surface_write_to_png(csurface, filename3.data());
        cairo_show_page(cr);
        cairo_surface_finish(csurface);
    }
    else
    {
        cout << "Failed to read the SVG file!" << endl;
        cout << error->message << endl;
    }

    // Free the RsvgHandle
//    g_object_unref(handle);

    clock_t end = clock();

    double run_time = (end - start)/(double) CLOCKS_PER_SEC;
    cout << "The operation took " << run_time * 1000 << " milliseconds.";

    g_object_unref(handle);

    return 0;
}

void testCairo(string filename)
{
    double width = 1920;
    double height = 1080;

    Cairo::RefPtr<Cairo::SvgSurface> surface = Cairo::SvgSurface::create(filename, width, height);
    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

    cr->save(); // save the state of the context
    cr->set_source_rgb(0.1, 0.1, 0.1);
    cr->paint(); // fill image with the color
    cr->restore(); // color svg_file back to black now

    cr->save();
    cr->set_source_rgba(1, 1, 1, 0.7);
    // draw a circle in the center of the image
    cr->arc(width/2.0, height/2.0, height/4.0, M_PI, 0);
    cr->stroke();

    // draw a diagonal line
    double line_width = cr->get_line_width();
    cr->move_to(0, height/2+line_width/2);
    cr->line_to(width, height/2+line_width/2);
    cr->stroke();
    cr->restore();

    cr->show_page();

    cout << "Wrote SVG file \"" << filename << "\"" << endl;
}

