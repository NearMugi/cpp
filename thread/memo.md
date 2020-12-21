# Threadについて学ぶ

参考URL  
[C/C++によるマルチスレッドプログラミング入門](https://qiita.com/nsnonsugar/items/be8a066c6627ab5b052a)  
[C++11における同期処理(std::mutex, std::unique_guard, std::lock_guard, std::condition_variable)](https://qiita.com/termoshtt/items/c01745ea4bcc89d37edc)

## threadを使う

g++でコンパイル時に-lpthreadをつける

``` g++
g++ thread1.cpp -lpthread
```

イメージ

``` cpp
#include <thread>

void ThreadA()
{
　// ...
}

void ThreadB()
{
　// ...
}

int main()
{
    std::thread th_a(ThreadA);　//スレッドをセット
    std::thread th_b(ThreadB);

    th_a.join(); //ThreadAが終わるまでここで待つ
    th_b.join(); //ThreadBが終わるまでここで待つ

    return 0;
}

```

|API|用途|
|---|---|
|join|スレッド動作完了待ち、スレッドの開放|
|detach|スレッドを生成したプロセスの管理対象から外す (スレッドを生成したプロセスが終了してもdetachされたスレッドはterminateされずに最後まで動き続ける)|
|get_id|スレッド固有のIDを取得|
|hardware_concurrency|H/WでサポートされているCPUスレッド数を取得|
|joinable|コンテキストがスレッドと関連付けられているならtrue、そうでなければfalseを返す|
|native_handle|プラットフォーム依存のスレッドハンドルを取得 (Unix系はpthread_t, WindowsはHANDLEのインスタンスを返す)|
|swap|std::threadをスワップ|



## 同じ変数を編集するときは排他制御にする

[std::mutex](https://cpprefjp.github.io/reference/mutex/mutex.html)  

>mutexは、スレッド間で使用する共有リソースを排他制御するためのクラスである。lock()メンバ関数によってリソースのロックを取得し、unlock()メンバ関数でリソースのロックを手放す。
>
>このクラスのデストラクタは自動的にunlock()メンバ関数を呼び出すことはないため、通常このクラスのメンバ関数は直接は呼び出さず、**lock_guard**や**unique_lock**といったロック管理クラスと併用する。

[std::lock_guard](https://cpprefjp.github.io/reference/mutex/lock_guard.html)  
|名前|説明|対応バージョン|
|-|-|-|
|(constructor)|コンストラクタ|C++11|
|(destructor)|デストラクタ|C++11|
|operator=(const lock_guard&) = delete|代入演算子|C++11|

[std::unique_lock](https://cpprefjp.github.io/reference/mutex/unique_lock.html)  
こっちのほうが高機能  

|名前|説明|対応バージョン|
|-|-|-|
|(constructor)|コンストラクタ|C++11|
|(destructor)|デストラクタ|C++11|
|operator=|代入演算子|C++11|
|lock|ロックを取得する|C++11|
|try_lock|ロックの取得を試みる|C++11|
|try_lock_for|タイムアウトする相対時間を指定してロックの取得を試みる|C++11|
|try_lock_until|タイムアウトする絶対時間を指定してロックの取得を試みる|C++11|
|unlock|ロックを手放す|C++11|
|swap|他のunique_lockオブジェクトと値を入れ替える|C++11|
|release|ミューテックスの所有権を放棄する|C++11|
|owns_lock|ロックを取得しているかを判定する|C++11|
|operator bool|ロックを取得しているかを判定する|C++11|
|mutex|所有しているミューテックスオブジェクトを取得する|C++11|

``` cpp
#include <mutex>
std::mutex mtx_; // 排他制御用ミューテックス
uint32_t count_;

void add_count()
{
    // count_を加算する前にミューテックスを取得する
    // "lock"はインスタンス名なので何でもよい。
    std::lock_guard<std::mutex> lock(mtx_);
    ++count_;
}
```

## 同期させる

std::mutexとstd::condition_variableを組み合わせる  
別のスレッドが終わるまで待機する

[std::condition_variable](https://cpprefjp.github.io/reference/condition_variable/condition_variable.html)  
>condition_variableは、特定のイベントもしくは条件を満たすまでスレッドの実行を待機するためのクラスである。  
>**wait()／wait_for()／wait_until()を使用してスレッドを待機させ、notify_one()／notify_all()によって待機しているスレッドを起床させる。**  
>condition_variableはcondition_variable_anyと違い、ロック型として**unique_lock<mutex>のみ**をサポートしている。これは、処理系にcondition_variableクラスに最も効率の良い実装を許可するためである。
>（例：POSIXスレッド環境においてはcondition_variableがpthread_cond_tの、mutexがpthread_mutex_tの単純なラッパクラスとして実装されうる）  

[std::condition_variable::wait](https://cpprefjp.github.io/reference/condition_variable/condition_variable/wait.htm)

> 起床されるまで待機する。  
> この関数は、処理をするための準備ができたことをnotify_one()/notify_all()によって通知されるまでスレッドを待機するために使用する。  
> 述語を指定しない場合、notify_one()/notify_all()が呼び出された時点でこの関数のブロッキングが解除される。  
> 述語を指定する場合、述語呼び出しがtrueになるまで待機を続行する。

``` cpp
template <class Predicate>
void wait(unique_lock<mutex>& lock, Predicate pred);

// 記述例
// 述語を指定しているので、述語の呼び出しがTrueになる(is_ready = True)まで待つ
std::unique_lock<std::mutex> lk(mtx_);
cond_.wait(lk, [this] { return is_ready; });
```

なぜis_readyがいるの？？？　-> 確実にwait状態を解除するため  
[C++11における同期処理(std::mutex, std::unique_guard, std::lock_guard, std::condition_variable)](https://qiita.com/termoshtt/items/c01745ea4bcc89d37edc)より
> ここで問題なのは、何故is_ready変数が必要なのかという事だ。  
> do_preparing_process()はcv.notify_one()によって準備が終了した事を通知している筈である。  
> という事はis_readyなんて変数は必要ないのではないか？と思える。  
> 
> これは大抵のライブラリがwait()状態から処理を再開する際に、  
> notify_one()あるいは他の通知を受けとった事を保証していないからである。  
> つまりどのスレッドも通知を条件変数に送っていないのにwait()状態が解除される事がある。  
> これをspurious wakeupと呼ぶ。日本語が確定していないようだが、 見せ掛けの目覚め である。  
> なのでこの場合、準備が確実に終了した事を通知する必要がある。  
> そのために用いているのがis_readyである  

## スレッドの優先度設定

[C++ std::threadの使い方](https://qiita.com/kurun_pan/items/f626e763e74e82a44493)を参照  

>std::threadではスレッドに対する詳細設定が出来ませんので、native_handle()でプラットフォーム固有のスレッドハンドラを取得し、そのプラットフォームに合わせた形で設定する必要があります。ここではUnix系 (Linux, macOS) の例を以下に示します。

``` cpp
int main() {
  auto func = [](std::string message) {
    std::cout << "thread id = " << std::this_thread::get_id() << " " << message << std::endl;
  };
  std::thread th2(func, "Hellow, World!");

  // 優先度を設定
  struct sched_param param;
  param.sched_priority = 0;
  if (pthread_setschedparam(th2.native_handle(), SCHED_OTHER, &param) != 0)
    std::cout << "Priority set Error" << std::endl;

  th2.join();

  return 0;
}
```

## join or detach を確実に処理させる

EffectiveModernC++の項目37「std::threadはすべての場面でjoin不可にする」に記載されている。  
また[C++11で始めるマルチスレッドプログラミングその1 ～std::thread事始め～](https://suikaba.hatenablog.com/entry/2014/08/19/225703)も参照  

>RAIIを用いてjoin()、detach()の呼び出し忘れを防ぐ  
>先に述べたとおり、threadは必ずjoin()またはdetach()が呼び出されなければなりません。しかし直にjoin()やdetach()を呼び出すコードは、例外機構との相性が悪いです。例えば、以下のコードではjoinが呼び出されない可能性があります。

``` cpp
std::thread t([] { /*...*/ });
some_process(); // 例外が投げられうる
t.join();       // some_processで例外が投げられると呼び出されない
```

>これを防ぐために、RAIIを用いてjoin()やdetach()を呼び出す仕組みがあります。以下のthread_guardがその一例です*1が、他にもBoostのscoped_guardなどがあるので、調べてみてください。

つまりデストラクタで確実に処理する
``` cpp
class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t(t_) {}
    ~thread_guard() {
        if(t.joinable()) {
            t.join();
        }
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

int main() {
    std::thread t1([]{ /* ... */ });
    thread_guard tg(t1);
    some_process();
} // 例外が投げられてもjoinが呼ばれる
```
