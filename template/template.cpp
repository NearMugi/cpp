#include <iostream>
#include <sstream>
#include "abstraction_of_types.h"
#include "constraints_on_types.h"
#include "inheritance_of_template_parameters.h"

int main() {
  {
    std::cout << "Abstraction of types" << std::endl;
    abstraction_of_types a;
    {
      int v{1};
      a.print("int", v);
    }
    {
      std::vector<int> v{1,2,3,4,5};
      a.print("std::vector", v);
    }
    {
      std::string v{"Hello, world!"};
      a.print("std::string", v);
    }
    {
      abstraction_of_types::Structure_01 v{"value1", 1};
      a.print("Structure_01", v);
    }
    {
      abstraction_of_types::Structure_02 v{"value2", {1,2,3,4,5,6,7,8,9,10}};
      a.print("Structure_02", v);
    }
    std::cout << "" << std::endl;
  }

  {
    std::cout << "Constraints on types" << std::endl;
    constraints_on_types a;
    {
      int v{1};
      a.print(v);
    }
    {
      float v{1};
      a.print(v);
    }
    {
      std::string v{"Hello, world!"};
      a.print(v);
    }
    {
      std::vector<int> v{1,2,3,4,5};
      a.print(v);
    }
    {
      std::vector<float> v{1,2,3,4,5};
      a.print(v);
    }
    std::cout << "" << std::endl;
  }

  {
    std::cout << "Inheritance of template parameters" << std::endl;
    inheritance_of_template_parameters<int, float> a(1, 0.125);
    std::cout << "inheritance_of_template_parameters<int, float> a(1, 0.125);" << std::endl;
    std::cout << "value1 : " << a.getValue1() << std::endl;
    std::cout << "value2 : " << a.getValue2() << std::endl;

    inheritance_of_template_parameters<bool, std::array<int,5>> b(true, {0,1,2,3,4});
    std::cout << "inheritance_of_template_parameters<bool, std::array<int,5>> b(true, {0,1,2,3,4});" << std::endl;
    std::cout << "value1 : " << std::boolalpha << b.getValue1() << std::endl;
    {
      auto value = b.getValue2();
      std::ostringstream ss_v;
      std::for_each(value.begin(), value.end(), [&ss_v](int v){ss_v << v << ",";});
      std::cout << "value2 : " << "{" << ss_v.str().erase(ss_v.str().size() - 1) << "}" << std::endl;
    }

  }
}