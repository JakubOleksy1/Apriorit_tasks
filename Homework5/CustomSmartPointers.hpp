#ifndef CUSTOM_SMART_POINTERS_HPP
#define CUSTOM_SMART_POINTERS_HPP

#include <windows.h>
#include <memory>
#include <iostream>

class HandleGuard {
public:
    explicit HandleGuard(HANDLE handle) : handle_(handle) {}
    ~HandleGuard() {
        if (handle_ != INVALID_HANDLE_VALUE) {
            CloseHandle(handle_);
        }
    }
    HANDLE get() const { return handle_; }
private:
    HANDLE handle_;
};

struct SocketDeleter1 {
    void operator()(SOCKET* socket) const {
        if (socket && *socket != INVALID_SOCKET) {
            closesocket(*socket);
            delete socket;
        }
    }
};

struct SocketDeleter2 {
    void operator()(SOCKET socket) const {
        if (socket != INVALID_SOCKET) {
            closesocket(socket);
        }
    }
};

struct SocketDeleter3 {
    void operator()(SOCKET* socket) const {
        if (socket) {
            closesocket(*socket);
            delete socket;
        }
    }
};

template <typename Resource>
class SharedPtr;

template <typename Resource>
class WeakPtr;

template <typename Resource>
class SharedPtr {
public:
    SharedPtr() : resource_(nullptr), ref_count_(new long(1)), weak_count_(new long(0)) {}
    explicit SharedPtr(Resource* res) : resource_(res), ref_count_(new long(1)), weak_count_(new long(0)) {}
    SharedPtr(const SharedPtr<Resource>& rhs) : resource_(rhs.resource_), ref_count_(rhs.ref_count_), weak_count_(rhs.weak_count_) {
        ++(*ref_count_);
    }
    SharedPtr(const WeakPtr<Resource>& rhs);
    SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs) {
        if (this != &rhs) {
            release();
            resource_ = rhs.resource_;
            ref_count_ = rhs.ref_count_;
            weak_count_ = rhs.weak_count_;
            ++(*ref_count_);
        }
        return *this;
    }
    ~SharedPtr() {
        release();
    }

    void Reset() {
        release();
        resource_ = nullptr;
        ref_count_ = new long(1);
        weak_count_ = new long(0);
    }
    void Reset(Resource* res) {
        release();
        resource_ = res;
        ref_count_ = new long(1);
        weak_count_ = new long(0);
    }
    void Swap(SharedPtr<Resource>& rhs) {
        std::swap(resource_, rhs.resource_);
        std::swap(ref_count_, rhs.ref_count_);
        std::swap(weak_count_, rhs.weak_count_);
    }

    Resource* Get() const { return resource_; }
    Resource& operator*() const { return *resource_; }
    Resource* operator->() const { return resource_; }
    long UseCount() const { return *ref_count_; }

private:
    void release() {
        if (--(*ref_count_) == 0) {
            delete resource_;
            delete ref_count_;
            if (*weak_count_ == 0) {
                delete weak_count_;
            }
        }
    }

    Resource* resource_;
    long* ref_count_;
    long* weak_count_;

    friend class WeakPtr<Resource>;
};

template <typename Resource>
class WeakPtr {
public:
    WeakPtr() : resource_(nullptr), ref_count_(nullptr), weak_count_(new long(1)) {}
    WeakPtr(const WeakPtr<Resource>& rhs) : resource_(rhs.resource_), ref_count_(rhs.ref_count_), weak_count_(rhs.weak_count_) {
        ++(*weak_count_);
    }
    WeakPtr(const SharedPtr<Resource>& rhs) : resource_(rhs.resource_), ref_count_(rhs.ref_count_), weak_count_(rhs.weak_count_) {
        ++(*weak_count_);
    }
    WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs) {
        if (this != &rhs) {
            release();
            resource_ = rhs.resource_;
            ref_count_ = rhs.ref_count_;
            weak_count_ = rhs.weak_count_;
            ++(*weak_count_);
        }
        return *this;
    }
    WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs) {
        release();
        resource_ = rhs.resource_;
        ref_count_ = rhs.ref_count_;
        weak_count_ = rhs.weak_count_;
        ++(*weak_count_);
        return *this;
    }
    ~WeakPtr() {
        release();
    }

    void Reset() {
        release();
        resource_ = nullptr;
        ref_count_ = nullptr;
        weak_count_ = new long(1);
    }
    void Swap(WeakPtr<Resource>& rhs) {
        std::swap(resource_, rhs.resource_);
        std::swap(ref_count_, rhs.ref_count_);
        std::swap(weak_count_, rhs.weak_count_);
    }
    long UseCount() const { return ref_count_ ? *ref_count_ : 0; }
    bool Expired() const { return !ref_count_ || *ref_count_ == 0; }
    SharedPtr<Resource> Lock() const {
        return Expired() ? SharedPtr<Resource>() : SharedPtr<Resource>(*this);
    }

private:
    void release() {
        if (--(*weak_count_) == 0) {
            delete weak_count_;
        }
    }

    Resource* resource_;
    long* ref_count_;
    long* weak_count_;

    friend class SharedPtr<Resource>;
};

template <typename Resource>
SharedPtr<Resource>::SharedPtr(const WeakPtr<Resource>& rhs) : resource_(rhs.resource_), ref_count_(rhs.ref_count_), weak_count_(rhs.weak_count_) {
    ++(*ref_count_);
}

#endif // CUSTOM_SMART_POINTERS_HPP
