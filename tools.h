#ifndef TOOLS_H
#define TOOLS_H

#include <sys/stat.h>       // mkdir()
#include <libgen.h>         // dirname()
#include <unistd.h>         // readlink()
#include <log4cxx/logger.h>

class Tools
{
  public:
    /*
    ** Constructors and Destructor
    */
    Tools(void);
    virtual ~Tools(void);

    /*
    ** Instance methods
    */
    const std::string   douane_root_path(void) const;
    const std::string   douane_data_path(void) const;

  private:
    log4cxx::LoggerPtr  logger;
};

#endif
