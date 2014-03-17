#ifndef DBUS_CLIENT_H
#define DBUS_CLIENT_H

#include <boost/signals2.hpp>
#include <log4cxx/logger.h>
#include <dbus-c++/dbus.h>
#include "interface/org_zedroot_douane_proxy.h"
#include "../network_activity.h"

class DBusClient : public org::zedroot::Douane_proxy,
                   public DBus::IntrospectableProxy,
                   public DBus::PropertiesProxy,
                   public DBus::ObjectProxy
{
  public:
    /*
    ** Signals
    */
    typedef boost::signals2::signal<void(const NetworkActivity*)> signalNewActivityReceived;
    typedef signalNewActivityReceived::slot_type                  signalNewActivityReceivedType;

    /*
    ** Constructors and Destructor
    */
    DBusClient(DBus::Connection &connection, const char *path, const char *name);
    virtual ~DBusClient(void);

    /*
    ** Instance methods
    */
    void                                  push_new_rule(const NetworkActivity * activity, bool allowed);
    void                                  start(void);
    // Signals methods
    static boost::signals2::connection    on_new_activity_received_connect(const signalNewActivityReceivedType &slot);

  private:
    log4cxx::LoggerPtr   logger;

    static signalNewActivityReceived      new_activity_received;
};

#endif
