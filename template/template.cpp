#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

// 型の抽象化
template <typename T>
void print(T value) {
  std::cout << value << std::endl;
}

template <typename T>
void print(std::vector<T> value) {
  std::ostringstream ss_v;
  std::for_each(value.begin(), value.end(), [&ss_v](T v){ss_v << v << ",";});
  // copyだけなら以下の書き方でもOK
  // std::copy(value.begin(), value.end(), std::ostream_iterator<T>(ss_v));
  std::ostringstream ss;
  ss << "["
     << ss_v.str().erase(ss_v.str().size() - 1)
     << "]";
  std::cout << ss.str() << std::endl;
}

int main() {
  {
    int v{1};
    print(v);
  }
  {
    std::vector<int> v{1,2,3,4,5};
    print(v);
  }
  {
    std::string v{"Hello, world!"};
    print(v);
  }
}