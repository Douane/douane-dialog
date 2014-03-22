#include "douane.h"

Douane::Douane(DBus::Connection &connection, const char *path, const char *name)
: DBus::ObjectProxy(connection, path, name),
  logger(log4cxx::Logger::getLogger("Douane"))
{
  LOG4CXX_DEBUG(logger, "Douane::Douane()");
}

Douane::~Douane()
{
  LOG4CXX_DEBUG(logger, "Douane::~Douane()");
}

void Douane::push_new_rule(const NetworkActivity * activity, bool allowed)
{
  LOG4CXX_DEBUG(logger, "Douane::push_new_rule()");
}

void Douane::NewActivityToBeValidated(const ::DBus::Struct< std::string, std::string, std::string, std::string >& activity)
{
  LOG4CXX_DEBUG(logger, "NewActivityToBeValidated signal emitted !");
  LOG4CXX_DEBUG(logger, "activity._1:executable_sha256: " << activity._1 << " | activity._2:printable_name: " << activity._2 << " | activity._3:executable_name: " << activity._3 << " | activity._4:icon_name: " << activity._4);
  const NetworkActivity * network_activity = new NetworkActivity(activity._1, activity._2, activity._3, activity._4);

  LOG4CXX_DEBUG(logger, "Firing signal new_activity_received...");
  this->new_activity_received(network_activity);
}

boost::signals2::connection Douane::on_new_activity_received_connect(const signalNewActivityReceivedType &slot)
{
  return Douane::new_activity_received.connect(slot);
}

Douane::signalNewActivityReceived Douane::new_activity_received;
