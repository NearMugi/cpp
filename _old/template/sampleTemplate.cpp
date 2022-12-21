#include <iostream>

template <typename T>
T add(T x, T y)
{
  return x + y;
}

int main()
{
  std::cout << add<int>(5, 3) << std::endl;
  std::cout << add<std::string>("ABC", "abc") << std::endl;
  std::cout << add(5.4, 3.0) << std::endl;
  return 0;
};
