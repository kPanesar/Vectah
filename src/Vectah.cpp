#include "Vectah.h"

Vectah::Vectah()
        :
        vBox(Gtk::Orientation::ORIENTATION_VERTICAL, 25),
        entryIconPath(),
        boxSearch(Gtk::Orientation::ORIENTATION_VERTICAL),
        toggleButtonSearch()
{
    set_title("Vectah");
    set_default_size(950, 700);

    searchbar.set_show_close_button();
    searchbar.connect_entry(searchEntry);

    searchbar.property_search_mode_enabled().signal_changed().connect(
            sigc::mem_fun(*this, &Vectah::OnSearchbarRevealChanged));

    toggleButtonSearch.set_image_from_icon_name("system-search-symbolic");
    toggleButtonSearch.set_active(false);
    toggleButtonSearch.property_active().signal_changed().connect(sigc::mem_fun(*this, &Vectah::OnSearchModeChanged));

    // Searchbar Layout
    boxSearch.pack_start(searchEntry, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    boxSearch.set_spacing(6);
    searchbar.add(boxSearch);

    // Connect signal handlers.
    searchEntry.signal_search_changed().connect(sigc::mem_fun(*this, &Vectah::OnSearchTextChanged));

    buttonOpenFolder.set_image_from_icon_name("folder-open-symbolic");
    buttonOpenFolder.set_tooltip_text("Open");
    buttonOpenFolder.signal_clicked().connect(sigc::mem_fun(*this, &Vectah::OnButtonOpenFolderClicked));

    buttonCopyIcon.set_image_from_icon_name("edit-copy-symbolic");
    buttonCopyIcon.set_tooltip_text("Copy");
    buttonCopyIcon.signal_clicked().connect(sigc::mem_fun(*this, &Vectah::OnButtonCopyIconPressed));

    //Set start color:
    colorBackground.set_rgba(1, 1, 1, 1.0);
    colorButtonBackground.set_tooltip_text("Change background color");
    colorButtonBackground.set_rgba(colorBackground);
    colorButtonBackground.signal_color_set().connect(sigc::mem_fun(*this, &Vectah::OnBackgroundColorSet));

    headerBar.set_title(get_title());
    headerBar.set_show_close_button();
    headerBar.pack_start(buttonOpenFolder);
    headerBar.pack_start(buttonCopyIcon);
    //headerBar.pack_start(toggleButtonSearch);
    headerBar.pack_start(colorButtonBackground);
    toggleButtonSearch.set_halign(Gtk::ALIGN_END);
    colorButtonBackground.set_halign(Gtk::ALIGN_END);
    set_titlebar(headerBar);

    scrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);

    vBox.set_margin_top(12);
    vBox.set_margin_bottom(12);
    vBox.set_margin_left(12);
    vBox.set_margin_right(12);

    listModel = Gtk::ListStore::create(columns);
    listModel->set_sort_column(columns.colDescription, Gtk::SortType::SORT_ASCENDING);

    iconView.set_model(listModel);
    iconView.set_markup_column(columns.colDescription);
    iconView.set_pixbuf_column(columns.colPixbuf);
    iconView.set_selection_mode(Gtk::SelectionMode::SELECTION_MULTIPLE);
    iconView.signal_item_activated().connect(sigc::mem_fun(*this, &Vectah::OnItemActivated));
    iconView.signal_selection_changed().connect(sigc::mem_fun(*this, &Vectah::OnSelectionChanged));

    scrolledWindow.add(iconView);
    //vBox.pack_start(searchbar, Gtk::PackOptions::PACK_SHRINK);
    vBox.pack_start(scrolledWindow, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    add(vBox);

    OnBackgroundColorSet();

    LoadIcons(fs::path(ICON_DIRECTORY));

    show_all_children();
}

void Vectah::OnBackgroundColorSet()
{
    colorBackground = colorButtonBackground.get_rgba();
    override_background_color(colorBackground);
    vBox.override_background_color(colorBackground);
    iconView.override_background_color(colorBackground);
}

void Vectah::OnButtonOpenFolderClicked()
{
    Gtk::FileChooserDialog dialog("Please choose a folder",
            Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::ResponseType::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch (result) {
    case Gtk::ResponseType::RESPONSE_OK: {
        LoadIcons(dialog.get_filename());
        break;
    }
    case Gtk::ResponseType::RESPONSE_CANCEL: {
        break;
    }
    default: {
        break;
    }
    }
}

void Vectah::OnButtonCopyIconPressed() {
    auto clipboard = Gtk::Clipboard::get();

    std::vector<Gtk::TreeModel::Path> selected = iconView.get_selected_items();
    if (!selected.empty()) {
        const Gtk::TreeModel::Path& path = *selected.begin();
        auto iter = listModel->get_iter(path);
        auto row = *iter;

        const Glib::ustring description = row[columns.colDescription];

//        clipboard->set_text(description);
        clipboard->set_image(row[columns.colPixbuf]);
    }
}

void Vectah::OnSearchTextChanged()
{

}

void Vectah::OnSearchbarRevealChanged()
{
    const bool revealed = searchbar.get_search_mode();
    toggleButtonSearch.set_active(revealed);
}

void Vectah::OnSearchModeChanged()
{
    const bool search_mode = toggleButtonSearch.get_active();
    searchbar.set_search_mode(search_mode);
}

void Vectah::LoadIcons(const fs::path& directory)
{
    if (directory.empty())
        return;

    listModel->clear();

    for (auto& p : fs::recursive_directory_iterator(directory)) {
        if (p.is_directory() || !(p.path().extension()==fs::path(".svg") || p.path().extension()==fs::path(".png"))) {
            continue;
        }
        AddEntry(p.path().string(), p.path().filename().string());
    }
}

void Vectah::AddEntry(const std::string& filePath, const std::string& description)
{
    auto row = *(listModel->append());
    row[columns.colFilename] = filePath;
    row[columns.colDescription] = description;

    try {
        Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file(filePath, 60, 60);
        row[columns.colPixbuf] = image;
    }
    catch (const Gdk::PixbufError& ex) {
        std::cerr << "Gdk::PixbufError: " << ex.what() << std::endl;
    }
    catch (const Glib::FileError& ex) {
        std::cerr << "Glib::FileError: " << ex.what() << std::endl;
    }
    catch (const Glib::Error& ex) {
        std::cerr << "Glib::Error: " << ex.what() << std::endl;
    }
}

void Vectah::OnItemActivated(const Gtk::TreeModel::Path& path)
{
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

void Vectah::OnSelectionChanged()
{
    std::vector<Gtk::TreeModel::Path> selected = iconView.get_selected_items();
    if (!selected.empty()) {
        const Gtk::TreeModel::Path& path = *selected.begin();
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

