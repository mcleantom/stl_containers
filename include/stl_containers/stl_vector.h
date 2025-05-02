#pragma once

#include <utility>

namespace tom {

template<typename T>
class vector {
public:
    vector()
        : size_(0)
        , reserved_(0)
        , items_(nullptr)
    {}

    vector(size_t n)
        : size_(n)
        , reserved_(n)
        , items_(new T[n])
    {
        for (size_t i=0; i<size_; ++i) {
            items_[i] = T();
        }
    }

    vector(size_t n, const T& default_value)
        : size_(n)
        , reserved_(n)
        , items_(new T[n])
    {
        for (size_t i=0; i < size_; ++i) {
            items_[i] = default_value;
        }
    }

    ~vector() { delete[] items_; }

    // Copy constructor
    vector(const vector& other)
        : size_(other.size_)
        , reserved_(other.reserved_)
        , items_(new T[other.reserved_])
    {
        for (size_t i=0; i<size_; ++i) {
            items_[i] = other.items_[i];
        }
    }
    
    vector(vector&& other)
        : size_(other.size_)
        , reserved_(other.reserved_)
        , items_(other.items_)
    {
        other.items_ = nullptr;
        other.size_ = 0;
        other.reserved_ = 0;
    }

    vector& operator=(vector& other) noexcept
    {
        if (this != &other) {
            delete[] items_;
            items_ = std::exchange(other.items_, nullptr);
            size_ = std::exchange(other.size_, 0);
            reserved_ = std::exchange(other.reserved_, 0);
        }
        return *this;
    }

    vector& operator=(vector&& other) noexcept {
        if (this != &other) {
            delete[] items_;
            items_ = std::exchange(other.items_, nullptr);
            size_ = std::exchange(other.size_, 0);
            reserved_ = std::exchange(other.reserved_, 0);
        }
        return *this;
    }

    T& operator[](size_t i)
    {
        return items_[i];
    }

    const T& operator[](size_t i) const 
    { 
        return items_[i]; 
    }
    
    size_t size() const 
    { 
        return size_; 
    }
    size_t capacity() const 
    { 
        return reserved_; 
    }

    void push_back(const T& value) {
        if (size_ >= reserved_) {
            size_t new_capacity = reserved_ == 0 ? 1 : reserved_ * 2;
            reserve(new_capacity);
        }

        items_[size_] = value;
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ >= reserved_) {
            size_t new_capacity = reserved_ == 0 ? 1 : reserved_ * 2;
            reserve(new_capacity);
        }
        items_[size_] = std::move(value);
        ++size_;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= reserved_) {
            return;
        }

        T* new_items = new T[new_capacity];
        for (size_t i=0; i<size_; ++i) {
            new_items[i] = std::move(items_[i]);
        }

        delete[] items_;
        items_ = new_items;
        reserved_ = new_capacity;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= reserved_) {
            size_t new_capacity = reserved_ == 0 ? 1 : reserved_ * 2;
            reserve(new_capacity);
        }
        // Placement new takes in the address of already allocated memory
        new (&items_[size_]) T(std::forward<Args>(args)...);
        ++size_;
    }

    void resize(size_t count) {
        if (count < size_) {
            for (size_t i=count; i<size_; ++i) {
                items_[i].~T();
            }
        } else {
            if (count > reserved_) {
                reserve(count);
            }
            for (size_t i=size_; i<count; ++i) {
                new (&items_[i]) T();
            }
        }
        size_ = count;
    }

    void resize(size_t count, const T& value) {
        if (count < size_) {
            for (size_t i=count; i<size_; ++i) {
                items_[i].~T();
            }
        } else {
            if (count > reserved_) {
                reserve(count);
            }
            for (size_t i=size_; i<count; ++i) {
                new (&items_[i]) T(value);
            }
        }
        size_ = count;
    }

    void clear() {
        for (size_t i=0; i<size_; ++i) {
            items_[i].~T();
        }
        size_ = 0;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            items_[size_].~T();
        }
    }

    T& front() { return items_[0]; }
    T& back() { return items_[size_ - 1]; }

    T* begin() { return items_; }
    T* end() { return items_ + size_; }
    const T* begin() const { return items_; }
    const T* end() const { return items_ + size_; }
private:
    size_t size_;
    size_t reserved_;
    T* items_;
};

}