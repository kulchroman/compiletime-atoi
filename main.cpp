#include <cmath>
#include <iostream>

using namespace std;

static int res;
static int index;
static bool minus_flag;

template <char ch> constexpr void parseSymbol()
{
    if constexpr (ch == ' ')
    {
        index--;
        return;
    }

    if constexpr (ch == '-')
    {
        index--;
        minus_flag = true;
        return;
    }

    if constexpr (ch == '+')
    {
        index--;
        minus_flag = false;
        return;
    }

    res += std::pow(10, index--) * (ch - '0');
}

template <char const *const string, typename T = int, T... ints>
constexpr void parseChar(std::integer_sequence<T, ints...> int_seq)
{
    (parseSymbol<string[ints]>(), ...);
}

template <char const *const string, size_t stringSize> constexpr int myAtoi()
{
    res = 0;
    index = stringSize - 1;
    minus_flag = false;
    parseChar<string>(std::make_integer_sequence<int, stringSize>{});
    return minus_flag ? -res : res;
}

int main()
{
    static constexpr char str0[]{ "  -123" };
    std::cout << myAtoi<str0, 6>() << std::endl;
    return 0;
}
