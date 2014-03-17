// Basic includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <boost/bind.hpp>
#include <signal.h>

// Internal includes
#include "dbus/dbus_client.h"
// Log4cxx includes
#include <log4cxx/logger.h>
#include <log4cxx/helpers/pool.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/patternlayout.h>

// In the case the Makefile didn't initialized the VERSION variable
// this code initialize it to "UNKNOWN"
#ifndef DOUANE_DIALOG_VERSION
#define DOUANE_DIALOG_VERSION "UNKNOWN"
#endif

// Daemon flags and paths
bool          enabled_debug = false;
bool          has_to_daemonize = false;
const char *  log_file_path = "/var/log/douane.log";

// Initialize the logger for the current file
log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("Main");

/*
** Handle the exit signal
*/
void handler(int sig)
{
  LOG4CXX_INFO(logger, "Exiting Douane dialog with signal " << sig << "...");
  exit(sig);
}

/*
** Print the daemon version
*
*  This is executed when passing argument -v
*/
void do_version(void)
{
  std::cout << DOUANE_DIALOG_VERSION << std::endl;
  exit(1);
}

/*
** Print the help menu
*
*  This is executed when passing argument -h
*/
void do_help(void)
{
  std::cout << "TODO: Write help message" << std::endl;
  exit(1);
}

void do_from_options(std::string option, const char * optarg)
{
  if (option == "version")
  {
    do_version();
  }
  else if (option == "help")
  {
    do_help();
  } else if (option == "log-file")
  {
    if (optarg)
      log_file_path = optarg;
  } else if (option == "debug")
  {
    enabled_debug = true;
  }
}

int main(int argc, char * argv[])
{
  // CTRL + C catcher
  signal(SIGINT, handler);

  // Force the nice value to -20 (urgent)
  nice(-20);

  /*
  **  Application options handling with long options support.
  */
  int c;
  const struct option long_options[] =
  {
    {"version",  no_argument,       0, 'v'},
    {"help",     no_argument,       0, 'h'},
    {"log-file", required_argument, 0, 'l'},
    {"debug",    no_argument      , 0, 'D'},
    {0,0,0,0}
  };
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "vhl:D", long_options, &option_index)) != -1)
  {
    switch (c)
    {
      case 0:
        do_from_options(long_options[option_index].name, optarg);
        break;
      case 'v':
        do_from_options("version", optarg);
        break;
      case 'h':
        do_from_options("help", optarg);
        break;
      case 'l':
        do_from_options("log-file", optarg);
        break;
      case 'D':
        do_from_options("debug", optarg);
        break;
      case '?':
        std::cout << std::endl << "To get help execute me with --help" << std::endl;
        exit(1);
        break;
      default:
        printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  /*
  **  log4cxx configuration
  *
  *  Appending logs to the file /var/log/douane.log
  */
  log4cxx::PatternLayoutPtr pattern = new log4cxx::PatternLayout(
    enabled_debug ? "%d{dd/MM/yyyy HH:mm:ss} | %5p | [%F::%c:%L]: %m%n" : "%d{dd/MM/yyyy HH:mm:ss} %5p: %m%n"
  );
  log4cxx::FileAppender * fileAppender = new log4cxx::FileAppender(
    log4cxx::LayoutPtr(pattern),
    log_file_path
  );
  log4cxx::helpers::Pool pool;
  fileAppender->activateOptions(pool);
  log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(fileAppender));
  log4cxx::Logger::getRootLogger()->setLevel(enabled_debug ? log4cxx::Level::getDebug() : log4cxx::Level::getInfo());
  /*
  **
  */

  try {
    LOG4CXX_INFO(logger, "The log file is " << log_file_path);

    if (enabled_debug)
      LOG4CXX_DEBUG(logger, "The debug mode is enabled");

    /*
    ** ~~~~ Global class initializations ~~~~
    */
    LOG4CXX_DEBUG(logger, "Initializing Douane::DBusClient");
    Douane::DBusClient   dbus_client;
    /*
    **/

    /*
    ** ~~~~ Signal connexions ~~~~
    */
    // TODO: Connect a signal when something has been retreived from D-Bus client
    //       to popup the GTK dialog.
    /*
    **/

    /*
    ** ~~~~ Dialog starting ~~~~
    */

    LOG4CXX_DEBUG(logger, "Dialog is dying...");
    return EXIT_SUCCESS;

  } catch(const std::exception &e)
  {
    LOG4CXX_ERROR(logger, e.what());
  } catch (const std::string &e)
  {
    LOG4CXX_ERROR(logger, e);
  } catch(...)
  {
    LOG4CXX_ERROR(logger, "Unknown error occured!");
  }
}
