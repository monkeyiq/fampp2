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

    $Id: Fampp2_private.hh,v 1.2 2010/09/24 05:16:50 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#ifndef INCLUDED_FAMPP_PRIVATE_HH
#define INCLUDED_FAMPP_PRIVATE_HH

#include <exception>

namespace Fampp
{
    void addException( const std::exception& e );
};
#endif
