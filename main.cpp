#include "ContactWindow.h"
int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "com.github.giorgi-kiknavelidze.contact-manager");
	ContactWindow main_window;
	return app->run(main_window);
}
