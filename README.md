# cpp
cppの知識

## Setting

VScodeでC++をコンパイルできるようにする
(参考URL)
https://www.freecodecamp.org/japanese/news/how-to-compile-your-c-code-in-visual-studio-code/

1. C++ のコンパイラのダウンロードとインストール
osdn.net/projects/mingw/ にアクセスしてから、「Windows mingw-get-setup.exe」をクリックして MinGW のセットアップファイルをダウンロードしてください。
2. ダウンロードが終わったら、MinGW のインストールを開始して、「MinGW Installation Manager」が表示されるのを待ちます。
3. 「MinGW Installation Manager」が表示されたら、mingw32-gcc-g++ のチェックボックスをクリックしてから、「Mark for Installation」を選んでください。
4. 上部の左端にあるメニューの中の、「Installation > Apply Changes」をクリックしてください。
5. 変更の適用が完了するのを待ちましょう。この処理は必ずインターネット接続が安定している状態で実行してください。
6. C:\MinGW\bin をパスを通す
7. Code Runner 拡張機能を VS Code にインストール
8. gdb をインストール  
https://code.visualstudio.com/docs/languages/cpp  
https://www.msys2.org/  
https://blog.websandbag.com/entry/2022/10/01/033811
```
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
9. MinGW がそろっているか確認
```
gcc --version
g++ --version
gdb --version
```

## Compile & Run
Code Runner を使ってコードを実行
```
Ctrl+Alt+N
# ※EverNoteが起動してしまうので、閉じておく。
```
もしくはF1 で Run Code を実行

実行中のコードを停止するには
```
Ctrl+Alt+M
```
