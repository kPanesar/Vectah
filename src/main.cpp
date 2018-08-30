#include "Vectah.h"
#include <iostream>
#include <gtkmm/application.h>

using namespace std;

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.kpanesar.vectah");
    Vectah mainWindow;

    return app->run(mainWindow, argc, argv);
}