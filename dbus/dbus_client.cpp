#include "dbus_client.h"

Douane::DBusClient::DBusClient(DBus::Connection &connection, const char *path, const char *name)
: logger(log4cxx::Logger::getLogger("Douane::DBusClient")),
 DBus::ObjectProxy(connection, path, name)
{

}

Douane::DBusClient::~DBusClient()
{

}
