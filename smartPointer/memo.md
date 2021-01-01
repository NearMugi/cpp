# スマートポインタ 
[参考URL]  
[C++11スマートポインタ入門](https://qiita.com/hmito/items/db3b14917120b285112f)  
[std::unique_ptr](https://cpprefjp.github.io/reference/memory/unique_ptr.html)  
[std::unique_ptr::reset](https://cpprefjp.github.io/reference/memory/unique_ptr/reset.html)  
[std::make_shared](https://cpprefjp.github.io/reference/memory/make_shared.html)  
  
**※下記の内容は[C++11スマートポインタ入門](https://qiita.com/hmito/items/db3b14917120b285112f)を参照したもの。**

## 概要
C++11では、unique_ptr<T> shared_ptr<T> weak_ptr<T>の3種のスマートポインタが新たに追加された。  
これらのスマートポインタは、いずれもメモリの動的確保の利用の際に生じる多くの危険性を低減する目的で使用されるが、それぞれ独自の考え方と機能を持っている。  
3種のスマートポインタを適切に使い分けることで、安全性と開発速度の向上が見込めるだけでなく、プログラマの意図に合わせて「ポインタ」を記述し分けることができる、非常に強力なツールとなる。

## 導入
スマートポインタには、一般にメモリの 所有権 という考え方がある。これは「そのメモリにアクセスする権利と、解放する義務」のことである。簡単に言ってしまうと、所有権を保持するとは「そのメモリは俺が管理するから、俺から使え & 勝手に消すな」という意味である。  
  
確保したメモリをスマートポインタに渡すと、スマートポインタはそのメモリに対する所有権を得る。所有権を保持している間は、そのスマートポインタを介してメモリにアクセス可能であり、解放されることはない。  
所有権を持つスマートポインタが全て破棄されれば、そのメモリは誰からも使用されていないことが保障できる。そこで、スマートポインタは ディストラクタを用いて所有権を持つメモリが不要となる瞬間を判断し、解放を自動的に行う。生成されたオブジェクトは、破棄される際に（わずかな例外を除いて）必ずディストラクタが呼ばれるので、メモリの解放忘れを避けることができる。  
C++11以降では auto_ptr<T>の使用は非推奨となっており、代わりとして後述する新たな3種のスマートポインタが追加された。このため、C++11以降が使える環境下では、 auto_ptr<T>を使用してはいけない。仮に使わざるを得ない場合にも、使用には細心の注意を要する。  

## unique_ptr
unique_ptr<T>は、あるメモリに対する所有権を持つポインタが、ただ一つであることを保証するようなスマートポインタである。  

- あるメモリの所有権を持つ unique_ptr<T>は、 ただ一つのみである。
- コピーが出来ない。代わりに、C++11で新たに追加されたムーブによって、所有権を移動することができる。
- 通常のポインタに匹敵する処理速度。
- 配列を扱うことができる。
- deleter（後述）を指定することができる。  

``` cpp
#include <iostream> 
#include <memory> 
class hoge 
{ 
  public: 
    hoge(int v):value(v) { std::cout << "hoge::hoge() constractor" << std::endl;
    ~hoge() { std::cout << "hoge::hoge() distractor" << std::endl; } 
    int v() const {return value;} 
  private: 
    int value; 
}; 
int main() 
{ 
  // リソースを設定する 
  std::unique_ptr<hoge> p0(new hoge(10)); 
  std::cout << p0->v() << std::endl; 
  // 所有権をp1に移動させる 
  std::unique_ptr<hoge> p1(std::move(p0)); 
  std::cout << p1->v() << std::endl; 
  // reset関数を使ってリソースを開放する 
  std::cout << "reset!" << std::endl; 
  p1.reset(); 
  // 再設定 
  p1.reset(new hoge(99)); 
  std::cout << p1->v() << std::endl; 
  return 0; 
};
```

所有権を実際に保持しているかの判定には、 operator bool()を使う。所有権を持つ場合にはtrue、持たない場合にはfalseを返す。  

``` cpp
std::unique_ptr<int> ptr;
//メモリの所有権を保持しているかどうかは、boolの文脈で使用することで判定できる
//所有していれば、trueを返す
if(ptr){
   //---所有しているときの処理---
}

//bool変数への代入でも、所有権の有無を取得可能
bool CanAccess=ptr;
```

ポインタの保持するメモリにアクセスするには、通常のポインタ同様に operator*()や operator->()が使用できる  

``` cpp
std::unique_ptr<std::string> pStr(new std::string("test"));

//operator*()でstring型を参照
// "test" と表示される
std::cout<<*pStr<<std::endl;        

//operator->()で、string型のsize関数を呼び出せる
unsigned int StrSize = pStr->size();  
```

生のポインタが欲しいときには、get()か release()を使う。 get()は生ポインタを得るだけで、ポインタの所有権は unique_ptr<T>が保持し続ける。 release()はポインタの所有権自体も放棄するため、メモリの解放は自分で行う必要がある。  
``` cpp
//通常のポインタがほしい時には、get関数を使う。
//ポインタの所有権はunique_ptrが保持し続ける
int* pint;
pint = ptr.get();

//所有権自体を放棄する場合は、release関数を使う
//この場合、メモリの解放自体は自分で行う必要がある
pint = ptr.release();
delete pint; 
```

unique_ptr<T>では、第二テンプレート引数に指定することで、deleterを指定することができる。  
※deleterとは、このようなメモリ解放時の処理を指定する、関数オブジェクトのことである。  
deleterを明示的に指定してやれば、 new以外の方法で確保したメモリや、あるいはメモリ以外のリソースについても、 unique_ptr<T>を用いて管理することができる。

``` cpp
#include<memory>
#include"memory_from_storage.hpp"
//free_int_from_storageを使ってメモリを解放する関数オブジェクトを定義する。
struct deleter_for_storage{
   void operator()(int* ptr_){
      free_int_from_sotrage(ptr_);
   }
};
int main(){
   //テンプレート第二引数で、deleterを指定する
   std::unique_ptr<int, deleter_for_storage> ptr(malloc_int_from_storage());

   //deleteではなく、free_int_from_storageがメモリ解放の際に呼ばれる。
   return 0;
}
```

## shared_ptr  
あるメモリの所有権を持つ unique_ptr<T>がただ一つに限られていたのに対し、同一のメモリの所有権を複数で共有できるようにしたスマートポインタが、shared_ptr<T>である。  
  
具体的には、次のような仕組みである。 shared_ptr<T>は、所有権を持つポインタの数を記録するカウンタを持っている。所有権を持つ shared_ptr<T>がコピーされると、内部でカウンタがインクリメントされ、ディストラクタや明示的解放時にデクリメントされる。全ての所有者がいなくなると、カウンタがゼロとなり、メモリが解放される。カウンタで所有者数を管理することで、複数の shared_ptr<T>が所有権を保持していても、適切なタイミングで一度だけメモリ解放が実行されるのである。  
- あるメモリの所有権を、複数の shared_ptr<T>で 共有することができる。メモリの解放は、全ての所有権を持つ shared_ptr<T>が破棄された際に実行される。
- コピーもムーブも可能。
- 内部でカウンタを利用している関係上、やや通常のポインタよりメモリ確保やコピー等の処理が遅い。
- 配列を扱うことができる。ただし、明示的にdeleterを指定する必要がある。

``` cpp
#include <memory>
#include <iostream>
int main()
{
  // 空のshared_ptrを作成
  std::shared_ptr<int> ptr;

  {
    // intの所有権を持つptr2を作成
    std::shared_ptr<int> ptr2(new int(0));

    // ptr2の所有権をptrにコピー、共有する
    ptr = ptr2;

    *ptr += 10;
    *ptr2 += 5;

    // オブジェクトを共有しているのでどちらも"15"になる
    std::cout << "ptr  : " << *ptr << std::endl;
    std::cout << "ptr2 : " << *ptr2 << std::endl;
  }  // ここでptr2のディストラクタが呼ばれる

  // 所有者が唯一であるか確認する
  if(ptr.unique())
  {
    std::cout << "ptr.unique is true " << std::endl;
  };

  // make_sharedを使ってメモリ確保
  // こちらのほうが効率よく確保できる
  std::shared_ptr<int> ptr3 = std::make_shared<int>(100);
  std::cout << "ptr3 : " << *ptr3 << std::endl;


  // コピーコンストラクタ、コピー代入演算子が使える
  std::shared_ptr<int> ptr4(ptr3);
  std::shared_ptr<int> ptr5;
  ptr5 =  ptr3;
  std::cout << "ptr4 : " << *ptr4 << std::endl;
  std::cout << "ptr5 : " << *ptr5 << std::endl;

  // 所有者の数を確認
  std::cout << "ptr3 count : " << ptr3.use_count() << std::endl;

  // moveも可
  // その場合は所有権を失う
  std::shared_ptr<int> ptr6;
  ptr6 = std::move(ptr5);
  std::cout << "ptr6 : " << *ptr6 << std::endl;
  if(!ptr5)
  {
    std::cout << "ptr5 is empty" << std::endl;
  };

  // 所有者の数を確認
  std::cout << "ptr3 count : " << ptr3.use_count() << std::endl;

  return 0;
};
```

- shared_ptr<T>もunique_ptr<T>同様にコンストラクタで指定するか、 reset(pointer)を使うことでメモリの所有権を委ねる事ができる。ただ、 shared_ptr<T>は所有するメモリだけでなく自身のカウンタも動的にメモリを確保する必要があるため、これらのメモリ確保を同時に行える make_shared<T>(args...)を使って作成した方が処理効率が良い。可能な限りこちらを使うべきである。  
- shared_ptr<T>は、コピー、ムーブともに使用することができる。  
- unique_ptr<T>からムーブすることも可能。この時、もちろん unique_ptr<T>は所有権を失う。  
- 所有権の放棄は、ディストラクタや reset(pointer)で行われる。ただし、実際にメモリが解放されるのは、そのメモリの所有権を持つポインタが全て破棄された場合である。
- 所有権を実際に保持しているかの判定には、 operator bool()を使う。所有権を持つ場合にはtrue、持たない場合にはfalseを返す。また、 use_count()を使って自身が保持するメモリに所有権を持つポインタの数を、 unique()を使って自身が保持するメモリに所有権を持つポインタが唯一（自分だけ）かどうかを、調べることができる。
- ポインタの保持するメモリにアクセスするには、通常のポインタ同様に operator*()や operator->()が使用できる。
- 生のポインタが欲しいときには、get()を用いる。 unique_ptr<T>と違って、複数のポインタが所有権を保持しているので、 所有権のみを放棄するrelease()は用意されていない。

## shared_ptrで発生する循環参照の問題  

``` cpp
// shared_ptrの循環参照の例
#include <iostream>
#include <memory>

class hoge
{
  public:
    hoge() { std::cout << "constractor" << std::endl; }
    ~hoge() { std::cout << "distractor" << std::endl; }

    std::shared_ptr<hoge> ptr;
};

int main()
{
  std::shared_ptr<hoge> p1 = std::make_shared<hoge>();
  std::shared_ptr<hoge> p2 = std::make_shared<hoge>();

  // p1のメンバ変数でp2を確保する
  p1->ptr = p2;
  // p2のメンバ変数でp1を確保する
  p2->ptr = p1;

  return 0;

}; // p1,p2のデストラクタが発生しない
```

ディストラクタが呼ばれる直前、Hoge1はp1とHoge2.ptrが、Hoge2はp2とHoge1.ptrがそれぞれ所有権を持っている。  
まず、pHoge1のディストラクタが呼ばれると、Hoge1への所有権を放棄する。しかし、この時Hoge2.ptrはHoge1への所有権を保持しているので、Hoge1のディストラクタは呼ばれない。  

次に、p2のディストラクタが呼ばれると、Hoge2への所有権を放棄する。  
しかし、先ほど同様、Hoge2はHoge1.ptrも所有権を保持しているので、Hoge2のディストラクタは呼ばれない。  
結果として、shared_ptrが最初に所有権を委ねられたHoge1, Hoge2は、最後まで解放されないままになってしまう。  

## weak_ptrを使って回避する

weak_ptr<T>は、循環参照によって生じる問題を防ぐために導入されたスマートポインタである。先の二つのスマートポインタと違い、 weak_ptr<T>は メモリへの所有権を持つことはない。その代わりに、 weak_ptr<T>は shared_ptr<T>の指すメモリを参照することができる。

``` cpp
// shared_ptrの循環参照を回避する
#include <iostream>
#include <memory>

class hoge
{
  public:
    hoge() { std::cout << "constractor" << std::endl; }
    ~hoge() { std::cout << "distractor" << std::endl; }

    // weak_ptrを使うことで、所有権を持たないようにする
    // shared_ptrの指すメモリは参照できる
    std::weak_ptr<hoge> ptr;
};

int main()
{
  std::shared_ptr<hoge> p1 = std::make_shared<hoge>();
  std::shared_ptr<hoge> p2 = std::make_shared<hoge>();

  // p1のメンバ変数でp2を確保する
  p1->ptr = p2;
  // p2のメンバ変数でp1を確保する
  p2->ptr = p1;

  //参照先のメモリが解放されていないかどうかはexpired関数を使う
  if(p1->ptr.expired()){
     std::cout<<"expired"<<std::endl;
  } else {
     std::cout<<"not expired"<<std::endl;
  }


  return 0;

}; // p1,p2のデストラクタは発生する
```

- weak_ptr<T>はshared_ptr<T>が所有権を持つメモリしか管理できない。
- weak_ptr<T>は、コピー、ムーブともに使用することができる。
- 参照の解放は、ディストラクタや reset()を使う。
- 所有権はそもそも保持していないので、 operator bool()は使えない。参照先が解放されていないかどうかは、 expired()を使う。戻り値がtrueならすでに解放されている。また、 use_count()を使って参照先のメモリに所有権を持つ shared_ptr<T>の数を調べることができる。
- 参照するメモリにアクセスするのに、 operator*()や operator->()は使えない。メモリにアクセスするためには、まず lock()によって参照先を保持する shared_ptr<T>を取得し、そこからアクセスする。これは、使用中に解放されてしまうのを避けるためである。

``` cpp
std::shared_ptr<int> sptr=std::make_shared<int>(10);
std::weak_ptr<int> wptr(sptr);
{
   //lock関数によって、参照先を保持するshared_ptrを取得する
   std::shared_ptr<int> ptr=wptr.lock();
}
```

## 生のポインタと3つのスマートポインタの使い分け

### ポインタの利用方法における二つの側面

一つ目は、ポインタの指す対象を 「所有」しているのか、単に 「参照」しているのか、である。  
所有している、すなわち自身が解放する責任を有する動的確保したメモリを指すためにポインタを使っているのであれば、それは「所有」のポインタである。  
一方、単にアクセスするためだけにしか使わないのであれば、それは「参照」である。
一般に、あるオブジェクトを「所有」するのは単一のオブジェクトであるが、まれに 複数のオブジェクトが単一のオブジェクトを「所有」するのが自然である場合もある。例えば、複数のperson(人物)で構成されるcommittee(委員会)クラスを考えた場合、committeeはpersonを「所有」するのは自然な設計である。しかし、あるpersonが複数のcommitteeに参加する場合には、複数のcommitteeによって所有権は共有されることになる。

二つ目は、ポインタの指す対象へのアクセスが、アクセス中に解放されることのない 「安全なアクセス」か、解放される可能性がある 「危険なアクセス」か、である。  
自身が所有するポインタへのアクセスや、所有者より内側のスコープで利用している場合は、基本的に「安全なアクセス」だといえる。一方で、アクセスしようとするメモリが、いつ解放されるか分からない他のオブジェクトが所有権を持つ場合、その利用は「危険なアクセス」であるといえる。

### 使い分ける指針
これら二つの側面から、ポインタの使い方をいくつかに分類することができる。  
あくまで一つの指針としてであるが、以下のような基準で使い分けるとよいのではないか、と筆者は考えている。

1. メモリを動的確保によって「所有」する必要がある場合、原則として unique_ptr<T>を利用する。  
ただし、メモリへのアクセスは所有者のメンバ関数内に限るなど、「危険なアクセス」による「参照」が必要ない設計にしておく。
2. メモリを動的確保によって「所有」するが、以下のいずれかの場合には shared_ptr<T>を利用する。  
複数のオブジェクトによって「所有」されるのが、最も自然な設計である場合。「危険なアクセス」による「参照」が、設計上どうしても必要な場合。
3. 「危険なアクセス」による「参照」には、weak_ptr<T>を利用する。
4. 「安全なアクセス」による「参照」か、外部のAPIの利用する際にどうしても必要である場合に限り、生のポインタを使ってよい。それ以外では原則として生ポインタを使ってはいけない。



