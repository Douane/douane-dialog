#ifndef DBUS_CLIENT_H
#define DBUS_CLIENT_H

#include <boost/signals2.hpp>
#include <log4cxx/logger.h>
#include <dbus-c++/dbus.h>
#include "douane.h"
#include "../thread.h"
#include "../network_activity.h"

#define DOUANE_SERVER_PATH "/org/zedroot/Douane"
#define DOUANE_SERVER_NAME "org.zedroot.Douane"

/*
** D-Bus client in order to communicate with the Douane daemon.
*
*  This client is running in a thread as it is hooked to a signal
*  from the daemon when a new unknown activity has been caught.
*/
class DBusClient : public Thread
{
  public:
    /*
    ** Constructors and Destructor
    */
    DBusClient(void);
    virtual ~DBusClient(void);

    /*
    ** Instance methods
    */
    // Thread body
    void                execute(void);
    // Send to the daemon the user answer (Allow or deny activity)
    void                push_new_rule(const NetworkActivity * activity, bool allowed);

  private:
    log4cxx::LoggerPtr  logger;
    DBus::BusDispatcher dispatcher;
    Douane *            douane;
    bool                started;
};

#endif
