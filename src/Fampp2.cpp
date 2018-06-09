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

    $Id: Fampp2.cpp,v 1.5 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <Fampp2.hh>
#include <Fampp2_private.hh>
#include <iostream>

#include <sigc++/sigc++.h>
#include <sigc++/slot.h>


using namespace std;


namespace Fampp
{
    FamppSingletonClass& FamppInstance()
    {
        return Fampp::Instance();
    }
    FAMEvent* getCurrentFAMEvent()
    {
        FamppInstance().getFAMEvent();
    }
    

    static int
    FamReqNum()
    {
        const FAMEvent* ev = Fampp::Instance().getFAMEvent();
        return FAMREQUEST_GETREQNUM( (&(ev->fr)) );
    }

    int
    FamReqNum( FamppRequest *req )
    {
        return FAMREQUEST_GETREQNUM( &req->getRequest() );
    }

    static int
    FamReqNum( fh_fampp_req req )
    {
        return FamReqNum( GetImpl( req ) );
    }




    FamppRequest::FamppRequest(
        const string& filename,
        void* userData,
        bool isFile )
    {
        if(isFile)
        {
            if( 0 != FAMMonitorFile( 
                    &getFAMConnection(),
                    filename.c_str(),
                    &theFAMRequest,
                    userData)) 
            {
                throw FamppFileMonitorInitFailedException(filename);
            }
        }
        else
        {
            if( 0 != FAMMonitorDirectory( 
                    &getFAMConnection(),
                    filename.c_str(),
                    &theFAMRequest,
                    userData)) 
            {
                throw FamppDirMonitorInitFailedException(filename);
            }
        }
    }

// #include <unistd.h>

    FamppRequest::~FamppRequest()
    {
//         cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//         cerr << "FamppRequest::~FamppRequest() this:" << (void*)this << endl;
//         cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//         sleep(5);
        
        if( 0 != FAMCancelMonitor(
                &getFAMConnection(), 
                &theFAMRequest)) 
        {
            throw FamppRequestCancelFailedException(this);
        }
        Fampp::Instance().removeRequest(this);
    }

    FAMRequest&
    FamppRequest::getRequest()
    {
        return theFAMRequest;
    }

    fh_fampp_req
    FamppRequest::toHandle()
    {
//         cerr << "FamppRequest::toHandle(enter)" << endl;
        fh_fampp_req req = fh_fampp_req(this);
//        req->AddRef();
//         cerr << "FamppRequest::toHandle(exit)" << endl;
        return req;
    }
    

    void
    FamppRequest::dispatch()
    {
//        cerr << "FamppRequest::dispatch(enter)" << endl;
        
        FamppEventBase* ev = EventFactory::Instance().CreateObject( getFamEvent()->code );
        
        {
//             cerr << "FamppRequest::dispatch(1)" << endl;
            const fh_fampp_req& req = toHandle();
//             cerr << "FamppRequest::dispatch(2)" << endl;
            ev->dispatch( req );
//             cerr << "FamppRequest::dispatch(3)" << endl;
        }
        
        
//         Sig.emit( getFAMEvent()->code,
//                   getFAMEvent()->getFileName(),
//                   this,
//                   getFAMEvent());

//        cerr << "FamppRequest::dispatch(exit)" << endl;
        
    }


    void
    FamppRequest::suspend()
    {
        if( 0 != FAMSuspendMonitor(
                &getFAMConnection(), 
                &getRequest())) 
        {
            throw FamppSuspendFailedException(this);
        }
    }

    void
    FamppRequest::resume()
    {
        if( 0 != FAMResumeMonitor(
                &getFAMConnection(), 
                &getRequest())) 
        {
            throw FamppResumeFailedException(this);
        }
    }

    FAMEvent*
    FamppRequest::getFamEvent()
    {
        return Fampp::Instance().getFAMEvent();
    }
    
    FAMConnection&
    FamppRequest::getFAMConnection()
    {
        return Fampp::Instance().getFAMConnection();
    }
    
    void
    FamppRequest::bounceEv(
        string filename,
        fh_fampp_req req,
        fh_fampp_ev ev )
    {
        getMuxedSig().emit( filename, req, ev );
    }
    
