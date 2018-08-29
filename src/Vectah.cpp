#include "Vectah.h"

#include <filesystem>

namespace fs = std::filesystem;

Vectah::Vectah()
{
    iconGrid = Gtk::Grid();
    iconGrid.set_row_spacing(75);
    iconGrid.set_column_spacing(75);
    iconGrid.set_border_width(75);

    int row = 0;
    int column = 0;
    for (auto & p : fs::recursive_directory_iterator(ICON_PATH))
    {
        if(column > 5) {
            row++;
            column = 0;
        }

        if(p.path().extension() != ".svg") continue;

        Icon* icon = new Icon(p.path().string());
        icons.push_back(icon);
        iconGrid.attach(*icon, column, row, 1, 1);

        column++;
    }

    add(iconGrid);
    show_all_children(true);
}

Vectah::~Vectah()
{
}