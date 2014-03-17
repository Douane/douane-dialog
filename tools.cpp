#include "tools.h"

Tools::Tools(void)
: logger(log4cxx::Logger::getLogger("Tools"))
{

}

Tools::~Tools(void)
{

}

const std::string Tools::douane_root_path(void) const
{
  char    result[PATH_MAX];
  readlink("/proc/self/exe", result, PATH_MAX);
  const char * root_path = dirname(result);

  LOG4CXX_DEBUG(logger, "Douane root path is " << root_path);

  // Ensure folder exists
  mkdir(root_path, 0700);

  return std::string(root_path);
}

const std::string Tools::douane_data_path(void) const
{
  return this->douane_root_path() + "/data/";
}
