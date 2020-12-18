# [ラムダ式(Lambda)](https://cpprefjp.github.io/lang/cpp11/lambda_expressions.html)

参考URL
[C++ のラムダ式](https://c.keicode.com/cpp/cpp-lambda.php)  
関数を作るまでもない処理を記述したいときに便利

``` cpp
#include <iostream>
using namespace std;

int main() {

  auto f = []() {
    cout << "Hello, world!" << endl;
  };

  f();
}
```

## キャプチャリスト

ラムダ式の [ ] には キャプチャリスト を記述できます。次の例ではラムダ式を定義している時点の変数 i の値をキャプチャしています。このため、その後に i の値を書き換えてもラムダ式に取り込まれた値は変わりません。

``` cpp
#include <iostream>
using namespace std;

int main() {

  int i = 123;

  auto f = [i]() {
    cout << "f(): i = " << i << endl;
  };

  f();

  i = 999; // <-ここで値が変わってもfには影響しない

  f();
}
```

[ラムダ・キャプチャーの理解](https://www.xlsoft.com/jp/products/intel/compilers/ccl/12/ug/cref_cls/common/cppref_lambda_lambdacapt.htm)  
|シンボル|意味|
|---|---|
|[]|キャプチャーなし: 上位レベルの参照はエラーです。|
|[&x, y, ...]|指定どおりにキャプチャー: & プリフィックスが付加されている識別子は、参照でキャプチャーされます。その他の識別子は、コピーによってキャプチャーされます。明示的にリストされていない変数への上位レベルの参照はエラーです。|
|[&]|参照でキャプチャー: 上位レベルの参照は暗黙的に変数を参照でキャプチャーします。|
|[=]|コピーでキャプチャー: 上位レベルの参照は暗黙的に変数をコピーでキャプチャーします。|
|[&, x, y, ...]|参照でキャプチャー (例外あり): リストされた変数は、値/コピー (リストされていない変数は & プリフィックスが付加されています) でキャプチャーされます。|
|[=, &x, &y, ...]|コピーでキャプチャー (例外あり): リストされた変数は、参照でのみキャプチャーされます (リストされた変数にはすべて & プリフィックスが付加されていなければなりません)。|

サンプル

``` cpp
void f()
{
  int x = 3;

  // この時点で見える自動変数を参照でキャプチャし、
  // 参照した変数xを書き換える
  auto f = [&] { x = 1; };

  // 個別にキャプチャ方法を指定する場合は、
  // 以下のように、&の次に変数名を指定する
  // auto f = [&x] { x = 1; };

  f(); // x == 1
}

void g()
{
  int x = 3;

  // この時点で見える自動変数をコピーでキャプチャし、
  // コピーした変数xをラムダ式内で使用する
  auto f = [=] { return x + 1; };

  // 個別にキャプチャ方法を指定する場合は、
  // 以下のように、変数名を指定する
  // auto f = [x] { return x + 1; };

  int result = f(); // result == 4
}
```


## 引数と返値

``` cpp
#include <iostream>
using namespace std;

int main() {
  auto f = [](int i, int j) -> int {
    return i * j;
  };

  cout << f(2, 3) << endl; // <- 6が返ってくる
}
```