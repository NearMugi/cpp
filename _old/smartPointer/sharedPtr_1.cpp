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
