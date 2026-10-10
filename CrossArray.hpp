// CrossArray.hpp
// Implementation of CrossArray class as per problem statement
// No external libraries are used; only raw pointers and manual memory management.

#ifndef CROSSARRAY_HPP
#define CROSSARRAY_HPP

namespace sjtu {
class CrossArray {
private:
    int **data_;          // array of pointers to each line's int array
    int *sizes_;          // size of each line (number of elements), 0 if nullptr
    int capacity_;        // maximum number of lines (size of data_ array)
    int line_count_;      // number of lines that have been inserted (non-nullptr)

    // Helper to copy data from another CrossArray (deep copy)
    void deep_copy(const CrossArray &o) {
        capacity_ = o.capacity_;
        line_count_ = o.line_count_;
        data_ = new int*[capacity_];
        sizes_ = new int[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            if (o.data_[i] != nullptr) {
                int sz = o.sizes_[i];
                data_[i] = new int[sz];
                for (int j = 0; j < sz; ++j) {
                    data_[i][j] = o.data_[i][j];
                }
                sizes_[i] = sz;
            } else {
                data_[i] = nullptr;
                sizes_[i] = 0;
            }
        }
    }

public:
    explicit CrossArray(int lines) : data_(nullptr), sizes_(nullptr), capacity_(lines), line_count_(0) {
        if (lines < 0) lines = 0;
        data_ = new int*[capacity_];
        sizes_ = new int[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            data_[i] = nullptr;
            sizes_[i] = 0;
        }
    }

    // Copy constructor (deep copy)
    CrossArray(const CrossArray &o) : data_(nullptr), sizes_(nullptr), capacity_(0), line_count_(0) {
        deep_copy(o);
    }

    // Insert a new array; returns false if capacity exceeded
    bool InsertArrays(const int *Input, int size) {
        if (line_count_ >= capacity_) return false;
        // allocate new line at index line_count_
        data_[line_count_] = new int[size];
        for (int i = 0; i < size; ++i) {
            data_[line_count_][i] = Input[i];
        }
        sizes_[line_count_] = size;
        ++line_count_;
        return true;
    }

    // Append to an existing line (Line is 0‑based index)
    void AppendArrays(const int *Input, int Line, int size) {
        // Assume Line is valid and already inserted
        int old_sz = sizes_[Line];
        int new_sz = old_sz + size;
        int *new_arr = new int[new_sz];
        // copy old elements
        for (int i = 0; i < old_sz; ++i) {
            new_arr[i] = data_[Line][i];
        }
        // copy appended elements
        for (int i = 0; i < size; ++i) {
            new_arr[old_sz + i] = Input[i];
        }
        delete[] data_[Line];
        data_[Line] = new_arr;
        sizes_[Line] = new_sz;
    }

    // Return reference to the larger CrossArray (by total element count)
    CrossArray &WhichGreater(CrossArray &o) {
        long long total_this = 0, total_o = 0;
        for (int i = 0; i < capacity_; ++i) {
            total_this += sizes_[i];
        }
        for (int i = 0; i < o.capacity_; ++i) {
            total_o += o.sizes_[i];
        }
        if (total_o > total_this) return o;
        return *this; // also when equal
    }

    // Check if two CrossArray objects share the same underlying storage
    bool IsSame(const CrossArray &o) {
        return this->data_ == o.data_;
    }

    // Double the capacity (lines) while preserving existing data
    void DoubleCrossLength() {
        int new_cap = capacity_ * 2;
        if (new_cap == 0) new_cap = 1; // handle zero case
        int **new_data = new int*[new_cap];
        int *new_sizes = new int[new_cap];
        for (int i = 0; i < new_cap; ++i) {
            if (i < capacity_) {
                new_data[i] = data_[i];
                new_sizes[i] = sizes_[i];
            } else {
                new_data[i] = nullptr;
                new_sizes[i] = 0;
            }
        }
        delete[] data_;
        delete[] sizes_;
        data_ = new_data;
        sizes_ = new_sizes;
        capacity_ = new_cap;
        // line_count_ remains unchanged (it counts inserted lines)
    }

    // Return pointer to the array at index i (or nullptr)
    const int *AtArray(int i) {
        // i is guaranteed to be valid (0 <= i < capacity_)
        return data_[i];
    }

    // Return reference to element at (i, j)
    int &At(int i, int j) {
        // i and j are guaranteed valid
        return data_[i][j];
    }

    // Destructor
    ~CrossArray() {
        for (int i = 0; i < capacity_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        delete[] sizes_;
    }
};
} // namespace sjtu

#endif // CROSSARRAY_HPP
