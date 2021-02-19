# fffrenderer
造轮子之软渲染器。

这个项目让你自己动手一步步实现一个基于CPU的软件渲染器，可以通过编码过程学习 OpenGL, DirectX, Vulkan 等图形API库是怎么做的，相当于自己写了个图形API库。

## 编译项目
本项目全程使用 C++ 编写，使用 CMake 构建。

### Windows
推荐的工作环境：编译器 MinGW-GCC ，构建脚本 CMake 。

1. 安装 MinGW
2. 安装 CMake
3. 安装 VSCode 的 CMake 插件
4. VSCode Ctrl+Shift+P 使用 `CMake: Clean Rebuild` 构建
5. VSCode Ctrl+Shift+P 使用 `CMake: Debug` 调试代码

### Linux
推荐的工作环境：编译器 GCC ，构建脚本 CMake 。

1. 安装 GCC GDB 等一系列开发工具
2. 安装 CMake
3. 安装 VSCode 的 CMake 插件
4. VSCode Ctrl+Shift+P 使用 `CMake: Clean Rebuild` 构建
5. VSCode Ctrl+Shift+P 使用 `CMake: Debug` 调试代码

## 贡献项目
推荐本地使用 `git rebase` 合并多个提交，尽量保持主干提交记录是干净没有分叉的(Fast-forward)。

```
git rebase -i [startpoint] [endpoint]
// 这里的区间是左开右闭区间
```
