#include "EntryDialog.h"
EntryDialog::EntryDialog(Glib::ustring label_text, std::vector<Glib::ustring> combo_box_texts): Gtk::Dialog(), m_label(label_text), m_combobox_text(true)
{
	set_title("Add an Entry");
	for (const auto& i: combo_box_texts)
		m_combobox_text.append(i);
	get_vbox()->pack_start(m_grid);
	m_grid.attach(m_label, 0, 0, 1, 1);
	m_grid.attach(m_entry, 1, 0, 2, 1);
	if (combo_box_texts.size())
		m_grid.attach(m_combobox_text, 3, 0, 1, 1);
	m_grid.set_column_spacing(5);
	m_combobox_text.get_entry()->set_width_chars(8);
	m_entry.set_hexpand();
	add_button("Add", Gtk::RESPONSE_OK);
	add_button("Close", Gtk::RESPONSE_CLOSE);
	//This is Deprecated
	get_action_area()->set_layout(Gtk::BUTTONBOX_CENTER);
	show_all_children();
}
EntryDialog::~EntryDialog()
{

}
Glib::ustring EntryDialog::get_entry_text()
{
	return m_entry.get_text();
}
Glib::ustring EntryDialog::get_combobox_text()
{
	return m_combobox_text.get_entry_text();
}
