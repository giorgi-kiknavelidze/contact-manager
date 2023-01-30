#ifndef CONTACT_DATA_H
#define CONTACT_DATA_H 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <utility>
#include <glibmm/miscutils.h>
struct ContactData
{
	std::string emails = ",";
	std::string phones = ",";
};
std::string get_save_filename();
std::string get_save_dirname();
void create_data_dir();
std::string encode_name(std::string arg);
std::string decode_name(std::string arg);
std::map<std::string, ContactData> get_contacts();
size_t get_contact_by_name(const std::string& name, std::vector<ContactData> data);
std::map<std::string, ContactData> append_or_edit_contact(const std::string& name, const ContactData& new_val);
std::map<std::string, ContactData> remove_contact(const std::string& name);
std::vector<std::pair<std::string, std::string>> get_emails(ContactData arg);
std::vector<std::pair<std::string, std::string>> get_phones(ContactData arg);
std::string contact_entry_from_vector(const std::vector<std::pair<std::string, std::string>>& arg);
#endif
