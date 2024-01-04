#ifndef __CONSTRAINTS_ON_TYPES_H__
#define __CONSTRAINTS_ON_TYPES_H__

class constraints_on_types {

public:
  constraints_on_types(){};
  ~constraints_on_types(){};

  template <typename T>
  void print(T value) {
    if constexpr (std::is_integral_v<T>) {
      std::cout << "Integral type" << std::endl;
    }
    else if constexpr (std::is_same_v<T, std::string>) {
      std::cout << "String type" << std::endl;
    }
    else if constexpr (std::is_same_v<T, std::vector<int>>) {
      std::cout << "Vector type" << std::endl;
    } else {
      std::cout << "Unknown type" << std::endl;
    }
  };
};
#endif //__CONSTRAINTS_ON_TYPES_H__