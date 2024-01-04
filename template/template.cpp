#include <iostream>
#include <sstream>
#include "abstraction_of_types.h"
#include "constraints_on_types.h"

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
}