# Debug 记录：vector 扩容策略导致堆破坏

## 日期
2026-06-05

## 现象
测试3 `pop_back` 通过，测试4 `clear` 静默退出，无报错。

## 定位过程
1. 单个 `push_back` + `clear` 测试通过，排除 `destroy` 问题
2. 两个 `push_back` + `pop_back` + 析构测试通过
3. 两个 `push_back` 后 `capacity` 仍为 1，发现扩容失效
4. 打印 `capacity` 确认：push_back 两次后 cap=1 而非 2

## 根因
扩容公式 `capacity_ + capacity_ / 2` 在 `capacity_ = 1` 时：
- `1 / 2 = 0`（整数除法）
- `new_cap = 1 + 0 = 1`
- `reserve(1)` 判断 `new_cap <= capacity_`，直接 return
- `construct(data_ + 1, val)` 写入未分配内存，堆被破坏

## 修复
```cpp
// 旧
size_t new_cap = capacity_ == 0 ? 1 : capacity_ + capacity_ / 2;

// 新
size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;