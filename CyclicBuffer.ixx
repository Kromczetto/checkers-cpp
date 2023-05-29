export module CyclicBufferModule;
import<iostream>;

export template <typename T, int buffer_size>
 class CyclicBuffer {
    T buffer [buffer_size];
    int head;
    int tail;
    int count;

public:
    CyclicBuffer() : head(0), tail(0), count(0) {}
    CyclicBuffer(const CyclicBuffer<T, buffer_size>& o) : head(o.head), tail(o.tail), count(o.count) {}
    CyclicBuffer(CyclicBuffer<T, buffer_size>&& o) : head(o.head), tail(o.tail), count(o.count) {}
    T push(T value) {
        T returnValue;
        if (count == buffer_size) {
            returnValue = buffer[head];
            tail = (tail + 1) % buffer_size;
        }
        else {
            returnValue = (T)-1;
            count++;
        }
        buffer[head] = value;
        head = (head + 1) % buffer_size;
        return returnValue;
    }

    T pop() {
        if (count == 0) {
            std::cout << "Buffer is empty" << std::endl;
            return T();
        }
        T value = buffer[tail];
        tail = (tail + 1) % buffer_size;
        count--;
        return value;
    }
    int size() {
        return buffer_size;
    }
};