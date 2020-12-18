# [std::async](https://cpprefjp.github.io/reference/future/async.html)

>関数を非同期実行する。  
>この関数は、指定された関数を非同期実行し、結果値を取得するための**futureオブジェクト**を返す。  
>返されたfutureオブジェクトのget()もしくはwait()を呼び出すことにより、非同期実行の完了を待機する。  

asyncとfutureを組み合わせる

サンプル  
[C++で簡単非同期処理(std::thread,std::async)](https://qiita.com/termoshtt/items/d3cb7fe226cdd498d2ef)

``` cpp
auto result = std::async(std::launch::async, [] { return long_calc(); });
do_another_things();
std::cout << result.get() << std::endl;
```

> resultの型はstd::future<T>(Tはlong_calc()の戻り値の型)である。  
> result.get()ではじめて作成したスレッドをjoin()するので、  
> do_another_things()はthreadの生成直後に(long_calc()の実行を待たずに)実行される。

## std::asyncのPolicy

* std::launch::async : 別スレッドで実行
* std::launch::deferred : 遅延評価
* std::launch::async | std::launch::deferred : 上記のいずれか（実装依存）
* 指定なし : 両方指定した場合と同様

std::launch::deferredを指定した場合は単に遅延評価になる。  
つまり最初にresult.get()が呼ばれたタイミングでlong_calc()を評価する。  
次回以降にresult.get()が呼ばれたら最初の時に計算した値を返す。  

## 戻り値の指定有無で動作が変わる

``` cpp
//これらの呼び出しは別スレッドで実行されるが、同期的に呼び出される
std::async(std::launch::async, []{ f(); }); //f()が完了するまではこの行で待機する
std::async(std::launch::async, []{ g(); }); //g()の呼び出しは必ずf()の終了後、g()の完了まで処理はブロックされる

//次の様に戻り値を受けておけば、それぞれ非同期的に実行される
{
  auto futuref = std::async(std::launch::async, []{ f(); }); //f()の完了を待機しない
  auto futureg = std::async(std::launch::async, []{ g(); }); //g()の呼び出しはf()の完了前かもしれない

  /*何か他の処理*/

} //このブロックスコープを抜ける際に、f()とg()の完了を待機する
```
