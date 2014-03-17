#ifndef GTK_BOX_UNKNOWN_APPLICATION_H
#define GTK_BOX_UNKNOWN_APPLICATION_H

#include <boost/signals2.hpp>
#include <log4cxx/logger.h>
#include <gtkmm.h>
#include "gtk_application_icon_sublimer.h"
#include "../network_activity.h"

class GtkBoxUnknownApplication : public Gtk::Box
{
  public:
    /*
    ** Signals
    */
    typedef boost::signals2::signal<void(const NetworkActivity*, bool allowed)> signalNewRuleValidated;
    typedef signalNewRuleValidated::slot_type                                   signalNewRuleValidatedType;

    /*
    ** Constructors and Destructor
    */
    GtkBoxUnknownApplication(const NetworkActivity * activity);
    virtual ~GtkBoxUnknownApplication(void);

    /*
    ** Instance methods
    */
    void                                append_to_notebook(Gtk::Notebook * notebook);
    // Signals methods
    static boost::signals2::connection  on_new_rule_validated_connect(const signalNewRuleValidatedType &slot);

  private:
    log4cxx::LoggerPtr                  logger;
    NetworkActivity                     activity;
    Gtk::Notebook *                     notebook;
    bool                                destroying;

    void                                build_box(void);
    void                                on_allow_button_clicked(void);
    void                                on_deny_button_clicked(void);
    void                                make_rule_and_remove_box(bool allowed);

    static signalNewRuleValidated       new_rule_validated;
};

#endif
