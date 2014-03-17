DAEMON_VERSION=$(shell cat VERSION)

CC=g++
PKGCONFIG=`pkg-config --cflags --libs liblog4cxx dbus-c++-1 gtkmm-3.0`
CFLAGS=-pedantic -Wall -W -g $(PKGCONFIG) -DDOUANE_VERSION=\"$(DAEMON_VERSION)\"
LDFLAGS=$(PKGCONFIG) -lboost_signals -lpthread

OBJ=dbus/dbus_client.o \
	gtk/gtk_application_icon_sublimer.o \
	gtk/gtk_box_unknown_application.o \
	gtk/gtk_process_icon.o \
	gtk/gtk_question_window.o \
	main.o \
	network_activity.o \
	tools.o

INSTALL=/usr/bin/install -c
BINDIR=$(DESTDIR)/opt/douane
PIDSDIR=$(DESTDIR)/opt/douane/pids
EXEC=douane-dialog

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(EXEC)

dbus:
	dbusxx-xml2cpp d-bus/org.zedroot.douane.xml --adaptor=org_zedroot_douane.h

install: $(EXEC)
	test -d $(BINDIR) || mkdir -p $(BINDIR)
	test -d $(DESTDIR)/etc/init.d/ || mkdir -p $(DESTDIR)/etc/init.d/
	test -d $(DESTDIR)/etc/dbus-1/system.d/ || mkdir -p $(DESTDIR)/etc/dbus-1/system.d/
	install -m 0500 $(EXEC) $(BINDIR)
	install -m 0755 init.d/douane $(DESTDIR)/etc/init.d/
	install -m 0644 system.d/douane.conf $(DESTDIR)/etc/dbus-1/system.d/
