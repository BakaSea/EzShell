# EzShell

<!-- TOC -->

- [EzShell](#ezshell)
  - [**基本命令**](#%e5%9f%ba%e6%9c%ac%e5%91%bd%e4%bb%a4)
    - [**cat**](#cat)
    - [**cd**](#cd)
    - [**cmp**](#cmp)
    - [**cp**](#cp)
    - [**echo**](#echo)
    - [**install**](#install)
    - [**ls**](#ls)
    - [**man**](#man)
    - [**mkdir**](#mkdir)
    - [**pwd**](#pwd)
    - [**rm**](#rm)
    - [**rmdir**](#rmdir)
    - [**touch**](#touch)
    - [**uninstall**](#uninstall)
    - [**wc**](#wc)
  - [**执行.sh文件**](#%e6%89%a7%e8%a1%8csh%e6%96%87%e4%bb%b6)
  - [**向EzShell添加你自己的命令**](#%e5%90%91ezshell%e6%b7%bb%e5%8a%a0%e4%bd%a0%e8%87%aa%e5%b7%b1%e7%9a%84%e5%91%bd%e4%bb%a4)
    - [**运用EzShell API编写你自己的命令**](#%e8%bf%90%e7%94%a8ezshell-api%e7%bc%96%e5%86%99%e4%bd%a0%e8%87%aa%e5%b7%b1%e7%9a%84%e5%91%bd%e4%bb%a4)
    - [**在EzShell中安装你的自己命令**](#%e5%9c%a8ezshell%e4%b8%ad%e5%ae%89%e8%a3%85%e4%bd%a0%e7%9a%84%e8%87%aa%e5%b7%b1%e5%91%bd%e4%bb%a4)
    - [**例子-在EzShell中添加print命令**](#%e4%be%8b%e5%ad%90-%e5%9c%a8ezshell%e4%b8%ad%e6%b7%bb%e5%8a%a0print%e5%91%bd%e4%bb%a4)

<!-- /TOC -->

## **基本命令**

### **cat**
将文件内容显示到控制台
* 用法
    > cat [参数]... 文件...
* 支持的参数  
    -b, --number-nonblank: 显示行编号（空行不编号）  
    -E, --show-ends: 在每行末尾加"$"  
    -n, --number: 显示行编号  
    -s, --squeeze-blank: 删掉重复的空行  
    --help: 查看帮助

### **cd**
更改当前工作路径
* 用法
    > cd 路径

### **cmp**
一个个字节地比较两个文件的不同
* 用法
    > cmp [参数]... 文件1 文件2
* 支持的参数  
    -b, --print-bytes: 显示不同的字节  
    -l, --verbose: 显示所有不同之处  
    --help: 查看帮助

### **cp**
复制文件  
* 用法
    > cp [参数]... 源文件 目标文件  
    > cp [参数]... 文件... 文件夹
* 支持的参数  
    -i, --interactive: 在复制前询问是否覆盖  
    -R, -r, --recursive: 将文件夹内所有文件即文件夹一起复制  
    --help: 查看帮助

### **echo**
显示字符串内容
* 用法
    > echo [字符串]...

### **install**
安装一个用EzShell API编写的命令
* 用法
    > input 命令 命令文件
* 支持的参数  
    --help: 查看帮助

### **ls**
列出文件夹内容
* 用法
    > ls [参数]... [文件]...
* 支持的参数  
    -a, --all: 不忽略以"."开头的文件  
    -A， --almost-all: 不列出"."和".."  
    -l: 用一个清单列出所有内容  
    -r, --reverse: 反转顺序  
    -t: 以修改时间来排序，最新的最先  
    --help: 查看帮助

### **man**
查看命令的帮助文档
* 用法
    > man 命令
* 支持的参数  
    --help: 查看帮助

### **mkdir**
创建文件夹
* 用法
    > mkdir 文件夹...
* 支持的参数  
    --help: 查看帮助

### **pwd**
输出当前工作路径
* 用法
    > pwd
* 支持的参数  
    --help: 查看帮助

### **rm**
删除文件或文件夹
* 用法
    > rm [参数]... 文件...
* 支持的参数  
    -i: 删除前询问是否删除  
    -r, -R, --recursive: 删除文件夹及其所有内容  
    --help: 查看帮助

### **rmdir**
删除空文件夹
* 用法
    > rmdir [参数]... 文件夹...
* 支持的参数  
    -p, --parents: 删除文件夹和他的父级文件夹  
    --help: 查看帮助

### **touch**
更改文件的修改时间
* 用法
    > touch 文件...
* 支持的参数  
    --help: 查看帮助

### **uninstall**
卸载用EzShell API编写的命令
* 用法
    > uninstall 命令...
* 支持的参数  
    --help: 查看帮助

### **wc**
统计文件的行数、字数、字节数等
* 用法
    > wc [参数]... 文件...
* 支持的参数  
    -c, --bytes: 统计字节数  
    -m, --chars: 统计字符数  
    -l, --lines: 统计行数  
    -L, --max-line-length: 最长行的行号  
    -w, --words: 统计字数  
    --help: 查看帮助

## **执行.sh文件**
编写你的.sh文件，仅限于以上基本命令，然后在EzShell内输入
> ./xxx.sh  
> sh xxx.sh

即可运行你的.sh文件

## **向EzShell添加你自己的命令**

### **运用EzShell API编写你自己的命令**
EzShell API提供以下文件  
> CommandBase.h  
> CommandBase.cpp  
> DirHelper.h  
> DirHelper.cpp  
> main.cpp  
> makefile

你的命令需要继承CommandBase类，并且重载void run()，再在main.cpp中将command赋为你的命令，最后make成命令程序即可

### **在EzShell中安装你的自己命令**
在EzShell中，输入
> install 你的命令 你的命令程序

完成命令的安装，之后便可在EzShell中使用你自己的命令了

### **例子-在EzShell中添加print命令**
* 运用EzShell API编写print  
    print实现以下功能  
    有参数-b时输出"success! 1"  
    无参数时输出"success! 2"  

CommandPRINT.h:
```cpp
#ifndef COMMANDPRINT_H
#define COMMANDPRINT_H
#include "CommandBase.h"
#include "DirHelper.h"

class CommandPRINT : public CommandBase {
public:
    CommandPRINT(string str, DirHelper *dirHelper);
    ~CommandPRINT();
    void run();
private:
    bool _b;
};

#endif
```
CommandPRINT.cpp:
```cpp
#include "CommandPRINT.h"

CommandPRINT::CommandPRINT(string str, DirHelper *dirHelper) : CommandBase("print", str, dirHelper) {
    mapOpt["b"] = &_b;
    help = "Hello!\n";
}

CommandPRINT::~CommandPRINT() {

}

void CommandPRINT::run() {
    _b = false;
    if (!analyzeOpt()) return;
    if (_b) cout << "success! 1" << endl;
    else cout << "success! 2" << endl;
}
```
main.cpp:
```cpp
#include "DirHelper.h"
#include "CommandBase.h"
#include "CommandPRINT.h"

int main(int argc, char *argv[]) {
    if (argc < 3) return -1;
    DirHelper *dirHelper = new DirHelper();
    dirHelper->setPath(argv[2]);
    CommandBase *command = NULL;
    command = new CommandPRINT(argv[1], dirHelper);
    if (command != NULL) command->run();
    return 0;
}
```
makefile:
```makefile
main:main.o DirHelper.h DirHelper.o CommandBase.h CommandBase.o CommandPRINT.h CommandPRINT.o
	g++ main.o DirHelper.h DirHelper.o CommandBase.h CommandBase.o CommandPRINT.h CommandPRINT.o -o print
main.o:main.cpp
	g++ -c main.cpp
DirHelper.o:DirHelper.cpp
	g++ -c DirHelper.cpp
CommandBase.o:CommandBase.cpp
	g++ -c CommandBase.cpp
CommandPRINT.o:CommandPRINT.cpp
	g++ -c CommandPRINT.cpp

clean:
	rm *.o
```
* 在EzShell中安装print  
    在EzShell中输入
    > install print print

    到这里，你就可以使用print了