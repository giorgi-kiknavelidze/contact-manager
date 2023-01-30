#ifndef CONTACT_WINDOW_H
#define CONTACT_WINDOW_H 1
#include "ContactData.h"
#include "EntryDialog.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/viewport.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/separator.h>
class ContactWindow: public Gtk::Window
{
public:
	ContactWindow();
	virtual ~ContactWindow();
protected:
	void load_names(const std::map<std::string, ContactData>& list);
	void on_button_add_names_clicked();
	void on_button_remove_names_clicked();
	void on_list_names_selection();
	void on_button_add_email_clicked();
	void on_button_add_phone_clicked();
	void on_button_remove_info_clicked();
	void set_info(const std::string& arg);
	Gtk::Box m_main_container;
	Gtk::Box m_sidebar_left_container;
	Gtk::Box m_sidebar_right_container;

	Gtk::ButtonBox m_button_left_container;
	Gtk::ButtonBox m_button_right_container;

	Gtk::ListViewText m_list_names;
	Gtk::ScrolledWindow m_list_names_scroll;

	Gtk::Separator m_seperator;
	Gtk::ListViewText m_list_info;
	Gtk::ScrolledWindow m_list_info_scroll;

	Gtk::Button m_button_add_names;
	Gtk::Button m_button_remove_names;

	Gtk::Button m_button_add_email;
	Gtk::Button m_button_add_phone;
	Gtk::Button m_button_remove_info;
};
#endif
