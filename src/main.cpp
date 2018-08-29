#include "Vectah.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

using namespace std;

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv);

    static Gtk::Window window;
    window.set_title("Vectah - Icon Manager");
    window.set_size_request(400, 600);
    window.set_resizable(false);

    Vectah scrollWindow;
    scrollWindow.set_policy(Gtk::PolicyType::POLICY_NEVER, Gtk::PolicyType::POLICY_AUTOMATIC);

    window.add(scrollWindow);
    scrollWindow.show();

    return app->run(window);
}