#include <iostream>

// Base Template
template <typename T>
class squareMatrixBase
{
  protected:
    void invert(std::size_t matrixSize);
};

template <typename T>
void squareMatrixBase<T>::invert(std::size_t matrixSize)
{
  std::cout << matrixSize << std::endl;
};


// Child Template
template <typename T, std::size_t n>
class squareMatrix : private squareMatrixBase<T>
{
  private:
    using squareMatrixBase<T>::invert;

  public:
    void invert(){ invert(n); }  // inline

};

int main()
{
  squareMatrix<double, 10> s1;
  squareMatrix<double, 50> s2;
   
  s1.invert();
  s2.invert();
  s1.invert();
 
  return 0;
};
