#ifndef __ABSTRACTION_OF_TYPES_H__
#define __ABSTRACTION_OF_TYPES_H__
// 型の抽象化

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

class abstraction_of_types {

public:
  abstraction_of_types(){};
  ~abstraction_of_types(){};

  struct Structure_01 {
    std::string element_11;
    int element_12;
  };

  struct Structure_02 {
    std::string element_21;
    std::vector<int> element_22;
  };

  template <typename T1 = std::string, typename T2>
  void print(T1 msg, T2 value) {
    std::ostringstream ss;
    ss << msg << " : " << value;
    std::cout << ss.str() << std::endl;
  };

  template <typename T1 = std::string, typename T2>
  void print(T1 msg, std::vector<T2> value) {
    std::ostringstream ss_v;
    std::for_each(value.begin(), value.end(), [&ss_v](T2 v){ss_v << v << ",";});
    
    std::ostringstream ss_vector;
    ss_vector << "[" << ss_v.str().erase(ss_v.str().size() - 1) << "]";
    
    std::ostringstream ss;
    ss << msg << ss_vector.str();
    std::cout << ss.str() << std::endl;
  };

  template <typename T1 = std::string, typename T2 = Structure_01>
  void print(T1 msg, Structure_01 value) {
    std::ostringstream ss_v;
    ss_v << "{"
        << value.element_11
        << ", "
        << value.element_12
        << "}";

    std::ostringstream ss;
    ss << msg << " : " << ss_v.str();
    std::cout << ss.str() << std::endl;
  };

  template <typename T1 = std::string, typename T2 = Structure_02>
  void print(T1 msg, Structure_02 value) {

    std::ostringstream ss_v2;
    std::for_each(value.element_22.begin(), value.element_22.end(), [&ss_v2](auto v){ss_v2 << v << ",";});

    std::ostringstream ss_vector;
    ss_vector << "[" << ss_v2.str().erase(ss_v2.str().size() - 1) << "]";

    std::ostringstream ss_v;
    ss_v << "{"
        << value.element_21
        << ", "
        << ss_vector.str()
        << "}";

    std::ostringstream ss;
    ss << msg << " : " << ss_v.str();
    std::cout << ss.str() << std::endl;
  };
};

#endif