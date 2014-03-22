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
  const char * root_dirname = dirname(result);
  std::string root_path = std::string(root_dirname);

  LOG4CXX_DEBUG(logger, "Douane root path is " << root_path);

  // Remove the /bin in case the root_path ends with it.
  std::string substr = "/bin";
  size_t position = root_path.rfind(substr);
  if ((position != std::string::npos) && (position == (root_path.length() - substr.length())))
  {
    return root_path.substr(0, position);
  } else {
    return root_path;
  }
}

const std::string Tools::douane_data_path(void) const
{
  return this->douane_root_path() + "/data/";
}
