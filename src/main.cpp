#include "Vectah.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    Vectah window;
    return app->run(window);
}