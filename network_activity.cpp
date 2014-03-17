#include "network_activity.h"

NetworkActivity::NetworkActivity(const std::string &executable_sha256, const std::string &printable_name, const std::string &executable_name, const std::string &icon_name)
: executable_sha256(executable_sha256),
  printable_name(printable_name),
  executable_name(executable_name),
  icon_name(icon_name),
  logger(log4cxx::Logger::getLogger("NetworkActivity"))
{
   this->icon.set_icon_from_process(this->icon_name, this->executable_name);
}

NetworkActivity::~NetworkActivity(void)
{

}
