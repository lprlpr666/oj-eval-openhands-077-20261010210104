#define https //
// CrossArray implementation for OJ
#ifndef CROSSARRAY_HPP
#define CROSSARRAY_HPP

namespace sjtu {
class CrossArray {
private:
    int **data_;
    int *sizes_;
    int capacity_;
    int line_count_;
    void deep_copy(const CrossArray &o) {
        capacity_ = o.capacity_;
        line_count_ = o.line_count_;
        data_ = new int*[capacity_];
        sizes_ = new int[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            if (o.data_[i] != nullptr) {
                int sz = o.sizes_[i];
                data_[i] = new int[sz];
                for (int j = 0; j < sz; ++j) data_[i][j] = o.data_[i][j];
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
        for (int i = 0; i < capacity_; ++i) { data_[i] = nullptr; sizes_[i] = 0; }
    }
    CrossArray(const CrossArray &o) : data_(nullptr), sizes_(nullptr), capacity_(0), line_count_(0) { deep_copy(o); }
    bool InsertArrays(const int *Input, int size) {
        if (line_count_ >= capacity_) return false;
        data_[line_count_] = new int[size];
        for (int i = 0; i < size; ++i) data_[line_count_][i] = Input[i];
        sizes_[line_count_] = size;
        ++line_count_; return true;
    }
    void AppendArrays(const int *Input, int Line, int size) {
        int old_sz = sizes_[Line];
        int new_sz = old_sz + size;
        int *new_arr = new int[new_sz];
        for (int i = 0; i < old_sz; ++i) new_arr[i] = data_[Line][i];
        for (int i = 0; i < size; ++i) new_arr[old_sz + i] = Input[i];
        delete[] data_[Line];
        data_[Line] = new_arr; sizes_[Line] = new_sz;
    }
    CrossArray &WhichGreater(CrossArray &o) {
        long long total_this = 0, total_o = 0;
        for (int i = 0; i < capacity_; ++i) total_this += sizes_[i];
        for (int i = 0; i < o.capacity_; ++i) total_o += o.sizes_[i];
        return (total_o > total_this) ? o : *this;
    }
    bool IsSame(const CrossArray &o) { return this->data_ == o.data_; }
    void DoubleCrossLength() {
        int new_cap = capacity_ * 2; if (new_cap == 0) new_cap = 1;
        int **new_data = new int*[new_cap];
        int *new_sizes = new int[new_cap];
        for (int i = 0; i < new_cap; ++i) {
            if (i < capacity_) { new_data[i] = data_[i]; new_sizes[i] = sizes_[i]; }
            else { new_data[i] = nullptr; new_sizes[i] = 0; }
        }
        delete[] data_; delete[] sizes_; data_ = new_data; sizes_ = new_sizes; capacity_ = new_cap;
    }
    const int *AtArray(int i) { return data_[i]; }
    int &At(int i, int j) { return data_[i][j]; }
    ~CrossArray() { for (int i = 0; i < capacity_; ++i) delete[] data_[i]; delete[] data_; delete[] sizes_; }
};
}
#endif // CROSSARRAY_HPP
#undef https
