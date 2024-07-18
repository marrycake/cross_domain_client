#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include <memory>
template <typename T>
class ArrayBuffer
{
public:
    ArrayBuffer() : mBuffer(nullptr), mIndex(0), mLen(0), mDestroyResponsibility(false)
    {
    }
    ArrayBuffer(T *buffer, int len) : mBuffer(buffer), mIndex(0), mLen(len), mDestroyResponsibility(false)
    {
    }

    ~ArrayBuffer()
    {
        if (mDestroyResponsibility)
        {
            delete[] mBuffer;
        }
    }

    ArrayBuffer(const ArrayBuffer &other) = delete;
    ArrayBuffer &operator=(const ArrayBuffer &other) = delete;

    ArrayBuffer(ArrayBuffer &&other) : mBuffer(other.mBuffer), mIndex(other.mIndex), mLen(other.mLen), mDestroyResponsibility(other.mDestroyResponsibility)
    {
        other.mBuffer = nullptr;
        other.mIndex = 0;
        other.mLen = 0;
        other.mDestroyResponsibility = false;
    }

    ArrayBuffer &operator=(ArrayBuffer &&other)
    {
        if (this == &other)
            return *this;

        if (mDestroyResponsibility)
        {
            delete[] mBuffer;
        }

        this->mBuffer = other.mBuffer;
        this->mIndex = other.mIndex;
        this->mLen = other.mLen;
        this->mDestroyResponsibility = other.mDestroyResponsibility;

        other.mBuffer = nullptr;
        other.mIndex = 0;
        other.mLen = 0;
        other.mDestroyResponsibility = false;
        return *this;
    }

    static ArrayBuffer<T> allocate(int capacity)
    {
        T *data = new T[capacity];
        return ArrayBuffer<T>(data, 0, capacity, true);
    }

    void get(T *res, int len)
    {
        memcpy(res, mBuffer + mIndex, len * sizeof(T));
        mIndex += len;
    }

    T get()
    {
        return mBuffer[mIndex++];
    }

    void put(T data)
    {
        mBuffer[mIndex++] = data;
    }

    void put(T *src, int len)
    {
        memcpy(mBuffer + mIndex, src, len * sizeof(T));
        mIndex += len;
    }

    /**
     * Absolute <i>put</i> method&nbsp;&nbsp;<i>(optional operation)</i>.
     *
     * <p> Writes the given byte into this buffer at the given
     * index. </p>
     *
     * @param  index
     *         The index at which the byte will be written
     *
     * @param  b
     *         The byte value to be written
     *
     * @return  This buffer
     *
     * @throws  IndexOutOfBoundsException
     *          If <tt>index</tt> is negative
     *          or not smaller than the buffer's limit
     *
     * @throws  ReadOnlyBufferException
     *          If this buffer is read-only
     */
    void put(int index, T data)
    {
        mBuffer[index] = data;
    }

    void position(int position)
    {
        this->mIndex = position;
    }

    int position()
    {
        return this->mIndex;
    }

private:
    ArrayBuffer(T *buffer, int index, int len, bool destroyResponsibility) : mBuffer(buffer), mIndex(index), mLen(len), mDestroyResponsibility(destroyResponsibility) {}

    T *mBuffer;
    int mIndex;
    int mLen;
    bool mDestroyResponsibility;
};

#endif // ARRAYBUFFER_H