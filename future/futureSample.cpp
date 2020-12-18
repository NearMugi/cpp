#include <iostream>
#include <future>
#include <thread>
#include <utility>

void calc(std::promise<int> p, int cnt)
{
  int sum = 0;
  for (int i = 0; i < cnt; ++i) {
    sum += i + 1;
  }

  p.set_value(sum); // 結果値を書き込む
}

int main()
{
  std::promise<int> p;
  std::future<int> f = p.get_future();

  // 別スレッドで計算を行う
  std::thread t(calc, std::move(p), 10);

  // calc()によって書き込まれた結果を取得
  std::cout << f.get() << std::endl;

  t.join();
}
