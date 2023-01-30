#ifndef ENTRY_DIALOG_H
#define ENTRY_DIALOG_H 1
#include <gtkmm/comboboxtext.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <glibmm/ustring.h>
#include <vector>

class EntryDialog: public Gtk::Dialog
{
public:
	EntryDialog(Glib::ustring label_text, std::vector<Glib::ustring> combo_box_texts);
	virtual ~EntryDialog();
	Glib::ustring get_entry_text();
	Glib::ustring get_combobox_text();
protected:
	Gtk::Label m_label;
	Gtk::Entry m_entry;
	Gtk::ComboBoxText m_combobox_text;
	Gtk::Grid m_grid;
};
#endif
