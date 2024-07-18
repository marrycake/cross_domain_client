#ifndef ARRAYSCOPE_H
#define ARRAYSCOPE_H

#include <memory>

template <typename T>
class ArrayScope
{
public:
    ArrayScope(unsigned int len) : mArray(std::make_unique<T[]>(len)), mLen(len){};
    ArrayScope() = delete;
    ~ArrayScope() = default;
    ArrayScope(ArrayScope &other) = delete;
    ArrayScope &operator=(ArrayScope &other) = delete;
    ArrayScope(ArrayScope &&other) noexcept
        : mArray(std::move(other.mArray)), mLen(other.mLen)
    {
        other.mLen = 0; // 迁移后清零其他对象的长度
    };
    ArrayScope &operator=(ArrayScope &&other) noexcept
    {
        if (this != &other)
        {
            mArray = std::move(other.mArray); // 转移unique_ptr的所有权
            mLen = other.mLen;                // 转移长度
            other.mLen = 0;                   // 迁移后清零其他对象的长度
        }
        return *this;
    };
    unsigned int size() const
    {
        return mLen;
    };
    const T *constData() const
    {
        return mArray.get();
    };
    T *data() const
    {
        return mArray.get();
    }

private:
    std::unique_ptr<T[]> mArray;
    unsigned int mLen;
};

template <typename T>
ArrayScope<T> makeArrayScope(unsigned int size)
{
    ArrayScope<T> array(size);
}

#endif // ARRAYSCOPE_H