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

    $Id: Fampp2GlibSupport.cpp,v 1.2 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <Fampp2GlibSupport.hh>
#include <glib.h>

#include <iostream>
using namespace std;


namespace Fampp
{
    ExceptionList_t ExceptionList;
    
    ExceptionList_t getExceptions()
    {
        return ExceptionList;
    }
    void
    clearExceptions()
    {
        ExceptionList.clear();
    }
    
    bool
    haveMoreExceptions()
    {
        return !ExceptionList.empty();
    }
    
    std::exception
    getNextException()
    {
        std::exception r = ExceptionList.front();
        ExceptionList.pop_front();
        return r;
    }
    
    
    void
    addException( const exception& e )
    {
        ExceptionList.push_back(e);
    }
    
    static gboolean
    registerWithGLib_cb( GIOChannel *source,
                         GIOCondition condition,
                         gpointer data)
    {
        while( FamppInstance().Pending() )
        {
            try
            {
                FamppInstance().NextEvent();
            }
            catch( std::exception& e )
            {
                cerr << "fampp2 exception: " << e.what() << endl;
                // Cant throw through glib callback
                // throw;
                addException( e );
            }
        }
        return 1; // call again
    }
    
    void
    ProcessFamppEvents()
    {
        while( FamppInstance().Pending() )
        {
            FamppInstance().NextEvent();
        }
    }
    
    

    void
    RegisterFamppWithGLib()
    {
        static bool alreadyRegistered = false;
        
        if( !alreadyRegistered )
        {
            alreadyRegistered = true;
        
            guint result;
            GIOChannel *channel;
            GIOCondition cond = GIOCondition(G_IO_IN | G_IO_ERR | G_IO_PRI);

//            cerr << "Attaching to fd:" << FamppInstance().getFD() << endl;
            
            channel = g_io_channel_unix_new( FamppInstance().getFD() );
            result  = g_io_add_watch( channel, cond,
                                      registerWithGLib_cb, 0 );
            g_io_channel_unref (channel);
        
        }
    }
 
};

