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

    $Id: Fampp2GlibSupport.hh,v 1.2 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include <Fampp2.hh>
#include <list>

#ifndef INCLUDED_FAMPPGLIBSUP_HH
#define INCLUDED_FAMPPGLIBSUP_HH

namespace Fampp
{
    void RegisterFamppWithGLib();
    void ProcessFamppEvents();

    typedef std::list< std::exception > ExceptionList_t;
    bool haveMoreExceptions();
    std::exception getNextException();
};


#endif
