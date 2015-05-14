#include "gtk_process_icon.h"

GtkProcessIcon::GtkProcessIcon(void)
: logger(log4cxx::Logger::getLogger("GtkProcessIcon"))
{

}

GtkProcessIcon::~GtkProcessIcon(void)
{

}

void GtkProcessIcon::set_icon_from_process(const std::string &icon_name, const std::string &executable_name)
{
    Glib::RefPtr<Gtk::IconTheme> theme = Gtk::IconTheme::get_default();
    Glib::RefPtr<Gtk::IconTheme> hicolortheme = Gtk::IconTheme::create();
    hicolortheme->set_custom_theme("hicolor");

    if (icon_name != "" && icon_name != "image-missing")
    {
        LOG4CXX_DEBUG(logger, "Loading icon with icon_name");
        this->load_icon(icon_name, theme);
    } else if (executable_name != "")
    {
        LOG4CXX_DEBUG(logger, "Loading icon with executable_name");
        this->load_icon(executable_name, hicolortheme);
    } else {
        LOG4CXX_DEBUG(logger, "icon_name and executable_name are empty");
    }
    if (!this->application_large_icon && !this->application_small_icon)
    {
        if (icon_name == "image-missing")
        {
            this->load_icon(icon_name, theme);
        }
    }
}

void GtkProcessIcon::load_icon(const std::string &name, Glib::RefPtr<Gtk::IconTheme> &theme)
{
    if (theme->has_icon(name))
    {
        try {
            this->application_large_icon = theme->load_icon(name, APPLICATION_LARGE_ICON_SIZE, Gtk::ICON_LOOKUP_USE_BUILTIN);
        } catch (const Glib::Error &e)
        {
            LOG4CXX_ERROR(logger, "Unable to load the icon " << name << ": " << e.what());
        }
        this->application_small_icon = theme->load_icon(name, APPLICATION_SMALL_ICON_SIZE, Gtk::ICON_LOOKUP_USE_BUILTIN);
    }
}

Glib::RefPtr<Gdk::Pixbuf> GtkProcessIcon::get_large_icon_pixbuf(void) const
{
    return this->application_large_icon;
}

Glib::RefPtr<Gdk::Pixbuf> GtkProcessIcon::get_small_icon_pixbuf(void) const
{
    return this->application_small_icon;
}
