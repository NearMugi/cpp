#include <thread>
#include <future>

void func(std::promise<double> p, double x)
{
  try {
    double ret = /* 何らかの計算 */;
    p.set_value(ret);  // (2a) promiseに戻り値を設定
  } catch (...) {
    p.set_exception(std::current_exception());  // (2b) promiseに例外を設定
  }
}

int main()
{
  std::promise<double> p;
  std::future<double> f = p.get_future();

  double x = 3.14159;
  std::thread th(func, std::move(p), x);  // (1) 別スレッドで関数funcを実行

  /* 自スレッドでの処理 */;

  try {
    double result = f.get();  // (3a) promiseに設定された値を取得（別スレッドでの処理完了を待機）
  } catch (...) {
    // (3b) promiseに設定された例外が再throwされる
  }

  th.join();  // (4) 別スレッドの完了待ち
  // future/promiseによって既に必要な同期はとられているが、thread::join()を呼ばずに
  // thオブジェクトのデストラクタが呼ばれると、std::terminate()が呼び出されてしまう。
  return 0;
}
