#ifndef MAPLE_VECTOR_HPP
#define MAPLE_VECTOR_HPP

#include "maple/allocator.hpp"
#include "maple/construct.hpp"
#include "maple/uninitialized.hpp"
#include "maple/iterator.hpp"
#include "maple/util.hpp"

namespace maple {

template <typename T>
class vector {
public:
    using value_type      = T;
    using iterator        = T*;
    using const_iterator  = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = size_t;

    // 构造/析构
    vector() : data_(nullptr), size_(0), capacity_(0) {}

    explicit vector(size_t n, const T& val = T()) {
        data_ = alloc_.allocate(n);
        maple::uninitialized_fill(data_, data_ + n, val);
        size_ = n;
        capacity_ = n;
    }

    ~vector() {
        maple::destroy(data_, data_ + size_);
        alloc_.deallocate(data_, capacity_);
    }

    // 容量
    size_t size()     const { return size_; }
    size_t capacity() const { return capacity_; }
    bool   empty()    const { return size_ == 0; }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) return;

        T* new_data = alloc_.allocate(new_cap);
        maple::uninitialized_copy(data_, data_ + size_, new_data);
        maple::destroy(data_, data_ + size_);

        if (data_) {
            alloc_.deallocate(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_cap;
    }

    // 元素访问 
    T&       operator[](size_t i)       { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }
    T& front() { return data_[0]; }
    T& back()  { return data_[size_ - 1]; }
    T* data()  { return data_; }

    // 迭代器
    iterator       begin()       { return data_; }
    const_iterator begin() const { return data_; }
    iterator       end()         { return data_ + size_; }
    const_iterator end()   const { return data_ + size_; }

    // 修改
    void push_back(const T& val) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        maple::construct(data_ + size_, val);
        ++size_;
    }

    void push_back(T&& val) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        maple::construct(data_ + size_, maple::move(val));
        ++size_;
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        maple::construct(data_ + size_, maple::forward<Args>(args)...);
        ++size_;
    }

    void pop_back() {
        maple::destroy(data_ + size_ - 1);
        --size_;
    }

    iterator insert(iterator pos, const T& val) {
        size_t offset = pos - begin();
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        pos = begin() + offset;

        for (auto it = end(); it > pos; --it) {
            maple::construct(it, maple::move(*(it - 1)));
            maple::destroy(it - 1);
        }
        maple::construct(pos, val);
        ++size_;
        return pos;
    }

    iterator erase(iterator pos) {
        if (pos == end()) return end();

        for (auto it = pos + 1; it != end(); ++it) {
            *(it - 1) = maple::move(*it);
        }
        pop_back();
        return pos;
    }

    void clear() {
        maple::destroy(data_, data_ + size_);
        size_ = 0;
    }

    // 拷贝/移动 
    vector(const vector& other) {
        data_ = alloc_.allocate(other.capacity_);
        maple::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    vector(vector&& other) noexcept
        : data_(other.data_)
        , size_(other.size_)
        , capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    vector& operator=(const vector& other) {
        if (this != &other) {
            maple::destroy(data_, data_ + size_);

            if (capacity_ < other.size_) {
                alloc_.deallocate(data_, capacity_);
                data_ = alloc_.allocate(other.size_);
                capacity_ = other.size_;
            }

            maple::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
            size_ = other.size_;
        }
        return *this;
    }

    vector& operator=(vector&& other) noexcept {
        if (this != &other) {
            maple::destroy(data_, data_ + size_);
            if (data_) alloc_.deallocate(data_, capacity_);

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    void swap(vector& other) noexcept {
        maple::swap(data_, other.data_);
        maple::swap(size_, other.size_);
        maple::swap(capacity_, other.capacity_);
    }

private:
    T*     data_      = nullptr;
    size_t size_      = 0;
    size_t capacity_  = 0;
    allocator<T> alloc_;
};

} // namespace maple

#endif
