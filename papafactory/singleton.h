//          Copyright Narinder S Claire 2008 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef SINGLETON_HEADER_GUARD
#define SINGLETON_HEADER_GUARD
#include <boost/utility.hpp>


namespace papa {
template<class Object>
class singleton :boost::noncopyable
{
public:

    static Object & instance()
    {
        static Object theObject;
        return theObject;
    }
    virtual ~singleton() {} 
} ;
}

#endif

