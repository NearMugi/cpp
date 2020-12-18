#include <iostream>
#include <future>
#include <thread>

void f(){
  std::cout << "\nFunction start" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "\nFunction end" << std::endl;
}

int main()
{
  std::cout << "Main start" << std::endl;
  
  auto fut = std::async(std::launch::async, f);
  //auto fut = std::async(std::launch::deferred, f); 

  // もしローンチにstd::launch::deferredを選択すると、
  // wait_forは常にstd::future_status::deferredを返すので、whileから抜け出せない！
  while(fut.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready){
    std::cout << "." << std::flush;
  }
  std::cout << "Main end" << std::endl;
  return 0;
}
