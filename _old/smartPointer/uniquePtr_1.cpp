#include <iostream>
#include <memory>

class hoge 
{
  public:
    hoge(int v):value(v) { std::cout << "hoge::hoge() constractor" << std::endl; }
    ~hoge() { std::cout << "hoge::hoge() distractor" << std::endl; }
    
    int v() const {return value;}

  private:
    int value;
};

int main()
{
  // リソースを設定する
  std::unique_ptr<hoge> p0(new hoge(10));
  std::cout << p0->v() << std::endl;
  
  // 所有権をp1に移動させる
  std::unique_ptr<hoge> p1(std::move(p0));
  std::cout << p1->v() << std::endl;


  // reset関数を使ってリソースを開放する
  std::cout << "reset!" << std::endl;  
  p1.reset();

  // 再設定
  p1.reset(new hoge(99));
  std::cout << p1->v() << std::endl;

  return 0;
};
