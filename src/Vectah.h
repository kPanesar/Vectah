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
#include <gdkmm/screen.h>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#define ICON_DIRECTORY "../assets/sample-icons"

class Vectah : public Gtk::Window {

public:
    Vectah();

    ~Vectah();

protected:
    // Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:

        ModelColumns() {
            add(colFilename);
            add(colDescription);
            add(colPixbuf);
        }

        Gtk::TreeModelColumn<std::string> colFilename;
        Gtk::TreeModelColumn<Glib::ustring> colDescription;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > colPixbuf;
    };

private:
    void LoadIcons(const std::string &directory);

    void AddEntry(const std::string &filePath, const std::string &description);

    void OnButtonQuit();

    void OnItemActivated(const Gtk::TreeModel::Path &path);

    void OnSelectionChanged();

    //Member widgets:
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::IconView iconView;
    Gtk::Button buttonQuit;
    Gtk::Entry entryIconPath;
    Gtk::Box vBox;
    Gtk::ButtonBox buttonBox;

    ModelColumns columns;
    Glib::RefPtr<Gtk::ListStore> listModel;
};

#endif //VECTAH_VECTAH_H
