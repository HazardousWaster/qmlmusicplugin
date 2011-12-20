//          Copyright Narinder S Claire 2008  2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef DETAILS_HEADER_GUARD
#define DETAILS_HEADER_GUARD


#include<map>
#include<vector>
#include<iostream>


namespace papa {

template<typename key,class T>
std::vector<key> GetKeys(const std::map<key,T> &theMap) {

	std::vector<key> theVector;
	typedef typename std::map<key,T>::const_iterator const_iterator;
	const_iterator	theEnd(theMap.end());
	for(const_iterator theIterator(theMap.begin()); theIterator!=theEnd;++theIterator) {
		theVector.push_back(theIterator->first);
        }

	return theVector;
}
}






#endif

