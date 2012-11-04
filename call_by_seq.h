#include <tuple>
#include <utility>

#include "call_by_tuple.h"

//namespace panlib{

template<typename Tuple,typename T>
struct join_tuple;
template<typename T,template <typename...> class Pack,typename ...Args>
struct join_tuple<Pack<Args...>,T>{
	typedef Pack<Args...,T> type;
};

template<typename F,typename Tuple>
class seq_caller_t;
template<typename Tuple,typename R,typename ...Args>
class seq_caller_t<R (Args...),Tuple>{
public:
	typedef R (&&functor_type)(Args...);
	typedef R return_type;
	typedef std::tuple<Args...> arguments_tuple_type;
	typedef Tuple arguments_type;

	seq_caller_t(functor_type&& f,Tuple&& t) : functor(std::forward(f)),arguments(std::forward(t)){
	}

	return_type operator ()(void){
		return call_by_tuple(arguments);
	}

	template<typename T>
	seq_caller_t<functor_type,typename join_tuple<arguments_type,T>::type>
	operator ()(T obj){
		return {functor,std::move(arguments)};
	}

private:
	functor_type functor;
	arguments_type arguments;
};

//}

