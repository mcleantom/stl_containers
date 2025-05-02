#pragma once
#include <utility>

namespace tom {

template<class T>
class unique_ptr {
public:
    unique_ptr() noexcept
        : ptr_(nullptr) {}
    explicit unique_ptr(T* ptr) noexcept
        : ptr_(ptr)
    {}
    ~unique_ptr() {
        delete ptr_;
        ptr_ = nullptr;
    }

    // Move constructor
    unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    // Move assignment
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Delete copy constructor as unique pointers can only have one owner
    unique_ptr(const unique_ptr&) = delete;
    // Delete copy assignment as unique pointers can only have one owner
    unique_ptr& operator=(const unique_ptr&) = delete;

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    T* get() const noexcept { return ptr_; }

    T* release() noexcept {
        return std::exchange(ptr_, nullptr);
    }
    
    void reset(T* ptr = nullptr) noexcept {
        delete ptr_;
        ptr_ = ptr;
    }

    void swap(unique_ptr& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }
private:
    T* ptr_;
};

template<class T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    T* tmp = new T(std::forward<Args>(args)...);
    return unique_ptr(tmp);
}

}