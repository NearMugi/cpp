#include <iostream>

class Month
{
  public:
    static Month Jan() { return Month(1);}
    static Month Feb() { return Month(2);}
    int getVal(){return val;}

  private:
    explicit Month(int m) : val(m){};
    int val;
};

int main()
{
  Month m = Month::Jan();
  std::cout << m.getVal() << std::endl;
};
