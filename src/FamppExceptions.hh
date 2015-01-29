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

    $Id: FamppExceptions.hh,v 1.2 2010/09/24 05:16:51 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#ifndef INCLUDED_FAMEXCEPTIONS_HH
#define INCLUDED_FAMEXCEPTIONS_HH

#include <string>
#include <exception>

namespace Fampp {

    // Forward decl
	class FamppRequest;

	class _exception : public std::exception {
  			std::string _what;
			std::string _extra;
			std::string _fullmsg;

			const std::string getSep() {
				return std::string("   ");
			}

		public:
			_exception(const std::string& what_arg) throw()
                : 
				_what (what_arg), _extra()
				{ }

			_exception(const std::string& what_arg, const std::string& extra) throw()
                : 
				_what (what_arg), _extra(extra)
				{ }

        ~_exception() throw()
            {
            }
        

			virtual const char* what () throw()
            { 
				if(std::string() != _extra) {
					_fullmsg = _what + getSep() + _extra;
					return _fullmsg.c_str();
				}
				return _what.c_str (); 
			}
		protected:
			_exception() throw() : exception() {}
	};
	
	template <class ostreamT>
	ostreamT& operator<< (ostreamT& s, _exception ex)
    {
		return s << ex.what() << "\n";
	}

	class FamppException : public _exception
    {
		public:
			FamppException(const std::string& what_arg):
				_exception(what_arg) 
			{}

			FamppException(const std::string& what_arg, const std::string& extra):
				_exception(what_arg,extra)
			{}

			FamppException():
				_exception(getStdFAMError())
			{}

			std::string getStdFAMError() {
				return "libfam Errors not used at the moment";//std::string("Fam exeption:")+std::string(FamErrlist[FAMErrno]);
			}
	};


	

	class FamppOpenFailedException : public FamppException {
		public:
			FamppOpenFailedException()
				{}
	};


	class FamppCloseFailedException : public FamppException {
		public:
			FamppCloseFailedException()
				{}
	};

	class FamppRequestFailedException : public FamppException {
		public:
			FamppRequestFailedException(const FamppRequest* const req):
				FamppException(getStdFAMError(),
					std::string("hi"))
			{
			}
	};


	class FamppRequestCancelFailedException : public FamppRequestFailedException {
		public:
			FamppRequestCancelFailedException(const FamppRequest* const req):
				FamppRequestFailedException(req)
			{
			}
	};

	class FamppSuspendFailedException : public FamppRequestFailedException {
		public:
			FamppSuspendFailedException(const FamppRequest* const req):
				FamppRequestFailedException(req)
				{}
	};


	class FamppResumeFailedException : public FamppRequestFailedException {
		public:
			FamppResumeFailedException(const FamppRequest* const req):
				FamppRequestFailedException(req)
				{}
	};




///////


	class FamppMonitorInitFailedException : public FamppException {
		public:
			FamppMonitorInitFailedException()
				{}
		protected:
			FamppMonitorInitFailedException(
				const std::string& type, 
				const std::string& path):
					FamppException(getStdFAMError(),
						type + ":" + path)
				{}
	};

	class FamppDirMonitorInitFailedException : public FamppMonitorInitFailedException {
		public:
			FamppDirMonitorInitFailedException(std::string dirName):
				FamppMonitorInitFailedException(
					"dirName",dirName)
				{}
	};

	class FamppFileMonitorInitFailedException : public FamppMonitorInitFailedException {
		public:
			FamppFileMonitorInitFailedException(std::string dirName):
				FamppMonitorInitFailedException(
					"dirName",dirName)
				{}
	};



	class FamppNextEventFailedException : public FamppException {
		public:
			FamppNextEventFailedException()
				{}
	};

};

#endif /* INCLUDED_FAMEXCEPTIONS_HH */



