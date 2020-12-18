# [future](https://cpprefjp.github.io/reference/future/future.html)と[promise](https://cpprefjp.github.io/reference/future/promise.html)

>futureは、「別スレッドでの処理完了を待ち、その処理結果を取得する」といった非同期処理を実現するためのクラスであり、promiseクラスと組み合わせて使用する。  
>promiseが別スレッドでの処理結果を書き込み、futureがその結果を読み取る。promiseとfutureは内部的に同一の共有状態を参照する。これによってスレッド間での値の受け渡しやスレッド間同期を実現する。  
>このクラスはR&およびvoidの、2つの特殊化を持つ。

## future/promiseの基本
[futureとpromiseのあれこれ（理論編）](https://yohhoy.hatenadiary.jp/entry/20120131/p1)より  

両者ともに標準ヘッダ <future> にて定義されるクラステンプレートであり、「別スレッドでの処理完了を待ち、その処理結果を取得する」といった非同期処理を実現するための部品。

* 処理結果として、通常の戻り値(value)または例外(exception)を扱う。戻り値の型はテンプレート引数にて指定するが、例外は任意の型を扱うことができる。（例: int型を扱うならstd::future<int>, std::promise<int>を用いる。例外はstd::exception_ptrを利用するため任意の型を伝搬可能。）
* future は計算処理の完了待ち（同期機構）と結果取り出し（通信チャネル）機能を提供する。
* promise は計算処理の結果設定（通信チャネル）と完了通知（同期機構）機能を提供する。
* futureオブジェクトは、promiseオブジェクトのget_futureメンバ関数呼び出しにて作成する。
* future, promiseオブジェクトともにコピー不可／ムーブ可能。

**futureは待ち＆受け取り、promiseは結果のセット＆通知**

サンプルコード

``` cpp
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
```