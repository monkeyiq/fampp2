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

    $Id: Fampp2.hh,v 1.5 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#ifndef INCLUDED_FAMPP_HH
#define INCLUDED_FAMPP_HH

#include <Fampp2Handle.hh>

#include <stdexcept>
#include <map>
//#include <hash_map>

#include <fam.h>
#include <sigc++/sigc++.h>
#include <SmartPtr.h>
#include <Singleton.h>

#include <FerrisLoki/loki/Factory.h>
#include <FerrisLoki/loki/SmartPtr.h>
#include <FerrisLoki/Extensions.hh>

namespace Fampp
{
    class FamppSingletonClass;
	class FamppRequest;
    
//     typedef Loki::SmartPtr<
//         FamppRequest,
//         FamppRefCounted,
//         Loki::DisallowConversion,
//         Loki::AssertCheck,
//         Loki::DefaultSPStorage > fh_fampp_req;

    typedef Loki::SmartPtr<
        FamppRequest,
        FerrisLoki::FerrisExRefCounted,
        Loki::DisallowConversion,
        FerrisLoki::FerrisExSmartPointerChecker,
        FerrisLoki::FerrisExSmartPtrStorage >  fh_fampp_req;
    
    
    
    class FamppEventBase;
    typedef Loki::SmartPtr<
        FamppEventBase,
        FerrisLoki::FerrisExRefCounted,
        Loki::DisallowConversion,
        FerrisLoki::FerrisExSmartPointerChecker,
        FerrisLoki::FerrisExSmartPtrStorage >  fh_fampp_ev;

    typedef FamppSingletonClass& Fampp;
//    typedef Loki::SingletonHolder< FamppSingletonClass > Fampp;
    FamppSingletonClass& FamppInstance();
    FAMEvent* getCurrentFAMEvent();
};


#include "FamppExceptions.hh"

namespace Fampp
{


    template <class EventType>
    class FamppRequestEventDispatch
        :
        public virtual sigc::trackable
    {
    public:
        
        typedef sigc::signal< void (
                               std::string,
                               fh_fampp_req,
                               fh_fampp_ev ) > Sig_t;

        template <class T>
        Sig_t& getSig( T* dummy = 0)
            {
                return Sig;
            }

        Sig_t& getSig()
            {
                return Sig;
            }

        
//         Sig_t& getSig(const EventType& c)
//             {
//                 return Sig;
//             }

    protected:
        ~FamppRequestEventDispatch()
            {}
        
        
    private:

        Sig_t Sig;

    };

};
#include "FamppEvents.hh"
namespace Fampp
{


    class FamppRequest
        :
        public FamppHandlable,
        public FamppRequestEventDispatch<FamppChangedEvent>,
        public FamppRequestEventDispatch<FamppDeletedEvent>,
        public FamppRequestEventDispatch<FamppStartExecutingEvent>,
        public FamppRequestEventDispatch<FamppStopExecutingEvent>,
        public FamppRequestEventDispatch<FamppCreatedEvent>,
        public FamppRequestEventDispatch<FamppMovedEvent>,
        public FamppRequestEventDispatch<FamppAcknowledgeEvent>,
        public FamppRequestEventDispatch<FamppExistsEvent>,
        public FamppRequestEventDispatch<FamppEndExistEvent>
    {
        friend class FamppSingletonClass;
        friend int FamReqNum( FamppRequest *req );

        FAMRequest theFAMRequest;

        FamppRequest( const std::string& filename, void* userData=NULL, bool isFile=false );
        FamppRequest( const FamppRequest& ref);
        FamppRequest& operator=(const FamppRequest& ref);
        
        FAMRequest& getRequest();
        fh_fampp_req toHandle();
        void dispatch();
        FAMEvent* getFamEvent();
        FAMConnection& getFAMConnection();

        void bounceEv( std::string filename, fh_fampp_req req, fh_fampp_ev ev );
        
        
    public:

        
        ~FamppRequest();


        void suspend();
        void resume();


        template <class T>
        typename FamppRequestEventDispatch<T>::Sig_t&
        getSig(T* dummy = 0)
            {
                FamppRequestEventDispatch<T>* hook = this;
                return hook->getSig();
            }

        
        typedef sigc::signal< void (
                               std::string,
                               fh_fampp_req,
                               fh_fampp_ev ) > MuxedSig_t;
        MuxedSig_t& getMuxedSig();
        

    private:

        MuxedSig_t MuxedSig;
        
    };

    

    class FamppImplMethods
        :
        public FamppHandlable
    {
        FAMConnection theFAMConnection;

		FamppImplMethods( const FamppImplMethods& ref);
		FamppImplMethods& operator=(const FamppImplMethods& ref);

        // This is where the fam Event's data is stored. 
        FAMEvent theFAMEvent;


        
    protected:

        FamppImplMethods();
        virtual ~FamppImplMethods();


    public:
        
        int getFD();
        FAMConnection& getFAMConnection();


        FAMEvent* getFAMEvent(); // FIXME: private use only FamEvent!
        
    };
    


	class FamppSingletonClass : public FamppImplMethods
    {
        friend class FamppRequest;
        void removeRequest(FamppRequest *req);

//        std::hash_map<int, fh_fampp_req> FAMppRequestsByID;
//        std::map<int, fh_fampp_req> FAMppRequestsByID;
        std::map<int, FamppRequest*> FAMppRequestsByID;

        fh_fampp_req makeFamppRequest(
            std::string filename, 
            void* userData=NULL,
            bool isFile=false);




    public:
        FamppSingletonClass();
        FamppSingletonClass(const std::string appName);
        ~FamppSingletonClass();


        void NextEvent();
        int  Pending();

        fh_fampp_req MonitorDirectory( std::string filename, void* userData=NULL);

        fh_fampp_req MonitorFile( std::string filename, void* userData=NULL);

        
    };
    


    fh_fampp_req MonitorDirectory( std::string filename, void* userData=NULL);

    fh_fampp_req MonitorFile( std::string filename, void* userData=NULL);

    
};

#endif
