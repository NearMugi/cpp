// shared_ptrの循環参照の例
#include <iostream>
#include <memory>

class hoge
{
  public:
    hoge() { std::cout << "constractor" << std::endl; }
    ~hoge() { std::cout << "distractor" << std::endl; }

    std::shared_ptr<hoge> ptr;
};

int main()
{
  std::shared_ptr<hoge> p1 = std::make_shared<hoge>();
  std::shared_ptr<hoge> p2 = std::make_shared<hoge>();

  // p1のメンバ変数でp2を確保する
  p1->ptr = p2;
  // p2のメンバ変数でp1を確保する
  p2->ptr = p1;

  return 0;

}; // p1,p2のデストラクタが発生しない