    FamppRequest::MuxedSig_t&
    FamppRequest::getMuxedSig()
    {
        static bool virgin = true;

        if( virgin )
        {
            virgin = false;
            
            getSig<FamppChangedEvent>().connect(sigc::mem_fun( *this, &FamppRequest::bounceEv));
//             getSig<FamppDeletedEvent>().connect(sigc::mem_fun( *this, &FamppRequest::bounceEv));
//             getSig<FamppStartExecutingEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
//             getSig<FamppStopExecutingEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
//             getSig<FamppCreatedEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
//             getSig<FamppMovedEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
//             getSig<FamppAcknowledgeEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
//             getSig<FamppExistsEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
//             getSig<FamppEndExistEvent>().connect(sigc::mem_fun( this, &FamppRequest::bounceEv));
        }
        return MuxedSig;
    }
    

    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////


    FamppImplMethods::FamppImplMethods()
    {
        if( 0 != FAMOpen( &getFAMConnection()))
        {
            throw FamppOpenFailedException();
        }
    }

    
    FamppImplMethods::~FamppImplMethods()
    {
        if(0 != FAMClose( &theFAMConnection )) {
            throw FamppCloseFailedException();
        }
    }

    
    FAMConnection&
    FamppImplMethods::getFAMConnection()
    {
        return theFAMConnection;
    }
    
    int
    FamppImplMethods::getFD()
    {
        return FAMCONNECTION_GETFD((&theFAMConnection));
    }
    

    FAMEvent*
    FamppImplMethods::getFAMEvent()
    {
        return &theFAMEvent;
    }


    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////


    FamppSingletonClass::FamppSingletonClass()
    {
    }

    FamppSingletonClass::FamppSingletonClass(const string appName)
    {
    }
    
    FamppSingletonClass::~FamppSingletonClass()
    {
    }

    fh_fampp_req
    FamppSingletonClass::makeFamppRequest(
        string filename, 
        void* userData,
        bool isFile) 
    {
        fh_fampp_req ret = new FamppRequest(filename,userData,isFile);
//        cerr << "FamppSingletonClass::makeFamppRequest()... rc:" << ret->getReferenceCount() << endl;
        return ret;
    }


    void
    FamppSingletonClass::removeRequest(FamppRequest *req)
    {
        FAMppRequestsByID[ FamReqNum( req ) ] = 0;
    }


    
    fh_fampp_req
    FamppSingletonClass::MonitorDirectory( string filename, void* userData ) 
        throw(
            FamppDirMonitorInitFailedException
            )
    {
        fh_fampp_req ret = makeFamppRequest( filename, userData, false );
//        cerr << "MonitorDirectory. filename:" << filename << " FamReqNum(ret):" << FamReqNum(ret) << endl;
        FAMppRequestsByID[ FamReqNum(ret) ] = GetImpl(ret);
        return ret;
    }
    

    fh_fampp_req
    FamppSingletonClass::MonitorFile( string filename, void* userData ) 
        throw (FamppFileMonitorInitFailedException)
    {
        fh_fampp_req ret = makeFamppRequest( filename, userData, true );
        FAMppRequestsByID[ FamReqNum(ret) ] = GetImpl(ret);
        return ret;
    }



    void
    FamppSingletonClass::NextEvent()
    {
        try
        {
            if( 0 > FAMNextEvent(
                    &getFAMConnection(), 
                    getFAMEvent())) 
            {
                throw FamppNextEventFailedException();
            }
            
            if( fh_fampp_req req = FAMppRequestsByID[ FamReqNum() ] )
            {
                req->dispatch();
            }
        }
        catch( exception& e )
        {
            addException( e );
        }
    }

    int
    FamppSingletonClass::Pending()
    {
        return FAMPending(&getFAMConnection());
    }

	
    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    
    fh_fampp_req MonitorDirectory( string filename, void* userData ) 
        throw(FamppDirMonitorInitFailedException)
    {
        return Fampp::Instance().MonitorDirectory( filename, userData );
    }
    
        

    fh_fampp_req MonitorFile( string filename, void* userData ) 
        throw(FamppFileMonitorInitFailedException)
    {
        return Fampp::Instance().MonitorFile( filename, userData );
    }
    
    
    
};

