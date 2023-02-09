#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

template <typename T>
class vector2diter {
private:
    static const int chunk_size = (512ULL > sizeof(T) ? 512ULL : sizeof(T)) / sizeof(T);
    typename vector<T*>::iterator chunk_iter;
    T* elem_iter;
public:
    //Ниже надо задать вложенные типы итератора
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T difference_type;
    typedef T& reference;
    typedef T* pointer;
    vector2diter(typename vector<T*>::iterator c_it, T* e_it) : chunk_iter(c_it), elem_iter(e_it) {}

        vector2diter& operator++() {
            //cout<<(*elem_iter)<<'\\';
            if (elem_iter - *chunk_iter == chunk_size-1) {
                chunk_iter++;
                elem_iter =*chunk_iter;
                
        }
            else {
                elem_iter++;
            }
            return *this;
    }
    vector2diter& operator--() {
       // cout << *elem_iter<<'/';
        if (elem_iter == *chunk_iter) {
            chunk_iter--;
            elem_iter =*chunk_iter;
            for (int j = 0; j < chunk_size; j++) {
                elem_iter++;
            }
            
        }
        else {
            elem_iter--;
        }
            return *this;
    }
    T& operator*() { return *elem_iter; };

    friend bool operator==(const vector2diter<T>& a, const vector2diter<T>& b) {
        return a.elem_iter == b.elem_iter;
    }
    friend bool operator!=(const vector2diter<T>& a, const vector2diter<T>& b) {
        return  a.elem_iter!=b.elem_iter;
    }

    vector2diter& operator+=(int k) {
        for (int i = 0; i < k; i++) {
            if (chunk_size - (elem_iter - *chunk_iter + 1) == 0)
            {
                chunk_iter++;
                elem_iter = *chunk_iter;
            }
            else
                elem_iter++;
        }
        return *this;
    }
    vector2diter& operator-=(int k) {
        for (int i = 0; i < k; i++) {
            if (elem_iter == *chunk_iter)
            {
                chunk_iter--;
                elem_iter = *chunk_iter;
                for (int j = 0; j < chunk_size - 1; j++)
                    elem_iter++;
            }
            else
                elem_iter--;
        }
        return *this;
    }
    friend vector2diter operator+(const vector2diter<T>& a, int k) {
        vector2diter<T> other(a);
        return other += k;
    }

    friend bool operator<(const vector2diter<T>& a, const vector2diter<T>& b) {
        return  a.elem_iter < b.elem_iter;
    }
    friend bool operator>(const vector2diter<T>& a, const vector2diter<T>& b) {
        return  a.elem_iter > b.elem_iter;
    }

    friend vector2diter operator-(const vector2diter<T>& a, int k) {
        vector2diter<T> other(a);
        return other -= k;
    }

    friend int operator-(const vector2diter<T>& a, const vector2diter<T>& b) {
        vector2diter<T> other1(a);
        vector2diter<T> other2(b);
        return 1;
    }
};
template <typename T>
class vector2d {
private:
    static const int chunk_size = (512ULL > sizeof(T) ? 512ULL : sizeof(T)) / sizeof(T);
    int n;
    vector<T*> chunks;
public:
    vector2d() : n(0) {
        chunks.push_back(new T[chunk_size]);
    }
    vector2d(int _n, T val = T()) : n(_n) {
        int chunk_count = 1 + n / chunk_size;
        for (int i = 0; i < chunk_count; i++) {
            chunks.push_back(new T[chunk_size]);
                for (int j = 0; j < chunk_size; j++) {
                    chunks[i][j]=val;
                }
        }

    }
    ~vector2d() {
        for (int i = 0; i < chunks.size(); i++) {
            delete[] chunks[i];
        }

    }
    T& operator[](int i) {
        return chunks[i / chunk_size][i % chunk_size];
    }
    int size() {
        return n;
    }
    void resize(int newsize, const T& val = T()) {
        int new_chunk_count = 1 + newsize / chunk_size;
        if (newsize > n){
            int razn =(n%chunk_size);
            for (int i = razn; i < chunk_size; i++) {
                chunks.back()[i] = val;
            }
            for (int i = chunks.size(); i < new_chunk_count; i++) {
                chunks.push_back(new T[chunk_size]);
                for (int j = 0; j < chunk_size; j++) {
                    chunks[i][j] = val;
                }
}
        }
        else if (newsize < n) {
            for (int i = chunks.size()-1; i >= new_chunk_count; i--) {
                chunks.pop_back();
            }
            for (int i = newsize % chunk_size; i < chunk_size; i++) {
                chunks.back()[i] = 0;
            }
        }
            n = newsize;
    }
    void push_back(const T& val) {
        if (n % chunk_size == 0) {
            chunks.push_back(new T[chunk_size]);
            chunks[n/chunk_size][0] = val;
        }
        else {
            chunks[n / chunk_size][n % chunk_size] = val;
        }
        n++;
    }
    void pop_back() {
        if (n % chunk_size == 1) {
            chunks.pop_back();
        }
        else {
            chunks[n/chunk_size][n % chunk_size] = 0;
        }
        n--;
    }
    vector2diter<T> begin() {
        return vector2diter<T>(chunks.begin(), chunks[0]);
    }
    vector2diter<T> end() {
       return vector2diter<T>(chunks.end(),chunks[n/chunk_size]+n%chunk_size);
    }
    void log() {
        std::cout << "size=" << n << std::endl;
        std::cout << "ch_size=" << chunk_size << std::endl;
        std::cout << "chunks=" << chunks.size() << std::endl;
        for (auto p : chunks)
            std::cout << p << ' ';
        std::cout << std::endl;
    }
};

using namespace std;
int main() {
    /*vector2d<double> v(100, 0.5);
    for (int i = 0; i < 50; i++)
        v[i] = i / 100.0;
    v.log();
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    vector2d<double> w;
    w.log();
    vector2d<int> u(128, -1);
    u.log();*/


    /*vector2d<double> v(100, 0.5);
    v.log();
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    v.resize(50);
    v.log();
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    v.resize(128, 0.1);
    v.log();
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';*/

    vector2d<int> v;
    //v.log();
    //for (int i = 0; i < 600; i++) { v.push_back(i); }
    //v.log();
    /*for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';*/
    /*v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();*/
    
    /*for (int i = 0; i < v.size(); i++)
       cout << v[i] << ' ';*/
    
    v.resize(50);
    v.log();
    v.resize(128, 0.1);
    v.log();
    for (auto q : v) {
        cout << q << ' ';
    }
    sort(v.begin(), v.end());
}
