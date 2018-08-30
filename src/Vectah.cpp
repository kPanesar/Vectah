#include "Vectah.h"

#include <filesystem>
#include <giomm.h>
#include <iostream>

namespace fs = std::filesystem;

Vectah::Vectah() :
        vBox(Gtk::Orientation::ORIENTATION_VERTICAL),
        buttonQuit("Quit"),
        entryIconPath() {
    auto screen = get_screen();
    set_default_size(screen->get_width()*0.60f, screen->get_height()*0.60f);

    scrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);

    buttonBox.pack_start(buttonQuit, Gtk::PackOptions::PACK_SHRINK);
    buttonBox.set_border_width(6);
    buttonBox.set_layout(Gtk::ButtonBoxStyle::BUTTONBOX_END);

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
    vBox.pack_start(scrolledWindow, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    vBox.pack_start(buttonBox, Gtk::PackOptions::PACK_SHRINK);
    add(vBox);

    show_all_children();

    buttonQuit.signal_clicked().connect(sigc::mem_fun(*this, &Vectah::OnButtonQuit));

    LoadIcons(ICON_DIRECTORY);
}

Vectah::~Vectah() {
}

void Vectah::OnButtonQuit() {
    hide();
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

