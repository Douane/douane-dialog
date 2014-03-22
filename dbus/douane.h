#ifndef DOUANE_H
#define DOUANE_H

#include <boost/signals2.hpp>
#include <log4cxx/logger.h>
#include <dbus-c++/dbus.h>
#include "interface/org_zedroot_douane_proxy.h"
#include "../network_activity.h"

/*
** D-Bus interface to the Douane daemon.
*
*  This interface allows this process to be notified
*  in case new unknown network activities have been
*  detected by the Douane firewall.
*
*/
class Douane : public org::zedroot::Douane_proxy,
               public DBus::IntrospectableProxy,
               public DBus::PropertiesProxy,
               public DBus::ObjectProxy
{
  public:
    /*
    ** Internal signals
    */
    typedef boost::signals2::signal<void(const NetworkActivity*)> signalNewActivityReceived;
    typedef signalNewActivityReceived::slot_type                  signalNewActivityReceivedType;

    /*
    ** Constructors and Destructor
    */
    Douane(DBus::Connection &connection, const char *path, const char *name);
    virtual ~Douane(void);

    /*
    ** Instance methods
    */
    void                                  push_new_rule(const NetworkActivity * activity, bool allowed);
    /*
    ** Internal signals methods
    */
    static boost::signals2::connection    on_new_activity_received_connect(const signalNewActivityReceivedType &slot);

    /*
    ** D-Bus signal
    */
    void                                  NewActivityToBeValidated(const ::DBus::Struct< std::string, std::string, std::string, std::string >& activity);

  private:
    log4cxx::LoggerPtr                    logger;

    static signalNewActivityReceived      new_activity_received;
};

#endif
