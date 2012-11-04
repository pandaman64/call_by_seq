#include <tuple>

//namespace{

template<std::size_t... args>
struct index_tuple{};
 
template<std::size_t val,typename T>
struct make_index_tuple_impl;
template<std::size_t val,std::size_t... args>
struct make_index_tuple_impl<val,index_tuple<args...>>
{
	typedef index_tuple<val,args...> type;
};
 
template<std::size_t begin,std::size_t end>
struct make_index_tuple
{
	typedef typename make_index_tuple_impl<begin,typename make_index_tuple<begin+1,end>::type>::type type;
};
template<std::size_t value>
struct make_index_tuple<value,value>
{
	typedef index_tuple<> type;
};
 
template<typename F,typename Tuple,std::size_t... args>
auto call_by_tuple_impl(F f,Tuple t,index_tuple<args...> i)
-> decltype(f(std::get<args>(t)...))
{
	return f(std::get<args>(t)...);
}
 
template<typename F,typename Tuple>
auto call_by_tuple(F f,Tuple t)
-> decltype(call_by_tuple_impl(f,t,typename make_index_tuple<0,std::tuple_size<Tuple>::value>::type()))
{
	return call_by_tuple_impl(f,t,typename make_index_tuple<0,std::tuple_size<Tuple>::value>::type());
}

//}

