# Template

## 型の抽象化(Abstraction of types)

ファイル名 : abstraction_of_types.h  

print関数の引数にint型や文字列、Vector型を指定できる。  
オーバーロードのように扱える。

## 型の制約(Constraints on types)

ファイル名 : constraints_on_types.h  

std::is_integral_v<T>やstd::is_same_v<T, std::string> で型を判定している。  
「想定通りの型である場合処理を行う。」といった使い方と思われる。  


## テンプレートパラメータの継承(Inheritance of template parameters)

ファイル名 : inheritance_of_template_parameters.h  

インスタンスを生成する際に、クラスの持つメモリ変数の型を指定できる。  
用途が思いつかない。

## テンプレートクラスのインスタンス化(Instantiation of template classes)

