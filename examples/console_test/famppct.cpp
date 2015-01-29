/******************************************************************************
*******************************************************************************
*******************************************************************************

    Copyright (C) 2001 Ben Martin

    This file is part of fampp2.

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

    $Id: famppct.cpp,v 1.5 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <sigc++/sigc++.h>
#include <sigc++/slot.h>
#include <sigc++/object.h>
#include <sigc++/object_slot.h>

#include <glib.h>
#include <stdio.h>

#include <Fampp2.hh>
#include <Fampp2GlibSupport.hh>

#include <iostream>

using namespace std;


void CreatedFamEv( string filename, Fampp::fh_fampp_req req, Fampp::fh_fampp_ev ev )
{
    cerr << "CreatedFamEv() " 
         << " event:" << ev->getEventName() 
         << " filename:" << filename
         << endl;
}


void
OnFamppExistsEvent( string filename, Fampp::fh_fampp_req req, Fampp::fh_fampp_ev ev )
{
    cerr << "OnFamppExistsEvent() " 
         << " event:" << ev->getEventName() 
         << " filename:" << filename
         << endl;
}


void
OnFamppEndExistEvent( string filename, Fampp::fh_fampp_req req, Fampp::fh_fampp_ev ev )
{
    cerr << "OnFamppEndExistEvent() " 
         << " event:" << ev->getEventName() 
         << " filename:" << filename
         << endl;
}

void
OnFamppChangedEvent( string fqfilename, Fampp::fh_fampp_req req, Fampp::fh_fampp_ev ev )
{
    cerr << "OnFamppChangedEvent()"
         << " event:" << ev->getEventName() 
         << " filename:" << fqfilename
         << endl;
}

void
OnFamppDeletedEvent( string fqfilename, Fampp::fh_fampp_req req, Fampp::fh_fampp_ev ev )
{
    cerr << "OnFamppDeletedEvent()"
         << " event:" << ev->getEventName() 
         << " filename:" << fqfilename
         << endl;
}

void
OnFamppMovedEvent( string fqfilename, Fampp::fh_fampp_req req, Fampp::fh_fampp_ev ev )
{
    cerr << "OnFamppMovedEvent()"
         << " event:" << ev->getEventName() 
         << " filename:" << fqfilename
         << endl;
}


int 
main(int argc, char* argv[])
{
    try
    {

        // Hookup to glib for automatic handling during main loop
      Fampp::RegisterFamppWithGLib();

        string path = "/";
        if( argc > 1 )
            path = argv[1];
        // Create a request for /tmp
        cerr << "monitoring directory:" << path << endl;
        Fampp::fh_fampp_req req = Fampp::MonitorDirectory( path );

        // Connect libsigC++ signal
        req->getSig<Fampp::FamppCreatedEvent>(). connect(sigc::ptr_fun(&CreatedFamEv));
        req->getSig<Fampp::FamppExistsEvent>().  connect(sigc::ptr_fun(&OnFamppExistsEvent));
        req->getSig<Fampp::FamppEndExistEvent>().connect(sigc::ptr_fun(&OnFamppEndExistEvent));
        req->getSig<Fampp::FamppChangedEvent>(). connect(sigc::ptr_fun(&OnFamppChangedEvent));
        req->getSig<Fampp::FamppDeletedEvent>(). connect(sigc::ptr_fun(&OnFamppDeletedEvent));
        req->getSig<Fampp::FamppMovedEvent>(). connect(sigc::ptr_fun(&OnFamppMovedEvent));

        
        cerr << "=========================================" << endl;
        cerr << "=========================================" << endl;
        cerr << "=========================================" << endl;

//         while(1)
//         {
//             Fampp::Fampp::Instance().NextEvent();
//             cerr << "next ev" << endl;
//         }

//         while(1)
//         {
//             if( Fampp::Fampp::Instance().Pending() )
//                 Fampp::Fampp::Instance().NextEvent();
//         }
        
        GMainLoop *loop = g_main_loop_new(0,0);
        g_main_loop_run( loop );
        g_main_loop_unref( loop );

//		gtk_main();
		return 0;
    }
	catch( Fampp::FamppException& e )
    {
		cout << e << endl;
	}
}


