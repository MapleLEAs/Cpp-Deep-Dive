# Cpp-Deep-Dive
C++底层原理实战项目，手动复刻STL核心组件，探究C++内存与对象模型。

## 项目模块
1. SmartPtr：手写unique_ptr / shared_ptr / weak_ptr，实现RAII、引用计数、循环引用解决
2. MemoryPool：固定块内存池，模拟简易STL Allocator，优化频繁new/delete开销
3. ObjectModel：探究虚函数虚表、单/多/虚继承内存布局

## 编译方式
CMake + C++17