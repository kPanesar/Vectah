#include "Vectah.h"

#include <filesystem>
#include <gtkmm/colorchooserdialog.h>
#include <giomm.h>
#include <iostream>

namespace fs = std::filesystem;

Vectah::Vectah() :
        vBox(Gtk::Orientation::ORIENTATION_VERTICAL, 25),
        entryIconPath() {
    auto screen = get_screen();
    set_default_size(screen->get_width()*0.60f, screen->get_height()*0.60f);

    scrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);

    vBox.set_border_width(5);

    listModel = Gtk::ListStore::create(columns);
    listModel->set_sort_column(columns.colDescription, Gtk::SortType::SORT_ASCENDING);

    iconView.set_model(listModel);
    iconView.set_markup_column(columns.colDescription);
    iconView.set_pixbuf_column(columns.colPixbuf);
    iconView.set_selection_mode(Gtk::SelectionMode::SELECTION_MULTIPLE);
    iconView.signal_item_activated().connect(sigc::mem_fun(*this, &Vectah::OnItemActivated));
    iconView.signal_selection_changed().connect(sigc::mem_fun(*this, &Vectah::OnSelectionChanged));

    scrolledWindow.add(iconView);
    vBox.pack_start(colorButtonBackground, Gtk::PackOptions::PACK_SHRINK);
    vBox.pack_start(scrolledWindow, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    add(vBox);

    //Set start color:
    colorBackground.set_rgba(1,1,1,1.0);
    colorButtonBackground.set_rgba(colorBackground);
    colorButtonBackground.signal_color_set().connect(sigc::mem_fun(*this, &Vectah::OnBackgroundColorSet));
    OnBackgroundColorSet();

    LoadIcons(ICON_DIRECTORY);

    show_all_children();
}

Vectah::~Vectah() {
}

void Vectah::OnBackgroundColorSet() {
    colorBackground = colorButtonBackground.get_rgba();
//    override_background_color(colorBackground);
//    vBox.override_background_color(colorBackground);
//    scrolledWindow.override_background_color(colorBackground);
    iconView.override_background_color(colorBackground);
}

void Vectah::LoadIcons(const std::string &directory) {
    if (directory.empty())
        return;

    for (auto &p : fs::recursive_directory_iterator(directory)) {
        if (p.is_directory() || !(p.path().extension() == ".svg" || p.path().extension() == ".png")) continue;
        AddEntry(p.path().string(), p.path().filename().string());
    }
}

void Vectah::AddEntry(const std::string &filePath, const std::string &description) {
    auto row = *(listModel->append());
    row[columns.colFilename] = filePath;
    row[columns.colDescription] = description;

    try {
        row[columns.colPixbuf] = Gdk::Pixbuf::create_from_file(filePath);
    }
    catch (const Gdk::PixbufError &ex) {
        std::cerr << "Gdk::PixbufError: " << ex.what() << std::endl;
    }
    catch (const Glib::FileError &ex) {
        std::cerr << "Glib::FileError: " << ex.what() << std::endl;
    }
    catch (const Glib::Error &ex) {
        std::cerr << "Glib::Error: " << ex.what() << std::endl;
    }
}


void Vectah::OnItemActivated(const Gtk::TreeModel::Path &path) {
    auto iter = listModel->get_iter(path);
    auto row = *iter;

    const std::string filename = row[columns.colFilename];
    const Glib::ustring description = row[columns.colDescription];

    std::cout << "Item activated: filename="
              << filename
              << ", description="
              << description
              << std::endl;
}

void Vectah::OnSelectionChanged() {
    std::vector<Gtk::TreeModel::Path> selected = iconView.get_selected_items();
    if (!selected.empty()) {
        const Gtk::TreeModel::Path &path = *selected.begin();
        auto iter = listModel->get_iter(path);
        auto row = *iter;

        const std::string filename = row[columns.colFilename];
        const Glib::ustring description = row[columns.colDescription];

        std::cout << "Selection Changed to: filename="
                  << filename
                  << ", description="
                  << description
                  << std::endl;
    }
}

