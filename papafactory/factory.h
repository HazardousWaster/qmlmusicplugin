//          Copyright Narinder S Claire 2008 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef FACTORY_HEADER_GUARD
#define FACTORY_HEADER_GUARD 

#include<string>
#include<map>

#include"singleton.h"
#include"details.h"
#include"papa_exception.h"

#include<boost/shared_ptr.hpp>
#include<boost/scoped_ptr.hpp>
#include<boost/mpl/size.hpp>
#include<boost/mpl/list.hpp>
#include<boost/mpl/at.hpp>

#include<boost/preprocessor/repetition.hpp>
#include<boost/preprocessor/arithmetic/sub.hpp>

#ifndef MAX_FACTORIES
	#define MAX_FACTORIES  10
#endif


namespace papa {

// One  registration object per class in a hireachy, this is the template blue print for the base classes of
// the registration objects

template
<
	class BaseClass,
	typename Key = std::string,
	unsigned long  = boost::mpl::size<typename BaseClass::factory_constructor_typeList>::value
>
struct registra_base {};

// This is the template blue print for the concrete classes of
// the registration objects

template
<
	class BaseClass,
	class Derived,
	typename Key = std::string,
	unsigned long n = boost::mpl::size<typename BaseClass::factory_constructor_typeList>::value
>
struct registra :public registra_base<BaseClass,Key,n>{};

// This is the factory template blue print of the factory class

template
<
	class BaseClass,
	typename Key = std::string ,
	unsigned long  n = boost::mpl::size<typename BaseClass::factory_constructor_typeList>::value
>
class factory :public singleton<factory<BaseClass,Key,n> > {};

//Helper Macros 
#define PARAM(z,Nb,data)  typename boost::mpl::at_c<typename BaseClass::factory_constructor_typeList,Nb>::type P##Nb
#define  REGISTRABASE(z,Nb,data)\
  template<class BaseClass,typename Key>  struct registra_base<BaseClass,Key,Nb> {\
	virtual boost::shared_ptr<BaseClass> Create(BOOST_PP_ENUM(Nb,PARAM,~))const=0; \
};	

BOOST_PP_REPEAT(MAX_FACTORIES,REGISTRABASE,~)


#define FACTORY(z,Nb,data)     	\
template			\
<				\
	class BaseClass,	\
	typename Key		\
>				\
class factory<BaseClass,Key,Nb> :public singleton<factory<BaseClass,Key,Nb> > {	\
public:	\
		friend class singleton<factory<BaseClass,Key,Nb> >; \
		bool Register(const Key & theKey,boost::shared_ptr<registra_base<BaseClass,Key,Nb> > theregistra){	\
				return theInnerMapPtr->insert(typename InnerMap::value_type(theKey,theregistra)).second;\
			}\
                bool Register(const factory<BaseClass,Key,Nb> &theOther){\
			boost::scoped_ptr<InnerMap> theTemp(new InnerMap(*theInnerMapPtr));\
			InnerMapIterator theIterator(theOther.theInnerMapPtr->begin());\
			while (theIterator!=theOther.theInnerMapPtr->end()) {\
				if(!theTemp->insert(typename InnerMap::value_type(*theIterator++)).second)	\
					return false;\
			}	\
                        std::swap(theInnerMapPtr,theTemp);\
			return true;	\
		}\
		boost::shared_ptr<BaseClass> Create(const Key &id BOOST_PP_COMMA_IF(Nb) BOOST_PP_ENUM(Nb,PARAM,~))const {\
			InnerMapIterator theIterator (theInnerMapPtr->find(id));\
				if(theIterator==theInnerMapPtr->end())throw unregistered_creator(); \
						return theIterator->second->Create( BOOST_PP_ENUM_PARAMS(Nb,P)); \
					}\
		std::vector<Key> GetKeys()const{return papa::GetKeys(*theInnerMapPtr);}\
private:\
		typedef typename std::map<Key,boost::shared_ptr<registra_base<BaseClass,Key,Nb> > > InnerMap;\
		typedef typename InnerMap::const_iterator InnerMapIterator;\
		boost::scoped_ptr<InnerMap> theInnerMapPtr;   \
	        factory():theInnerMapPtr(new InnerMap){}\
};

BOOST_PP_REPEAT(MAX_FACTORIES,FACTORY,~)

// The macro defintions of the registration Objects

#define REGISTRA(z,Nb,data)\
template<class BaseClass,class Derived,typename Key>	\
struct registra<BaseClass,Derived,Key,Nb>:public registra_base<BaseClass,Key,Nb> {\
	registra(const Key & theKey){\
	   try {\
	   factory<BaseClass,Key,Nb> ::instance().Register(theKey,boost::shared_ptr<registra_base<BaseClass,Key,Nb> >(new registra<BaseClass,Derived,Key,Nb>));\
       }\
	   catch (...){}\
     }\
	virtual ~registra(){}\
private:\
	boost::shared_ptr<BaseClass> Create(BOOST_PP_ENUM(Nb,PARAM,~))const	\
		{return boost::shared_ptr<BaseClass>(new Derived( BOOST_PP_ENUM_PARAMS(Nb,P)));}\
	registra(){}\
	registra(const registra<BaseClass,Derived,Key,Nb> &);\
	registra<BaseClass,Derived,Key,Nb> & operator=(const registra<BaseClass,Derived,Key,Nb> &);\
};

BOOST_PP_REPEAT(MAX_FACTORIES,REGISTRA,~)

}//end namepace 

#undef MAX_FACTORIES
#undef PARAM
#undef REGISTRA
#undef REGISTRABASE
#undef FACTORY


#endif 



