project('contact-manager', 'cpp', version : '0.1', default_options : ['warning_level=3', 'cpp_std=c++17'])
gtkmm_dep = dependency('gtkmm-3.0')
cpp = meson.get_compiler('cpp')
src = ['main.cpp', 'EntryDialog.cpp', 'ContactWindow.cpp', 'ContactData.cpp']
executable('contact-manager', src, dependencies : [gtkmm_dep], install : true)
