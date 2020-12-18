#include <iostream>
#include <utility>

struct A {
  A() {}

  // 左辺値からコピー
  A(const A&)
  {
    std::cout << "copy" << std::endl;
  }

  // 右辺値からムーブ
  A(A &&)
  {
    std::cout << "move" << std::endl;
  }
};

int main()
{
  A a;
  A a1 = a;             // A(const A&)が呼ばれる
  A a2 = std::move(a);  // A(A&&)が呼ばれる
}
