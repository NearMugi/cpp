#ifndef __INHERITANCE_OF_TEMPLATE_PARAMETERS__
#define __INHERITANCE_OF_TEMPLATE_PARAMETERS__

template <typename T, typename U>
class inheritance_of_template_parameters {

public:
  inheritance_of_template_parameters(T t, U u)
  : value1(t) 
  , value2(u)
  {};
  ~inheritance_of_template_parameters(){};

  T getValue1() const {return value1;}
  U getValue2() const {return value2;}

private:
  T value1;
  U value2;

};
#endif //__INHERITANCE_OF_TEMPLATE_PARAMETERS__