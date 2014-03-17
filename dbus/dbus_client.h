#ifndef DOUANE_DBUS_CLIENT_H
#define DOUANE_DBUS_CLIENT_H

#include <log4cxx/logger.h>
#include <dbus-c++/dbus.h>

namespace Douane
{
  class DBusClient : public org::zedroot::Douane_proxy,
                     public DBus::IntrospectableProxy,
                     public DBus::PropertiesProxy,
                     public DBus::ObjectProxy
  {
    public:
      /*
      ** Constructors and Destructor
      */
      DBusClient(DBus::Connection &connection, const char *path, const char *name);
      virtual ~DBusClient(void);

      /*
      ** Instance methods
      */

  private:
    log4cxx::LoggerPtr   logger;
  };
}

#endif
