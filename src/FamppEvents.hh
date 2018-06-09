/******************************************************************************
*******************************************************************************
*******************************************************************************

    Copyright (C) 2000 Ben Martin

    These are the events that fam++ can raise. Also event handler adapters.
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

    $Id: FamppEvents.hh,v 1.5 2010/09/24 05:16:51 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <Fampp2.hh>

#ifndef INCLUDED_FAMPPEVENTS_HH
#define INCLUDED_FAMPPEVENTS_HH

#include <fam.h>
#include <sigc++/signal.h>
#include <SmartPtr.h>
#include <Singleton.h>
#include <Factory.h>
#include <Functor.h>
#include <FerrisLoki/Extensions.hh>

namespace Fampp
{

//     template < class Product >
//     struct MakeObject
//     {
//         static FamppEventBase* Create()
//             {
//                 FamppEventBase* ret = 0;
//                 ret = new Product();
//                 return ret;
//             }
//     };


//     typedef Loki::SingletonHolder<
//         Loki::Factory< FamppEventBase,
//                        int,
//                        FamppEventBase* (*)()
//         >
//     >
//     EventFactory;


    typedef Loki::SingletonHolder<
        Loki::Factory< FamppEventBase, int >,
        Loki::CreateUsingNew, Loki::NoDestroy
        > EventFactory;


    
    
    typedef int FamppFAMCode_t;

    class FamppEventBase
        :
        public FamppHandlable
    {
    protected:
        
        friend class FamppRequest;
        virtual void dispatch( fh_fampp_req req ) = 0;

    public:

        FamppEventBase()
            {
            }

        virtual ~FamppEventBase()
            {
            }
        
        virtual FamppFAMCode_t getFAMCode() const = 0;
        virtual std::string getFileName() const = 0;
        virtual std::string getEventName() = 0;
        
    };

    template <
        FamppFAMCode_t FamppFAMCode,
        const std::string& EventNameStr,
        class TypeClass >
    class FamppEvent
        :
        public FamppEventBase
    {
        FAMEvent* getFamEvent()
            {
//                return Instance().getFAMEvent();
                return getCurrentFAMEvent();
            }

    protected:

        friend class FamppRequest;
        void dispatch( fh_fampp_req req )
            {
//                cerr << "FamppEvent::dispatch(enter)" << endl;
                
                FamppRequestEventDispatch<TypeClass>* sigsrc = ::Ferris::GetImpl( req );
///                FamppRequestEventDispatch<TypeClass>* sigsrc = *req;
                
                sigsrc->getSig().emit( getFileName(), req, this);
                    
//                cerr << "FamppEvent::dispatch(exit)" << endl;
            }
        

    public:


        FamppEvent()
            {
//                EventFactory::Instance().Register( FamppFAMCode, &MakeObject<TypeClass>::Create );

                
            }

        FamppFAMCode_t getFAMCode() const
            {
				return FamppFAMCode;
			}

        std::string getFileName() const
            {
//                FAMEvent* ev = Fampp::Instance().getFAMEvent();
                FAMEvent* ev = getCurrentFAMEvent();
                return std::string(ev->filename);
            }
        
        /**
         * eventName - return printable name of fam event code
         */
        std::string getEventName()
            {
				static std::string name = "FAMChanged";
				return EventNameStr;
			}

    };

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    
    extern const std::string FamppChangedEventStr;
    class FamppChangedEvent : public FamppEvent< FAMChanged,
                              FamppChangedEventStr,
                              FamppChangedEvent>
    {
    };
    

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppDeletedEventStr;
    class FamppDeletedEvent : public FamppEvent< FAMDeleted,
                              FamppDeletedEventStr,
                              FamppDeletedEvent>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppStartExecutingEventStr;
    class FamppStartExecutingEvent : public FamppEvent< FAMStartExecuting,
                                     FamppStartExecutingEventStr,
                                     FamppStartExecutingEvent>
    {};
    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppStopExecutingEventStr;
    class FamppStopExecutingEvent : public FamppEvent< FAMStopExecuting,
                                    FamppStopExecutingEventStr,
                                    FamppStopExecutingEvent>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppCreatedEventStr;
    class FamppCreatedEvent : public FamppEvent< FAMCreated,
                              FamppCreatedEventStr,
                              FamppCreatedEvent>
    {};
    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppMovedEventStr;
    class FamppMovedEvent : public FamppEvent< FAMMoved,
                                               FamppMovedEventStr,
                                               FamppMovedEvent>
    {};
    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppAcknowledgeEventStr;
    class FamppAcknowledgeEvent : public FamppEvent< FAMAcknowledge,
                                  FamppAcknowledgeEventStr,
                                  FamppAcknowledgeEvent>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppExistsEventStr;
    class FamppExistsEvent : public FamppEvent< FAMExists,
                             FamppExistsEventStr,
                             FamppExistsEvent>
    {};
    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    
    extern const std::string FamppEndExistEventStr;
    class FamppEndExistEvent : public FamppEvent< FAMEndExist,
                               FamppEndExistEventStr,
                               FamppEndExistEvent>
    {};
    



    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

};



#endif
