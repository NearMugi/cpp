#include <iostream>

template<typename T>
class nameObject{
public:
  // Default Constructor
  nameObject(){
    std::cout << "Default Constructor" << std::endl;    
  };

  // Copy Constructor
  nameObject(const nameObject& rhs)
  : nameValue(rhs.nameValue), objectValue(rhs.objectValue)
  {
    std::cout << "Copy Constructor" << std::endl;
  };

  // Destructor
  ~nameObject(){
    std::cout << "Destructor" << std::endl;
  };

  // Copy Assignment Operator
  nameObject& operator=(const nameObject& rhs){
   std::cout << "Copy Assignment Operator" << std::endl;
   return *this; 
  };

  nameObject(const char* name, const T& value)
  : nameValue(name), objectValue(value) {
    std::cout << "Constructor(char*, T)" << std::endl;
  };

  nameObject(const std::string& name, const T& value)
  : nameValue(name), objectValue(value) {
    std::cout << "Constructor(std::string, T)" << std::endl;
  };

  void printValue(){ 
    std::cout << nameValue << std::endl;
    std::cout << objectValue << std::endl;
  };  

private:
  std::string nameValue;
  T objectValue;
};


int main(){
  // コンストラクタ
  nameObject<int> no1("hogehoge", 2);

  // コピーコンストラクタ
  nameObject<int> no2(no1);
  nameObject<int> no3 = no1;

  // デフォルトコンストラクタ
  nameObject<int> no4;

  // コピー演算子
  no4 = no3;

  no1.printValue();
  no2.printValue();
  no3.printValue();
  no4.printValue();

  std::cout << "main end" << std::endl;
};
