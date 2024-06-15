#include <iostream>

#include <concepts>
#include <vector>
#include <list>
#include <utility> // declval

template <typename T, typename = void>
struct is_container: std::false_type {};


template <typename T>
struct is_container<T, std::void_t<
        decltype(std::begin(std::declval<T&>())),
        decltype(std::end(std::declval<T&>()))
>
>: std::true_type {};


template <typename T>
using element_type = typename std::iterator_traits<decltype(std::begin(std::declval<T&>()))>::value_type;

/*
template <typename T,
		  typename = std::enable_if_t<is_container<T>::value &&
					  !std::is_same_v<element_type<T>,char>>>
std::ostream& operator<<(std::ostream& os, const T& c)
{
	os << "{";
	auto b = std::begin(c), e = std::end(c);
	if (b!=e) {
		os << *b;
		while (++b != e)
			os << "," << *b;
	}
	return os << "}";
}
*/

template <typename T>
constexpr auto is_character_v = std::is_same_v<char, std::remove_cvref_t<T>>;

/** Similar solution using concepts: */
template <typename T>
concept NotChar = !is_character_v<T>;

template <typename C>
concept Container = requires(C&& c)
{
    { *std::begin(c) } -> NotChar;
    {std::end(c)};
};

template <Container T>
std::ostream& operator<<(std::ostream& os, const T& c)
{
    os << "{";
    auto b = std::begin(c), e = std::end(c);
    if (b!=e) {
        os << *b;
        while (++b != e)
            os << "," << *b;
    }
    return os << "}";
}


template <typename T>
struct TD;


int main(){
//	TD<element_type<std::string>> e_t;
    std::cout << std::is_same_v<element_type<std::string>, char> << std::endl;
    std::cout << std::is_same_v<element_type<std::vector<int>>, int> << std::endl;
    std::cout << is_container<std::vector<int>>::value << std::endl;
    std::cout << is_container<std::string>::value << std::endl;

    auto ac = "{";
    std::cout << is_container<decltype(ac)>::value << std::endl;

    std::cout << std::vector{1,2,3} << std::endl;
    std::cout << std::list{1,2,3} << std::endl;
    std::cout << std::list{std::vector{1,2,3},std::vector{4,5,6}} << std::endl;
    using namespace std::string_literals; // "c++string"s
    std::cout << std::vector{"hello"s,"template"s,"world"s} << std::endl;
}