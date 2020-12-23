#include <boost/scoped_array.hpp>
#include <iostream>

template<typename T>
class squareMatrixBase
{
  protected:
    // constructor
    squareMatrixBase(std::size_t n, T *pMem) : size(n), pData(pMem)
    {
      std::cout << "Base Constructor" << std::endl; 
    };
    
    void setDataPtr(T* ptr){ pData=ptr;};
    void invert(std::size_t n);

  private:
    std::size_t size;
    T *pData;
};

template<typename T>
void squareMatrixBase<T>::invert(std::size_t n)
{
  std::cout << n << std::endl;
};


template<typename T, std::size_t n>
class squareMatrix : private squareMatrixBase<T>
{
  public:
    squareMatrix() : squareMatrixBase<T>(n, 0), pData(new T[n * n])
    {
      std::cout << "Child Constructor" << std::endl;
      this->setDataPtr(pData.get()); 
    };
    void invert() {invert(n);};

  private:
    using squareMatrixBase<T>::invert;
    boost::scoped_array<T> pData;

};

int main(){
  squareMatrix<double, 10> s1;
  s1.invert();

  return 0;
};
