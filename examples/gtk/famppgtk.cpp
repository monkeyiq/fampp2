/******************************************************************************
*******************************************************************************
*******************************************************************************

    Copyright (C) 2001 Ben Martin

    This file is part of fampp2.
    This is a simple gtk+ application that monitors /tmp using fam++

    fampp2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fampp2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with fampp2.  If not, see <http://www.gnu.org/licenses/>.

    For more details see the COPYING file in the root directory of this
    distribution.

    $Id: famppgtk.cpp,v 1.4 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <sigc++/sigc++.h>
#include <sigc++/slot.h>
#include <sigc++/object.h>
#include <sigc++/object_slot.h>

#include <gtk/gtk.h>
#include <stdio.h>

#include <Fampp2.hh>
#include <Fampp2GlibSupport.hh>

#include <iostream>

using namespace Fampp;
using namespace std;



static gint delete_event_cb(GtkWidget* w, GdkEventAny* e, gpointer data);
static void button_click_cb(GtkWidget* w, gpointer data);


class ThisApp : public sigc::trackable
{
public:

    void CreatedFamEv(
        string filename,
        fh_fampp_req req,
        fh_fampp_ev ev )
        {
            cerr << "CreatedFamEv() " 
                 << " event:" << ev->getEventName() 
                 << " filename:" << filename
                 << endl;
        }


    void MuxedFamEv(
        string filename,
        fh_fampp_req req,
        fh_fampp_ev ev )
        {
            cerr << "MuxedFamEv() " 
                 << " event:" << ev->getEventName() 
                 << " filename:" << filename
                 << endl;
        }
    

};



int 
main(int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* button;
    GtkWidget* label;
    ThisApp thisobj;
  

    gtk_init(&argc, &argv);  

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    button = gtk_button_new();

    label  = gtk_label_new("Change /tmp!");

    gtk_container_add(GTK_CONTAINER(button), label);
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_window_set_title(GTK_WINDOW(window), "Hello");
    gtk_container_set_border_width(GTK_CONTAINER(button), 10);
  
    gtk_signal_connect(GTK_OBJECT(window),
                       "delete_event",
                       GTK_SIGNAL_FUNC(delete_event_cb),
                       NULL);

    gtk_signal_connect(GTK_OBJECT(button),
                       "clicked",
                       GTK_SIGNAL_FUNC(button_click_cb),
                       label);

	
	try {

        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////
		// Begin FAM++ code                                       //
        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////

        // Hookup to glib for automatic handling during main loop
        RegisterFamppWithGLib();
        
        // Create a request for /tmp
        cerr << "===1======================================" << endl;
        fh_fampp_req req = MonitorDirectory("/tmp");
        cerr << "===2======================================" << endl;

        // Connect libsigC++ signal
        req->getSig<FamppCreatedEvent>();

        req->getSig<FamppCreatedEvent>().connect(sigc::mem_fun(thisobj, &ThisApp::CreatedFamEv));

        // Connect all signals to a method.
//        req->getMuxedSig().connect(SigC::slot(&thisobj, &ThisApp::MuxedFamEv));
        
        cerr << "===3======================================" << endl;

        
        
        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////
		// end of fam specific code, (fam) callbacks initiated by gtk_main() for us 
		// gtk only code from here!
        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////

        cerr << "=========================================" << endl;
        cerr << "=========================================" << endl;
        cerr << "=========================================" << endl;
        
		gtk_widget_show_all(window);
		gtk_main();
		return 0;
    }
	catch(FamppException e) {
		cout << e << endl;
	}
}

static gint 
delete_event_cb(GtkWidget* window, GdkEventAny* e, gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

static void 
button_click_cb(GtkWidget* w, gpointer data)
{
    GtkWidget* label;
    gchar* text;
    gchar* tmp;

    label = GTK_WIDGET(data);
    gtk_label_get(GTK_LABEL(label), &text);
    tmp = g_strdup(text);
    g_strreverse(tmp);
    gtk_label_set_text(GTK_LABEL(label), tmp);
    g_free(tmp);
}
