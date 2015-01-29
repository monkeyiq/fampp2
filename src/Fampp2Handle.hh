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

    $Id: Fampp2Handle.hh,v 1.3 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#ifndef INCLUDED_FAMPP_HANDLE_H
#define INCLUDED_FAMPP_HANDLE_H

#include <sigc++/sigc++.h>

//#include <iostream>
#include <SmartPtr.h>

// #include <iostream>
// using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Emits a signal before last reference is dropped.
////////////////////////////////////////////////////////////////////////////////

// /**
//  * SmartPtr<> policy class for Handlable objects. This class implements a
//  * intrusive reference count like the COMRefCounted policy in the Modern
//  * C++ design book.
//  */
// template <class P>
// class FamppRefCounted
// {
// public:
    
//     FamppRefCounted()
//         {}

//     FamppRefCounted( const FamppRefCounted& r)
//         {}
    
//     template <class U>
//     FamppRefCounted(const FamppRefCounted<U>&)
//         {}

    

//     /**
//      * Create a new handle
//      */
//     P Clone(const P& val)
//         {
//             if( val )
//             {
// //	            cerr << "Adding   ref :" << (void*)val << endl;
//         	    val->AddRef();
//             }
//             return val;
//         }

//     /**
//      * A signal that is emitted when the object is about to die.
//      */
//     typedef SigC::Signal1< void, P > ClosureSignal_t;
//     ClosureSignal_t ClosureSignal;

//     /**
//      * Get the ClosureSignal_t for this object.
//      */
//     ClosureSignal_t& getClosureSignal()
//         {
//             return ClosureSignal;
//         }

//     /**
//      * Release a reference. This may trigger a getClosureSignal() to fire due to
//      * the final reference being dropped.
//      *
//      * @param val Object that we are releasing an intrusive reference to
//      * @return true if the object should die.
//      */
//     bool Release(const P& val)
//         {
// //            cerr << "Removing ref :" << (void*)val << endl;
//             if( !val )
//             {
//                 return false;
//             }
            
//             // P::ref_count_t
//             int v = val->AddRef();
//             if( v == 2 )
//             {
//                 getClosureSignal().emit(val);
//             }

//             v = val->Release();
//             v = val->Release();
//             if( !v )
//             {
//                 /*
//                  * Time to die amigo
//                  */
//                 return true;
//             }

//             return false;
//         }
        
//     enum { destructiveCopy = false };
        
//     static void Swap(FamppRefCounted&)
//         {
//         }
// };


/**
 * Base class for all classes that have handles using the FamppRefCounted<>
 * policy.
 */
class FamppHandlable
{
protected:

    /**
     * Type for reference counts. This could be 16/32/64 bits.
     */
    typedef long ref_count_t;

    /**
     * shared reference count for all handles that point to this object.
     */
    ref_count_t ref_count;
    
public:

    /**
     * We start with a single reference already to prevent boundary race
     * conditions.
     */
    FamppHandlable()
        :
        ref_count(0)
        {
        }

    /**
     * Add another reference
     */
    virtual ref_count_t AddRef()
        {
//             cerr << "FamppHandlable::AddRef() OLD ref_count : " << ref_count
//                  << " this: " << (void*)this
//                  << endl;
            return ++ref_count;
        }

    /**
     * Release a reference
     */
    virtual ref_count_t Release()
        {
//             cerr << "FamppHandlable::Release() OLD ref_count : " << ref_count
//                  << " this: " << (void*)this
//                  << endl;
            return --ref_count;
        }

    virtual void private_AboutToBeDeleted()
        {
        }

    ref_count_t getReferenceCount()
        {
            return ref_count;
        }
    
    

//     int rc()
//         {
//             return ref_count;
//         }
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////




#endif
