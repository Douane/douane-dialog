DAEMON_VERSION=$(shell cat VERSION)

CC=g++
PKGCONFIG=`pkg-config --cflags --libs liblog4cxx dbus-c++-1 gtkmm-3.0`
CFLAGS=-pedantic -Wall -W -g $(PKGCONFIG) -DDOUANE_VERSION=\"$(DAEMON_VERSION)\"
LDFLAGS=$(PKGCONFIG) -lboost_signals -lpthread

OBJ=dbus/dbus_client.o \
	dbus/douane.o \
	gtk/gtk_application_icon_sublimer.o \
	gtk/gtk_box_unknown_application.o \
	gtk/gtk_process_icon.o \
	gtk/gtk_question_window.o \
	main.o \
	network_activity.o \
	thread.o \
	tools.o

INSTALL=/usr/bin/install -c
BINDIR=$(DESTDIR)/usr/local/bin
PIDSDIR=$(DESTDIR)/opt/douane/pids
EXEC=douane-dialog

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(EXEC)

install: $(EXEC)
	test -d $(BINDIR) || mkdir -p $(BINDIR)
	test -d $(DESTDIR)/usr/share/dbus-1/services/ || mkdir -p $(DESTDIR)/usr/share/dbus-1/services/
	install -m 0500 $(EXEC) $(BINDIR)
	install -m 0644 services/org.zedroot.DouaneDialog.service $(DESTDIR)/usr/share/dbus-1/services/
