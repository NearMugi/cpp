#include <iostream>
#include <future>
#include <thread>

int foo() { std::cout << "executes foo()\n"; return 3; }

int main()
{
  // 新たなスレッドで関数foo()を非同期実行
  {
    std::cout << "invokes std::async(std::launch::async, foo)" << std::endl;
    std::future<int> f = std::async(std::launch::async, foo);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "main thread: slept for 10 msec\n";
    // 非同期実行の結果を取得
    int result = f.get();
    std::cout << "foo() = " << result << std::endl;
  }

  std::cout << std::endl;

  // 関数fを遅延状態で非同期実行
  {
    // この段階では関数foo()を実行しない
    std::cout << "invokes std::async(std::launch::deferred, foo)" << std::endl;
    std::future<int> f = std::async(std::launch::deferred, foo);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "main thread: slept for 10 msec\n";

    // 非同期実行の結果を取得
    // この段階で関数foo()を実行
    int result = f.get();
    std::cout << "foo() = " << result << std::endl;
  }
  return 0;
}
