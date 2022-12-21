#include<iostream>
class family
{
  public:
    // 純粋仮想関数
    virtual void greet() = 0;
};

class personA : public family
{
  public:
    virtual void greet();
};

void personA::greet()
{
  std::cout << "Hello" << std::endl;
};

class personB : public family
{
  public:
    virtual void greet();
};

void personB::greet()
{
  std::cout << "Hey!!!" << std::endl;
};

int main()
{
  personA pA;
  personB pB;
  
  pA.greet();
  pB.greet();
  
  family* fam[] = 
  {
    &pA, &pB
  };

  for(family* f : fam)
  {
    f->greet();
  };

  return 0;
};
