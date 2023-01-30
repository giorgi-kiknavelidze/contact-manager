#include "ContactWindow.h"
ContactWindow::ContactWindow():	m_sidebar_left_container(Gtk::ORIENTATION_VERTICAL), m_sidebar_right_container(Gtk::ORIENTATION_VERTICAL),
	m_list_names(1), m_seperator(Gtk::ORIENTATION_VERTICAL), m_list_info(3),
	m_button_add_names("Add"), m_button_remove_names("Remove"),
	m_button_add_email("Add Email"), m_button_add_phone("Add Phone"), m_button_remove_info("Remove")
{
	set_title("Contact Manager");
	set_default_size(640, 480);
	add(m_main_container);

	m_list_names.set_activate_on_single_click();
	m_list_names.set_column_title(0, "Name");
	m_list_names_scroll.add(m_list_names);
	m_sidebar_left_container.pack_start(m_list_names_scroll);

	m_button_left_container.pack_start(m_button_add_names);
	m_button_left_container.pack_start(m_button_remove_names);
	m_sidebar_left_container.pack_start(m_button_left_container, Gtk::PACK_SHRINK);
	m_main_container.pack_start(m_sidebar_left_container);

	m_main_container.pack_start(m_seperator, Gtk::PACK_SHRINK, 5);

	m_list_info.set_column_title(0, "Entry");
	m_list_info.set_column_title(1, "Type");
	m_list_info.set_column_title(2, "Value");
	m_list_info_scroll.add(m_list_info);
	m_sidebar_right_container.pack_start(m_list_info_scroll);

	m_button_right_container.pack_start(m_button_add_email);
	m_button_right_container.pack_start(m_button_add_phone);
	m_button_right_container.pack_start(m_button_remove_info);
	m_sidebar_right_container.pack_start(m_button_right_container, Gtk::PACK_SHRINK);
	m_main_container.pack_start(m_sidebar_right_container);

	m_button_add_names.signal_clicked().connect(sigc::mem_fun(*this, &ContactWindow::on_button_add_names_clicked));
	m_button_remove_names.signal_clicked().connect(sigc::mem_fun(*this, &ContactWindow::on_button_remove_names_clicked));
	m_list_names.signal_cursor_changed().connect(sigc::mem_fun(*this, &ContactWindow::on_list_names_selection));

	m_button_add_email.signal_clicked().connect(sigc::mem_fun(*this, &ContactWindow::on_button_add_email_clicked));
	m_button_add_phone.signal_clicked().connect(sigc::mem_fun(*this, &ContactWindow::on_button_add_phone_clicked));
	m_button_remove_info.signal_clicked().connect(sigc::mem_fun(*this, &ContactWindow::on_button_remove_info_clicked));
	load_names(get_contacts());
	show_all_children();
}
ContactWindow::~ContactWindow()
{

}
void ContactWindow::load_names(const std::map<std::string, ContactData>& list)
{
	m_list_names.clear_items();
	for (const auto& i: list)
		m_list_names.append(decode_name(i.first));
}
void ContactWindow::on_button_add_names_clicked()
{
	EntryDialog dialog("Name:", {});
	int res = dialog.run();
	if (res == Gtk::RESPONSE_OK)
	{
		if (std::string(dialog.get_entry_text()).find(',') != std::string::npos)
		{
			Gtk::MessageDialog msg_dialog("An entry cannot contain a comma", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		std::map<std::string, ContactData> c = get_contacts();
		if (c.find(std::string(dialog.get_entry_text())) != c.end())
		{
			Gtk::MessageDialog msg_dialog("Name already in use", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		if (dialog.get_entry_text().size() == 0)
		{
			Gtk::MessageDialog msg_dialog("Name cannot be empty", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		append_or_edit_contact(encode_name(dialog.get_entry_text()), {});
	}
	load_names(get_contacts());
}
void ContactWindow::on_button_remove_names_clicked()
{
	const std::vector<int> selected = m_list_names.get_selected();
	if (selected.size() == 0)
	{
		Gtk::MessageDialog msg_dialog("None selected", false, Gtk::MESSAGE_ERROR);
		msg_dialog.run();
		return;
	}
	remove_contact(encode_name(m_list_names.get_text(selected[0])));
	load_names(get_contacts());
}
void ContactWindow::on_list_names_selection()
{
	std::vector<int> selected = m_list_names.get_selected();
	if (selected.size() == 0)
		set_info("");
	else
		set_info(encode_name(m_list_names.get_text(selected[0])));
}
void ContactWindow::set_info(const std::string& arg)
{
	m_list_info.clear_items();
	if (arg == "")
		return;
	const ContactData data = get_contacts().at(arg);
	std::vector<std::pair<std::string, std::string>> emails = get_emails(data);
	for (const auto& i: emails)
	{
		m_list_info.append("Email");
		m_list_info.set_text(m_list_info.size() - 1, 1, i.first);
		m_list_info.set_text(m_list_info.size() - 1, 2, i.second);
	}
	std::vector<std::pair<std::string, std::string>> phones = get_phones(data);
	for (const auto& i: phones)
	{
		m_list_info.append("Phone");
		m_list_info.set_text(m_list_info.size() - 1, 1, i.first);
		m_list_info.set_text(m_list_info.size() - 1, 2, i.second);
	}
}
void ContactWindow::on_button_add_email_clicked()
{
	EntryDialog dialog("Email", {"Home", "Work"});
	int res = dialog.run();
	if (res == Gtk::RESPONSE_OK)
	{
		if (std::string(dialog.get_entry_text()).find(',') != std::string::npos)
		{
			Gtk::MessageDialog msg_dialog("An entry cannot contain a comma", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		std::vector<int> selected = m_list_names.get_selected();
		if (selected.size() == 0)
		{
			Gtk::MessageDialog msg_dialog("No name selected", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		std::string name = m_list_names.get_text(selected[0]);
		const std::map<std::string, ContactData> c = get_contacts();
		ContactData data = c.at(encode_name(name));
		std::vector<std::pair<std::string, std::string>> v = get_emails(data);
		v.push_back(std::pair<std::string, std::string>(dialog.get_combobox_text().size() ? dialog.get_combobox_text() : "None", dialog.get_entry_text()));
		data.emails = contact_entry_from_vector(v);
		append_or_edit_contact(encode_name(name), data);
		set_info(encode_name(name));
	}
}
void ContactWindow::on_button_add_phone_clicked()
{
	EntryDialog dialog("Phone", {"Home", "Work"});
	int res = dialog.run();
	if (res == Gtk::RESPONSE_OK)
	{
		if (std::string(dialog.get_entry_text()).find(',') != std::string::npos)
		{
			Gtk::MessageDialog msg_dialog("An entry cannot contain a comma", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		std::vector<int> selected = m_list_names.get_selected();
		if (selected.size() == 0)
		{
			Gtk::MessageDialog msg_dialog("No name selected", false, Gtk::MESSAGE_ERROR);
			msg_dialog.run();
			return;
		}
		std::string name = m_list_names.get_text(selected[0]);
		const std::map<std::string, ContactData> c = get_contacts();
		ContactData data = c.at(encode_name(name));
		std::vector<std::pair<std::string, std::string>> v = get_phones(data);
		v.push_back(std::pair<std::string, std::string>(dialog.get_combobox_text().size() ? dialog.get_combobox_text() : "None", dialog.get_entry_text()));
		data.phones = contact_entry_from_vector(v);
		append_or_edit_contact(encode_name(name), data);
		set_info(encode_name(name));
	}
}
void ContactWindow::on_button_remove_info_clicked()
{
	const std::vector<int> selected = m_list_info.get_selected();
	if (selected.size() == 0)
	{
		Gtk::MessageDialog msg_dialog("None selected", false, Gtk::MESSAGE_ERROR);
		msg_dialog.run();
		return;
	}
	std::string name = m_list_names.get_text(m_list_names.get_selected()[0]);
	std::string email_phone = m_list_info.get_text(selected[0]);
	if (email_phone == "Email")
	{
		ContactData data = get_contacts().at(encode_name(name));
		std::pair<std::string, std::string> p(m_list_info.get_text(selected[0], 1), m_list_info.get_text(selected[0], 2));
		std::vector<std::pair<std::string, std::string>> v = get_emails(data);
		for (size_t i = 0; i < v.size(); i++)
		{
			if (v[i] == p)
			{
				v.erase(v.begin() + i);
				break;
			}
		}
		data.emails = contact_entry_from_vector(v);
		append_or_edit_contact(encode_name(name), data);
		set_info(encode_name(name));
	}
	if (email_phone == "Phone")
	{
		ContactData data = get_contacts().at(encode_name(name));
		std::pair<std::string, std::string> p(m_list_info.get_text(selected[0], 1), m_list_info.get_text(selected[0], 2));
		std::vector<std::pair<std::string, std::string>> v = get_phones(data);
		for (size_t i = 0; i < v.size(); i++)
		{
			if (v[i] == p)
			{
				v.erase(v.begin() + i);
				break;
			}
		}
		data.phones = contact_entry_from_vector(v);
		append_or_edit_contact(encode_name(name), data);
		set_info(encode_name(name));
	}
}
