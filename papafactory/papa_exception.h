//          Copyright Narinder S Claire 2008 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef PAPA_EXCEPTION_HEADER_GUARD
#define PAPA_EXCEPTION_HEADER_GUARD

#include <exception>

namespace papa {
    class exception: public std::exception
    {
	public:
       virtual const char* what() const throw()
		{
			return "Unknown papa exception";
		}
    };

	class unregistered_creator: public exception
	{
	public:
        virtual const char* what() const throw()
		{
			return "unregistered_creator";
		}
	};
	class incorrect_parameters: public exception
	{
	public:
        virtual const char* what() const throw()
		{
			return "incorrect_parameters";
		}
	};
	class missing_parameter: public exception
	{
	public:
		missing_parameter(const char * theVarName_):theVarName(theVarName_){}
        virtual const char* what() const throw()
		{
			return theVarName;
		}
	private:
		const char * theVarName;
	};

}
#endif //PAPA_EXCEPTION_HEADER_GUARD

