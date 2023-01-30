# Contact Manager

A GUI application written in C++.

Dependencies:

C++17 compiler with filesystem support

gtkmm 3 .24

To build and launch the application

```bash
meson ./builddir --prefix=/path/to/installdir
ninja -C ./builddir
ninja -C ./builddir install # may require sudo
/path/to/installdir/bin/contact-manager

```
