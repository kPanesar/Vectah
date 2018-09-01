//
// Created by Karanvir Panesar on 4/3/18.
//

#ifndef VECTAH_VECTAH_H
#define VECTAH_VECTAH_H

#include <gtkmm/iconview.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/searchbar.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/stack.h>
#include <gtkmm/switch.h>
#include <gtkmm/label.h>
#include <gtkmm/separator.h>
#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <gtkmm/headerbar.h>
#include <gdkmm/screen.h>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <glibmm/binding.h>

#define ICON_DIRECTORY "../assets/sample-icons"

class Vectah: public Gtk::Window {

public:
    Vectah();
    ~Vectah();

protected:
    // Tree model columns:
    class ModelColumns: public Gtk::TreeModel::ColumnRecord {
    public:

        ModelColumns()
        {
            add(colFilename);
            add(colDescription);
            add(colPixbuf);
        }

        Gtk::TreeModelColumn<std::string> colFilename;
        Gtk::TreeModelColumn<Glib::ustring> colDescription;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > colPixbuf;
    };

private:

    // Slots
    void OnBackgroundColorSet();
    void OnItemActivated(const Gtk::TreeModel::Path& path);
    void OnSearchTextChanged();
    void OnSelectionChanged();
    void OnSearchbarRevealChanged();
    void OnSearchModeChanged();
    void onButtonOpenFolderClicked();
    void LoadIcons(const std::string& directory);
    void AddEntry(const std::string& filePath, const std::string& description);

    //Member widgets:
    Gtk::Box vBox;
    Gtk::Box boxSearch;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::IconView iconView;
    Gtk::Entry entryIconPath;
    Gtk::ColorButton colorButtonBackground;
    Gdk::RGBA colorBackground;
    Gtk::ToggleButton toggleButtonSearch;
    Gtk::SearchBar searchbar;
    Gtk::SearchEntry searchentry;
    Gtk::HeaderBar headerBar;
    Gtk::Button buttonOpenFolder;

    ModelColumns columns;
    Glib::RefPtr<Gtk::ListStore> listModel;
};

#endif //VECTAH_VECTAH_H
