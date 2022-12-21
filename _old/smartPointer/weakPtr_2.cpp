// shared_ptrの循環参照を回避する
#include <iostream>
#include <memory>

class hoge
{
  public:
    hoge() { std::cout << "constractor" << std::endl; }
    ~hoge() { std::cout << "distractor" << std::endl; }
    
    // weak_ptrを使うことで、所有権を持たないようにする
    // shared_ptrの指すメモリは参照できる
    std::weak_ptr<hoge> ptr;
};

int main()
{
  std::shared_ptr<hoge> p1 = std::make_shared<hoge>();
  std::shared_ptr<hoge> p2 = std::make_shared<hoge>();

  // p1のメンバ変数でp2を確保する
  p1->ptr = p2;
  // p2のメンバ変数でp1を確保する
  p2->ptr = p1;

  //参照先のメモリが解放されていないかどうかはexpired関数を使う
  if(p1->ptr.expired()){
     std::cout<<"expired"<<std::endl; 
  } else {
     std::cout<<"not expired"<<std::endl; 
  }


  return 0;

}; // p1,p2のデストラクタは発生する
