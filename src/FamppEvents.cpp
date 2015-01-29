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

    $Id: FamppEvents.cpp,v 1.3 2010/09/24 05:16:51 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <FamppEvents.hh>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace Fampp
{
    

const string FamppChangedEventStr = "FAMChanged Event";
static FamppChangedEvent FamppChangedEventObj;

const string FamppDeletedEventStr = "FAMDeleted Event";
static FamppDeletedEvent FamppDeletedEventObj;

const string FamppStartExecutingEventStr = "FAMStartExecuting Event";
static FamppStartExecutingEvent FamppStartExecutingEventObj;

const string FamppStopExecutingEventStr = "FAMStopExecuting Event";
static FamppStopExecutingEvent FamppStopExecutingEventObj;

const string FamppCreatedEventStr = "FAMCreated Event";
static FamppCreatedEvent FamppCreatedEventObj;

const string FamppMovedEventStr = "FAMMoved Event";
static FamppMovedEvent FamppMovedEventObj;

const string FamppAcknowledgeEventStr = "FAMMoved Event";
static FamppAcknowledgeEvent FamppAcknowledgeEventObj;

const string FamppExistsEventStr = "FAMExists Event";
static FamppExistsEvent FamppExistsEventObj;

const string FamppEndExistEventStr = "FAMEndExist Event";
static FamppEndExistEvent FamppEndExistEventObj;

    struct RegisterEventClasses
    {

        template< class T >
        static FamppEventBase* CreateEvent()
            {
                FamppEventBase* ret = 0;
                ret = new T;
                return ret;
            }
        RegisterEventClasses()
            {
                Loki::Factory< FamppEventBase, int >& fac = EventFactory::Instance();

                fac.Register( FAMChanged,        &CreateEvent<FamppChangedEvent> );
                fac.Register( FAMDeleted,        &CreateEvent<FamppDeletedEvent> );
                fac.Register( FAMStartExecuting, &CreateEvent<FamppStartExecutingEvent> );
                fac.Register( FAMStopExecuting,  &CreateEvent<FamppStopExecutingEvent> );
                fac.Register( FAMCreated,        &CreateEvent<FamppCreatedEvent> );
                fac.Register( FAMMoved,          &CreateEvent<FamppMovedEvent> );
                fac.Register( FAMAcknowledge,    &CreateEvent<FamppAcknowledgeEvent> );
                fac.Register( FAMExists,         &CreateEvent<FamppExistsEvent> );
                fac.Register( FAMEndExist,       &CreateEvent<FamppEndExistEvent> );
            }
    };
    static RegisterEventClasses __RegisterEventClassesObject;
};
