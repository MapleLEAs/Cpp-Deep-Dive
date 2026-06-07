#ifndef MAPLE_SHARED_PTR_HPP
#define MAPLE_SHARED_PTR_HPP

#include <cstddef>
#include <atomic>
#include "maple/util.hpp"

namespace maple {

template <typename T> class weak_ptr;  // Ç°ÏòÉùÃ÷

template <typename T>
class shared_ptr {
public:
    shared_ptr() : ptr_(nullptr), ref_count_(nullptr) {}

    explicit shared_ptr(T* p) : ptr_(p), ref_count_(new std::atomic<size_t>(1)) {}

    shared_ptr(const shared_ptr& other)
        : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) ref_count_->fetch_add(1);
    }

    shared_ptr(shared_ptr&& other) noexcept
        : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    ~shared_ptr() { release(); }

    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (ref_count_) ref_count_->fetch_add(1);
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    T& operator*()  const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get()        const { return ptr_; }

    size_t use_count() const {
        return ref_count_ ? ref_count_->load() : 0;
    }

    bool unique() const { return use_count() == 1; }
    void reset() { release(); }

    std::atomic<size_t>* ref_count_ptr() const { return ref_count_; }

    bool operator==(const shared_ptr& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const shared_ptr& other) const { return ptr_ != other.ptr_; }

    friend class weak_ptr<T>;

private:
    T* ptr_;
    std::atomic<size_t>* ref_count_;

    shared_ptr(const weak_ptr<T>& wp)
        : ptr_(wp.ptr_), ref_count_(wp.ref_count_) {
        if (ref_count_) ref_count_->fetch_add(1);
    }

    void release() {
        if (ref_count_) {
            if (ref_count_->fetch_sub(1) == 1) {
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = nullptr;
            ref_count_ = nullptr;
        }
    }
};

} // namespace maple

#endif
