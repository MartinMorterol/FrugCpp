
	// la version qui fait le tuple a proprement parlé, constexpr :)
	template <int i, int j = i%2>
	struct is_even {
		constexpr static const bool value = false;
	};
	template <int i>
	struct is_even<i,0> {
		constexpr static const bool value = true;
	};

	template <int i, int j = i%2>
	struct is_odd {
		constexpr static const bool value = false;
	};
	template <int i>
	struct is_odd<i,1> {
		constexpr static const bool value = true;
	};

	template<bool go, int i , class TupleCible, class Value>
	struct add_tuple ;

	template<int i , class TupleCible, class Value>
	struct add_tuple<false,i,TupleCible,Value> {
		constexpr static void add (TupleCible& , Value )
		{
			
		}
	};

	template<int i , class TupleCible, class Value>
	struct add_tuple  <true,i,TupleCible,Value> {
		constexpr static void add (TupleCible& t,Value v)
		{
			std::get<i/2>(t) = v;
		}
	};



	template < size_t ...I ,class Tuple, class ... Args>
	constexpr Tuple make_tuple_even_impl(std::index_sequence<I...>,Tuple&& t, Args... args) {
		std::initializer_list<int> r = {  (add_tuple< is_even<I>::value,I,std::decay_t<Tuple>,std::decay_t<Args>>::add(t,args),0)...};
		(void) r;
		return t;
	}

	/***
	*  Je ne comprend pas pourquoi je n'arrive pas passer is_even tant que selecteur template
	*  a make_tuple_even_impl
	*/
	template <class... T>
	constexpr even_tuple_t<T...> make_tuple_even (T... t) {
		return make_tuple_even_impl( std::make_index_sequence<sizeof...(T)>(), even_tuple_t<T...>(), t... );
	}

	/* version lisible, fonctionnelle mais pas constexpr :''(
	template <class... T>
	even_tuple_t<T...> make_tuple_even2 (T... t) {
		even_tuple_t<T...> retour;
		auto tuple_args = std::make_tuple(t...);
		for_constexp<0, sizeof...(T),2>([&](auto const i){ std::get<i/2>(retour) =  std::get<i>(tuple_args) ;}); 
		return  retour;//make_tuple_even_impl( std::make_index_sequence<sizeof...(T)>(), even_tuple_t<T...>(), t... );
	}
	*/
	
	
	
	

	template < size_t ...I ,class Tuple, class ... Args>
	constexpr Tuple make_tuple_odd_impl(std::index_sequence<I...>,Tuple&& t, Args... args) {
		std::initializer_list<int> r = {  (add_tuple< is_odd<I>::value,I,std::decay_t<Tuple>,std::decay_t<Args>>::add(t,args),0)...};
		(void) r;
		return t;
	}

	/***
	*  Je ne comprend pas pourquoi je n'arrive pas passer is_even tant que selecteur template
	*  a make_tuple_even_impl
	*/
	template <class... T>
	constexpr odd_tuple_t<T...> make_tuple_odd (T... t) {
		return make_tuple_odd_impl( std::make_index_sequence<sizeof...(T)>(), odd_tuple_t<T...>(), t... );
	}
		
		 
