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

  // In the case we have an ID
  if (this->process_id.empty() == false)
  {
    LOG4CXX_DEBUG(logger, "Unregistering ID " << this->process_id << "...");
    // Unregister from the daemon
    this->douane->UnregisterDialogProcess(this->process_id);
  }

  LOG4CXX_DEBUG(logger, "Shutting down D-Bus server..");
  if (this->started)
    this->dispatcher.leave();
}

bool DBusClient::register_to_daemon(void)
{
  LOG4CXX_DEBUG(logger, "Registering to the daemon as dialog process...");

  this->process_id = this->douane->RegisterAsDialogProcess();
  if (this->process_id.empty())
  {
    LOG4CXX_ERROR(logger, "Failed to register.");
    return false;
  } else {
    LOG4CXX_DEBUG(logger, "Successfully registered with ID " << this->process_id << ".");
    return true;
  }
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
