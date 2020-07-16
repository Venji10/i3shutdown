## About i3shutdown
i3shutdown is a small shutdown menu for the i3 window manager. It currently provides three buttons for shutdown, reboot and logout.
The programming language used is C together with the GTK+ widget toolkit.

## Compilation
The program can be compiled easily using make:
```
$ git clone https://github.com/Venji10/i3shutdown
$ cd i3shutdown
$ make i3shutdown
```
The compiled binary will be named .i3shutdown

## Installation
To install i3shutdown just run:
```
$ sudo make install
```
This will install i3shutdown in /usr/bin/i3shutdown .
You will probably need to make it executable:
```
$ sudo chmod +x /usr/bin/i3shutdown   
```

