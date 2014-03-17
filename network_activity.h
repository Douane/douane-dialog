#ifndef NETWORK_ACTIVITY_H
#define NETWORK_ACTIVITY_H

#include <log4cxx/logger.h>
#include "gtk/gtk_process_icon.h"

class NetworkActivity
{
  public:
    /*
    ** Constructors and Destructor
    */
    NetworkActivity(const std::string &executable_sha256, const std::string &printable_name, const std::string &executable_name, const std::string &icon_name);
    virtual ~NetworkActivity(void);

    /*
    ** Instance methods
    */

    /*
    ** Attributes
    */
    const std::string     executable_sha256;
    const std::string     printable_name;
    const std::string     executable_name;
    const std::string     icon_name;
    GtkProcessIcon        icon;

  private:
    log4cxx::LoggerPtr    logger;
};

#endif
