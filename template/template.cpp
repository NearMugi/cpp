#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

// 型の抽象化
template <typename T1, typename T2>
void print(T1 msg, T2 value) {
  std::cout << msg << " : " << value << std::endl;
}

template <typename T1, typename T2>
void print(T1 msg, std::vector<T2> value) {
  std::ostringstream ss_v;
  std::for_each(value.begin(), value.end(), [&ss_v](T2 v){ss_v << v << ",";});
  // copyだけなら以下の書き方でもOK
  // std::copy(value.begin(), value.end(), std::ostream_iterator<T>(ss_v));
  std::ostringstream ss;
  ss << msg 
     << " : "
     << "["
     << ss_v.str().erase(ss_v.str().size() - 1)
     << "]";
  std::cout << ss.str() << std::endl;
}

int main() {
  {
    int v{1};
    print("int", v);
  }
  {
    std::vector<int> v{1,2,3,4,5};
    print("std::vector", v);
  }
  {
    std::string v{"Hello, world!"};
    print("std::string", v);
  }
}