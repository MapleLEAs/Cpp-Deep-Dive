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
| vector | ✅ | 动态数组，含扩容策略 + 移动语义 |
| list | ✅ | 双向链表，哨兵节点设计 |
| deque | ✅ | 分段连续存储，中控器 + 多缓冲区 |
| stack | ✅ | 栈适配器，默认基于 deque |
| queue | ✅ | 队列适配器，默认基于 deque |
| shared_ptr | ✅ | 共享智能指针，原子引用计数 |
| weak_ptr | ✅ | 弱指针，打破循环引用 |
| rb_tree | ✅ | 红黑树，插入修复 + 迭代器 |
| set | ✅ | 有序集合，封装 rb_tree |
| map | ✅ | 有序映射，封装 rb_tree + operator[] |
| hashtable | ✅ | 哈希表底层，拉链法 + 质数桶扩容 |
| unordered_set | ✅ | 哈希集合，封装 hashtable |
| unordered_map | ✅ | 哈希映射，封装 hashtable + operator[] |
| algorithm | ✅ | find/count/copy/fill/reverse + 二分查找 + 堆操作 |
| memory_pool | ✅ | 固定块内存池，allocate/deallocate O(1) |

## 技术栈

![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B)

- C++17 模板元编程、RAII、移动语义
- 迭代器模式、标签分派（tag dispatch）
- 空间配置器、placement new
- 异常安全、Rule of Five
- 红黑树插入修复（变色+旋转）
- 哈希表拉链法 + 质数扩容
- 原子引用计数、循环引用打破
- 内省排序、二分查找、堆操作
- 固定块内存池

## 项目结构
Cpp-Deep-Dive/
├── include/maple/
│ ├── util.hpp # pair + move + forward + swap
│ ├── type_traits.hpp # 类型判断 + 类型转换 + enable_if
│ ├── iterator.hpp # 迭代器标签 + traits + advance/distance
│ ├── allocator.hpp # 内存分配器
│ ├── construct.hpp # construct/destroy + 平凡优化
│ ├── uninitialized.hpp # 未初始化内存批量操作
│ ├── vector.hpp # vector 动态数组
│ ├── list.hpp / list_node.hpp # list 双向链表
│ ├── deque.hpp # deque 双端队列
│ ├── stack.hpp # stack 栈
│ ├── queue.hpp # queue 队列
│ ├── shared_ptr.hpp # shared_ptr 共享智能指针
│ ├── weak_ptr.hpp # weak_ptr 弱智能指针
│ ├── rb_tree.hpp # rb_tree 红黑树
│ ├── set.hpp # set 有序集合
│ ├── map.hpp # map 有序映射
│ ├── hashtable.hpp # hashtable 哈希表
│ ├── unordered_set.hpp # unordered_set 哈希集合
│ ├── unordered_map.hpp # unordered_map 哈希映射
│ ├── algorithm.hpp # 算法库
│ └── memory_pool.hpp # memory_pool 内存池
├── tests/ # 14 个测试文件，100+ 测试项
├── docs/
│ └── debug-vector-capacity.md # 扩容策略 bug 记录
├── CMakeLists.txt
└── README.md


## 快速开始

```bash
# 编译所有测试
mkdir build && cd build
cmake ..
make

# 运行单个测试
./test_vector
./test_list
./test_deque
./test_rb_tree
./test_algorithm
./test_shared_ptr
...