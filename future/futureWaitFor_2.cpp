#include <iostream>
#include <future>
#include <thread>

// std::launch::asyncを指定したfutureを返すテンプレート関数
template<typename F, typename... Ts>
inline
std::future<typename std::result_of<F(Ts...)>::type>
reallyAsync(F&& f, Ts&&... params)
{
  // 非同期(std::launch::async)にf(params...)を呼び出す
  // futureを返す
  return std::async(
    std::launch::async,
    std::forward<F>(f),
    std::forward<Ts>(params)...);
}


void f(){
  std::cout << "\nFunction start" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "\nFunction end" << std::endl;
}

int main()
{
  std::cout << "Main start" << std::endl;
  
  // 必ずローンチにstd::launch::asyncを選択する
  auto fut = reallyAsync(f);

  while(fut.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready){
    std::cout << "." << std::flush;
  }
  std::cout << "Main end" << std::endl;
  return 0;
}
