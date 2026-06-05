#ifndef MAPLE_TYPE_TRAITS_HPP
#define MAPLE_TYPE_TRAITS_HPP 


namespace maple{
	
	// 1. integral_constant（所有 type_traits 的基类）
	template<typename T,T v>
	struct integral_constant{
		static constexpr T value=v;
		using value_type=T;
		using type = integral_constant<T ,v>;
		constexpr operator T()const {return v;}
	};
	
	using true_type=integral_constant<bool,true>;
	using false_type=integral_constant<bool,false>;
	
	// 2. remove_reference（move/forward 依赖它）
	template <typename T> struct remove_reference { using type=T;};
	template <typename T> struct remove_reference<T&>{ using type=T;};
	template <typename T> struct remove_reference<T&&>{ using type=T;};
	
	//3. is_same
	template<typename T,typename U>
	struct is_same:false_type{
	};
	
	template<typename T>
	struct is_same<T,T>:true_type{};
	
	//4. enable_if
	template<bool B,typename T=void>
	struct enable_if{};
	
	template<typename T>
	struct enable_if<true,T>{
		using type=T;
	};
	
	//5. remove_const
	template <typename T>struct remove_const  { using type = T; };
	template <typename T>struct remove_const<const T>  { using type = T; };
	
	
	// 6. is_const
	template <typename T> struct is_const : false_type {};
	template <typename T> struct is_const<const T> : true_type {};
	
	// 7. is_integral
	template <typename T> struct is_integral : false_type {};
	template <> struct is_integral<bool>               : true_type {};
	template <> struct is_integral<char>               : true_type {};
	template <> struct is_integral<signed char>        : true_type {};
	template <> struct is_integral<unsigned char>      : true_type {};
	template <> struct is_integral<short>              : true_type {};
	template <> struct is_integral<unsigned short>     : true_type {};
	template <> struct is_integral<int>                : true_type {};
	template <> struct is_integral<unsigned int>       : true_type {};
	template <> struct is_integral<long>               : true_type {};
	template <> struct is_integral<unsigned long>      : true_type {};
	template <> struct is_integral<long long>          : true_type {};
	template <> struct is_integral<unsigned long long> : true_type {};
	
	// 8. is_floating_point
	template <typename T> struct is_floating_point : false_type {};
	template <> struct is_floating_point<float>       : true_type {};
	template <> struct is_floating_point<double>      : true_type {};
	template <> struct is_floating_point<long double> : true_type {};
	
	// 9. is_arithmetic（整数或浮点）
	template <typename T>
	struct is_arithmetic : integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value> {};
	
	// 10. is_pointer
	template <typename T> struct is_pointer : false_type {};
	template <typename T> struct is_pointer<T*> : true_type {};
	
	// 11. is_reference
	template <typename T> struct is_reference : false_type {};
	template <typename T> struct is_reference<T&> : true_type {};
	template <typename T> struct is_reference<T&&> : true_type {};
	
	//12. is_array
	template <typename T> struct is_array : false_type {};
	template <typename T> struct is_array<T[]> : true_type {};
	template <typename T, size_t N> struct is_array<T[N]> : true_type {};
	
	//// 13. is_void
	template <typename T> struct is_void : is_same<void, typename remove_const<T>::type> {};
	
	// 基本类型 = 平凡析构
	template <typename T>
	struct is_trivially_destructible : is_arithmetic<T> {};
}//namespace maple

#endif
