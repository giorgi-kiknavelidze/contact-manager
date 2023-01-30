#include "ContactData.h"
std::string get_save_dirname()
{
	return Glib::path_get_dirname(get_save_filename());
}
std::string get_save_filename()
{
	return Glib::build_filename(Glib::get_user_data_dir(), "contact-manager", "contacts.dat");
}
void create_data_dir()
{
	std::filesystem::path dir(get_save_dirname());
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);
}
std::string encode_name(std::string arg)
{
	std::replace(arg.begin(), arg.end(), ' ', ',');
	return arg;
}
std::string decode_name(std::string arg)
{
	std::replace(arg.begin(), arg.end(), ',', ' ');
	return arg;
}
std::map<std::string, ContactData> get_contacts()
{
	std::map<std::string, ContactData> ret;
	std::ifstream input_stream(get_save_filename());
	std::string s;
	while (getline(input_stream, s))
	{
		std::istringstream is(s);
		std::string name, emails, phones;
		is >> name >> emails >> phones;
		ret[name] = {emails, phones};
	}
	return ret;
}
std::map<std::string, ContactData> append_or_edit_contact(const std::string& name, const ContactData& new_val)
{
	std::map<std::string, ContactData> ret = get_contacts();
	ret[name] = new_val;
	create_data_dir();
	std::ofstream output_stream(get_save_filename());
	for (const auto& i: ret)
	{
		output_stream << i.first << ' ' << i.second.emails << ' ' << i.second.phones << '\n';
	}
	return ret;
}
std::map<std::string, ContactData> remove_contact(const std::string& name)
{
	create_data_dir();
	std::map<std::string, ContactData> ret = get_contacts();
	if (ret.find(name) != ret.end())
	{
		ret.erase(ret.find(name));
	}
	std::ofstream output_stream(get_save_filename());
	for (const auto& i: ret)
	{
		output_stream << i.first << ' ' << i.second.emails << ' ' << i.second.phones << '\n';
	}
	return ret;
}
std::vector<std::pair<std::string, std::string>> get_emails(ContactData arg)
{
	std::replace(arg.emails.begin(), arg.emails.end(), ',', ' ');
	std::vector<std::pair<std::string, std::string>> ret; // type, value
	std::istringstream is(arg.emails);
	std::pair<std::string, std::string> temp;
	while (is >> temp.first >> temp.second)
	{
		ret.push_back(temp);
	}
	return ret;
}
std::vector<std::pair<std::string, std::string>> get_phones(ContactData arg)
{
	std::replace(arg.phones.begin(), arg.phones.end(), ',', ' ');
	std::vector<std::pair<std::string, std::string>> ret; // type, value
	std::istringstream is(arg.phones);
	std::pair<std::string, std::string> temp;
	while (is >> temp.first >> temp.second)
	{
		ret.push_back(temp);
	}
	return ret;
}
std::string contact_entry_from_vector(const std::vector<std::pair<std::string, std::string>>& arg)
{
	if (arg.size() == 0)
		return ",";
	std::string ret;
	for (const auto& i: arg)
		ret += i.first + "," + i.second + ",";
	ret.erase(ret.size() - 1);
	return ret;
}
