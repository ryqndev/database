#ifndef BTREE_UTILITY_H
#define BTREE_UTILITY_H

#include <iostream>
#include <vector>

template <class T>
void print_array(const T data[], int n, int pos = -1){
    for(int i = pos + 1; i < n; i++){
        std::cout << data[i] << ' ';
    }
}
template <class T>
T maximal(const T& a, const T& b){
    return a < b ? b : a;
}
template <class T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = a;
}
template <class T>
int index_of_maximal(T data[], int n){
    int max = 0;
    for(int i = 1; i < n; i++){
        if(data[i] > data[max]) max = i;
    }
    return max;
}
template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
    for(int j = n - 1; j >= i; j--){
        data[j + 1] = data[j];
    }
    data[i] = entry;
    n++;
}
template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    for(int i = 0; i < n; i++){
        if(entry < data[i]){
            insert_item(data, i, n, entry);
            return;
        }
    }
    insert_item(data, n, n, entry);
}
template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    for(int i = 0; i < n; i++){
        if(entry <= data[i]) return i;
    }
    return n;
}
template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    //TODO
}


template <class T>
void detach_item(T data[ ], int& n, T& entry){
    entry = data[--n];
}
template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
    assert(n > 0 && i < n);
    entry = data[i];
    for(int j = i; j < --n; j++){
        data[j] = data[j + 1];
    }
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    //TODO
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    int ni1 = n1;
    for(int i = (ni1/2) + 1; i < ni1; i++){
        data2[n2++] = data1[i];
        n1--;
    }
}
template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size){
    for(dest_size = 0; dest_size < src_size; dest_size++){
        dest[dest_size] = src[dest_size];
    }
}

template <class T>
bool is_gt(const T data[], int n, const T& item){
    for(int i = 0; i < n; i++){
        if(item <= data[i]) return false;
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){
    for(int i = 0; i < n; i++){
        if(item > data[i]) return false;
    }
    return true;
}

template <typename T>
std::ostream& operator <<(std::ostream& outs, const std::vector<T>& list){
    for(T item: list) std::cout << item << ' ';
}

template <typename T>
std::vector<T>& operator +=(std::vector<T>& list, const T& addme){
    list.push_back(addme);
}

#endif /* BTREE_UTILITY_H */