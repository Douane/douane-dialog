#include "dbus_client.h"

DBusClient::DBusClient(void)
: logger(log4cxx::Logger::getLogger("DBusClient")),
  dispatcher(DBus::BusDispatcher()),
  started(false)
{
  LOG4CXX_DEBUG(logger, "Initializing D-Bus client...");
  DBus::_init_threading();
  DBus::default_dispatcher = &this->dispatcher;
  DBus::Connection bus = DBus::Connection::SystemBus();

  this->douane = new Douane(bus, DOUANE_SERVER_PATH, DOUANE_SERVER_NAME);

  LOG4CXX_DEBUG(logger, "D-Bus client Initialized");
}

DBusClient::~DBusClient(void)
{
  LOG4CXX_DEBUG(logger, "Shutting down D-Bus client..");
  if (this->started)
    this->dispatcher.leave();
}

void DBusClient::execute(void)
{
  LOG4CXX_DEBUG(logger, "Starting D-Bus client...");
  this->started = true;
  this->dispatcher.enter();
}

void DBusClient::push_new_rule(const NetworkActivity * activity, bool allowed)
{
  this->douane->push_new_rule(activity, allowed);
}
