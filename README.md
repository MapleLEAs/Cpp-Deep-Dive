# Cpp-Deep-Dive

从零复刻 STL 核心组件，深挖 C++17 对象模型与内存管理机制。

## 已完成模块

| 模块 | 状态 | 核心知识点 |
|------|------|-----------|
| util | ✅ | pair + move + forward + swap |
| type_traits | ✅ | 15 个类型判断 + enable_if + 引用/const 移除 |
| iterator | ✅ | 5 种迭代器标签 + iterator_traits + advance/distance |
| allocator | ✅ | 内存分配/释放 + construct/destroy + 平凡类型优化 |
| uninitialized | ✅ | 批量拷贝/填充 + 异常安全回滚 |
| vector | ✅ | 完整动态数组，14 项测试全部通过 |
| list | ⬜ | 双向链表 |
| deque | ⬜ | 双端队列 |
| RBTree | ⬜ | 红黑树底层 |
| set/map | ⬜ | 关联容器 |
| shared_ptr | ⬜ | 原子引用计数 + 线程安全 |
| MemoryPool | ⬜ | 固定块内存池 |

## 技术栈

![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B)
![CMake](https://img.shields.io/badge/Build-CMake-green?logo=cmake)

- C++17 模板元编程、RAII、移动语义
- 迭代器模式、标签分派
- 空间配置器、placement new
- 异常安全、Rule of Five

## 快速开始

```bash
mkdir build && cd build
cmake ..
make
./test_vector