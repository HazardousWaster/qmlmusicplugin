//          Copyright Narinder S Claire 2008 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef PHACTORY_HEADER_GUARD
#define PHACTORY_HEADER_GUARD 


#include<string>
#include<map>
#include<cassert>

#include<papafactory/singleton.h>
#include<papafactory/papa_exception.h>

#include<boost/shared_ptr.hpp>
#include<boost/scoped_ptr.hpp>
#include<boost/variant.hpp>
#include<boost/utility.hpp>
#include<boost/static_assert.hpp>

#include<boost/mpl/size.hpp>
#include<boost/mpl/list.hpp>
#include<boost/mpl/at.hpp>

#include<boost/preprocessor/repetition.hpp>


#ifndef MAX_PHACTORIES
	#define MAX_PHACTORIES  10
#endif

namespace papa {

template<unsigned long i>
struct unsigned_long {enum {value=i};};

template<class BaseClass>
struct ph_registra_base {
	typedef typename boost::make_variant_over<typename  BaseClass::variant_type_list::type>::type variant;
	typedef std::map<std::string,variant> ParameterMap;

	virtual boost::shared_ptr<BaseClass> Create(const std::string &theKey,const ParameterMap& theMap )const=0;
};

template<class BaseClass>
class phactory :public singleton<phactory<BaseClass> > {
public:
	friend class singleton<phactory<BaseClass> >; 
	typedef typename boost::make_variant_over<typename BaseClass::variant_type_list::type>::type variant;
	typedef typename BaseClass::phactory_map ParameterMap;

	bool Register(const std::string &theKey, const boost::shared_ptr<ph_registra_base<BaseClass> > &theRegistra){
		return theInnerMapPtr->insert(typename InnerMap::value_type(theKey,theRegistra)).second;	
	}
	bool Register(const phactory<BaseClass> &theOther){
			boost::scoped_ptr<InnerMap> theTemp(new InnerMap(*theInnerMapPtr));
			InnerMapIterator theIterator(theOther.theInnerMapPtr->begin());
			while (theIterator!=theOther.theInnerMapPtr->end()) {
				if(!theTemp->insert(typename InnerMap::value_type(*theIterator++)).second)
					return false;
			}
            std::swap(theInnerMapPtr,theTemp);
			return true;	
		}
	boost::shared_ptr<BaseClass> Create(const std::string &id, const ParameterMap & theMap)const {	
						InnerMapIterator theIterator (theInnerMapPtr->find(id));	
						if(theIterator==theInnerMapPtr->end())
							return boost::shared_ptr<BaseClass>(static_cast<BaseClass *>(0));	
						return theIterator->second->Create(id,theMap);	
					}


private:
	typedef typename std::map<std::string,const boost::shared_ptr<ph_registra_base<BaseClass> > > InnerMap;	
	typedef typename InnerMap::const_iterator InnerMapIterator;	
	boost::scoped_ptr<InnerMap> theInnerMapPtr;   
	phactory():theInnerMapPtr(new InnerMap){}
};


#define PARAM(z,Nb,data) boost::get<const typename boost::mpl::at_c<signature, Nb >::type >(theMap.find(theVarNames[Nb])->second)

#define INNER_RETRIVE_OBJECT(z,Nb,data)\
boost::shared_ptr<BaseClass> \
InnerRetrieveObject(const std::string &theKey,const ParameterMap& theMap,unsigned_long< Nb > t) const{\
  CheckMap(theMap);\
  return boost::shared_ptr<BaseClass>(new DerivedClass( BOOST_PP_ENUM(Nb,PARAM,~)  ));	\
 }



template
<
	class BaseClass,
	class DerivedClass
>
class ph_registra:public ph_registra_base<BaseClass>{
public:
	
	typedef typename DerivedClass::constructor_signature_typelist signature;
	typedef typename boost::make_variant_over<typename  BaseClass::variant_type_list::type>::type variant;
	typedef std::map<std::string,variant> ParameterMap;


	enum {ssize = boost::mpl::size<signature>::value};
	
	template<unsigned long i>
	ph_registra(const std::string &theKey, const char *theVariableNames[],const unsigned_long<i> *p=0)
	{
		try {
            boost::shared_ptr<ph_registra<BaseClass,DerivedClass> > 
				theActualRegistra(new ph_registra<BaseClass,DerivedClass>());
		    BOOST_STATIC_ASSERT(i==ssize); // Must have ONE variable name for each paramter of the constructor
		    for(size_t i(0);i<ssize;i++) theActualRegistra->theVarNames[i]=std::string(theVariableNames[i]);
		    phactory<BaseClass>::instance().Register(theKey,theActualRegistra);
		}
		catch(...){return;}
	}

	boost::shared_ptr<BaseClass> Create(const std::string &theKey,const ParameterMap& theMap)const{
		  return InnerRetrieveObject(theKey,theMap,unsigned_long<ssize>());
	  }
	

private:
	BOOST_PP_REPEAT(MAX_PHACTORIES,INNER_RETRIVE_OBJECT,~)
	void CheckMap(const ParameterMap& theMap)const {
		if (theMap.size()!=ssize)throw incorrect_parameters();
		for(size_t i(0);i<ssize;++i)
		 {
			 if (theMap.find(theVarNames[i])==theMap.end())
				 throw missing_parameter(theVarNames[i].c_str());
		 }
	}

	ph_registra(){}
	ph_registra(const ph_registra<BaseClass,DerivedClass> &);
	ph_registra<BaseClass,DerivedClass> &operator=(const ph_registra<BaseClass,DerivedClass> &);
	std::string theVarNames[ssize];
};




}//end namespace

#define PARAM_NAMES(n)   n , static_cast<papa::unsigned_long<sizeof(n)/sizeof(char*)> *>(0)


#undef MAX_PHACTORIES
#undef PARAM
#undef INNER_RETRIVE_OBJECT


#endif

