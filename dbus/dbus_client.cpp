#include "dbus_client.h"

DBusClient::DBusClient(DBus::Connection &connection, const char *path, const char *name)
: DBus::ObjectProxy(connection, path, name),
  logger(log4cxx::Logger::getLogger("DBusClient"))
{

}

DBusClient::~DBusClient()
{

}

void DBusClient::push_new_rule(const NetworkActivity * activity, bool allowed)
{

}

void DBusClient::start(void)
{

}

boost::signals2::connection DBusClient::on_new_activity_received_connect(const signalNewActivityReceivedType &slot)
{
  return DBusClient::new_activity_received.connect(slot);
}

DBusClient::signalNewActivityReceived DBusClient::new_activity_received;
