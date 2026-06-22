# c-

一个基于 C++ 和 EasyX 的课程实训项目，主题参考《最强大脑》第十二季中的数字谜题玩法，并加入了场景切换、平台跳跃、闯关积分和排行榜功能。

## 项目简介

项目使用 Visual Studio C++ 工程组织代码，整体采用简单的场景管理结构。

- 主菜单：进入游戏或退出游戏
- 行走场景：控制角色在平台之间移动，通过传送门进入关卡
- 数字谜题关卡：完成 5x5 区域填数字玩法
- 自定义/扩展关卡场景：包含额外谜题与玩法页面
- 排行榜：记录分数和用时，数据保存在 `rank.txt`

## 技术栈

- C++
- EasyX 图形库
- Visual Studio 2022 工程文件
- Windows x64

## 目录结构

- [实训.sln](/mnt/d/product/实训/实训.sln)：Visual Studio 解决方案
- [实训](/mnt/d/product/实训/实训)：核心源码与资源目录
- [实训/resources](/mnt/d/product/实训/实训/resources)：图片、字体等运行资源
- [x64/Release/实训.exe](/mnt/d/product/实训/x64/Release/实训.exe)：现成的 Release 可执行文件
- [run.bat](/mnt/d/product/实训/run.bat)：一键启动脚本

## 运行方式

推荐直接使用仓库里现成的 Release 程序。

### 方式一：一键启动

在项目根目录双击 [run.bat](/mnt/d/product/实训/run.bat)。

这个脚本会自动切换到正确的工作目录后再启动程序，避免资源文件加载失败。

### 方式二：命令行启动

在 Windows 命令行中执行：

```bat
cd /d D:\product\实训\实训
..\x64\Release\实训.exe
```

不要直接在错误目录下双击 `实训.exe`，因为程序通过相对路径读取 `resources` 目录下的图片和字体资源。

## 编译方式

如果需要从源码重新编译，建议使用 Visual Studio 2022。

### 环境要求

- Windows
- Visual Studio 2022
- 安装 C++ 桌面开发工具链
- 安装或配置 EasyX

### 编译步骤

1. 用 Visual Studio 打开 [实训.sln](/mnt/d/product/实训/实训.sln)
2. 选择 `Release | x64`
3. 确认项目工作目录为 `$(ProjectDir)`
4. 执行生成并运行

如果机器上没有完整的 Visual Studio C++ 构建工具链，`MSBuild` 会缺少 `Microsoft.Cpp.Default.props`，此时无法从源码重新编译。

## 基本玩法

- 在主菜单点击 `Start` 进入游戏
- 在行走场景中控制角色移动和跳跃
- 通过不同传送门进入数字谜题关卡
- 谜题完成后可获得分数并返回主场景
- 按 `Tab` 可进入排行榜场景

## 说明

- 排行榜数据保存在 [实训/rank.txt](/mnt/d/product/实训/实训/rank.txt)
- 项目资源较多，运行时请保持 `resources` 目录完整
- 当前仓库已忽略 `.vs`、`x64` 中间文件和常见 Visual Studio 构建产物
