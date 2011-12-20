//          Copyright Narinder S Claire 2008 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STATIC_FACTORY_HEADER_GUARD
#define STATIC_FACTORY_HEADER_GUARD 
#include<string>
#include<map>
#include<iostream>
#include<papafactory/singleton.h>
#include<papafactory/details.h>

#include<iostream>

#include<boost/shared_ptr.hpp>
#include<boost/mpl/size.hpp>
#include<boost/mpl/list.hpp>
#include<boost/mpl/at.hpp>

#include<boost/preprocessor/repetition.hpp>
#include<boost/preprocessor/arithmetic/sub.hpp>

#ifndef MAX_STATIC_FACTORIES
	#define MAX_STATIC_FACTORIES  10
#endif


namespace papa {

template
<
	class BaseClass,
	typename Key = std::string
>
struct static_registra_base {	
	virtual boost::shared_ptr<BaseClass> RetrieveObject()const=0;
};	

template
<
	class BaseClass,
	class Derived,
	typename Key = std::string,
	unsigned long n = boost::mpl::size<typename BaseClass::factory_constructor_typeList>::value
>
struct static_registra :public static_registra_base<BaseClass,Key>{};

template
<	
class BaseClass,
typename Key=std::string	
>	
class static_factory :public singleton<static_factory<BaseClass,Key> >{		
public:									
	friend class singleton<static_factory<BaseClass,Key> >;
	bool Register(const Key & theKey,static_registra_base<BaseClass,Key> *theRegistra){	
                     // std::cerr << (theKey) << " is Registered " << " at " << &(theInnerMap) << "\n";
					return theInnerMap.insert(typename InnerMap::value_type(theKey,theRegistra)).second;	
						}	
	bool Register(const static_factory<BaseClass,Key> &theOther){
		InnerMap temp(theInnerMap);
		InnerMapIterator theIterator(theOther.theInnerMap.begin());
		while (theIterator!=theOther.theInnerMap.end()) {
			//std::cerr << (theIterator->first) << " is Registered " << " at " << &(theInnerMap) << "\n" ;
			temp.insert(typename InnerMap::value_type(*theIterator++));             
		}
		theInnerMap = temp;
		return true;
	}  
					
	boost::shared_ptr<BaseClass> RetrieveObject(const Key &id )const {	
					//	std::cerr << " Retireving object " << (id) << " from " << &(theInnerMap) << "\n" ;
						InnerMapIterator theIterator (theInnerMap.find(id));	
						if(theIterator==theInnerMap.end())
							return boost::shared_ptr<BaseClass>(static_cast<BaseClass *>(0));	
						return theIterator->second->RetrieveObject();	
					}
	std::vector<Key> GetKeys()const{return papa::GetKeys(theInnerMap);}

private:	
	typedef typename std::map<Key,static_registra_base<BaseClass,Key> *> InnerMap;	
	typedef typename std::map<Key,static_registra_base<BaseClass,Key> *>::const_iterator InnerMapIterator;	
	std::map<Key,static_registra_base<BaseClass,Key> *> theInnerMap;
	static_factory(){};

};

//Helper Macros 
#define PARAM(z,Nb,data)  typename boost::mpl::at_c<typename BaseClass::factory_constructor_typeList,Nb>::type P##Nb

#define STATICREGISTRA(z,Nb,data) template<class BaseClass,class Derived,typename Key>	 \
	struct static_registra<BaseClass,Derived,Key, Nb >:public static_registra_base<BaseClass,Key> \
	{\
	static_registra(const Key & theKey BOOST_PP_COMMA_IF(Nb) BOOST_PP_ENUM(Nb,PARAM,~)): \
		theObjectPtr(new Derived(BOOST_PP_ENUM_PARAMS(Nb,P))) \
		{\
			static_factory<BaseClass,Key>::instance().Register(theKey,this);\
		}\
	boost::shared_ptr<BaseClass> RetrieveObject()const{return theObjectPtr;} \
	virtual ~static_registra(){} \
private: \
	boost::shared_ptr<BaseClass> theObjectPtr; \
	};

BOOST_PP_REPEAT(MAX_STATIC_FACTORIES,STATICREGISTRA,~)


#define STATICFACTORY_INSTANCE(BaseClass) INSTANCE(static_factory< BaseClass > )

}//end namespace

#undef MAX_STATIC_FACTORIES
#undef PARAM
#undef STATICREGISTRA

#endif




