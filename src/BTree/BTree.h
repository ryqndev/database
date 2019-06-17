#ifndef BTREE_H
#define BTREE_H

#include "BTreeUtility.h"
#include <iostream>
#include <iomanip>

template <class T>
class BTree{
    public:
        BTree(bool dups = false):dups_ok(dups), data_count(0), child_count(0){}
        BTree(const BTree<T>& other){
            dups_ok = other.dups_ok;
            copy_array(data, other.data, data_count, other.data_count);
            copy_array(subset, other.subset, child_count, other.child_count);
        }
        ~BTree(){
            if(!is_leaf())
                for(int i = 0; i < child_count; i++)
                    subset[i]->~BTree();
        }
        BTree<T>& operator =(const BTree<T>& RHS){
            ~BTree();
            dups_ok = RHS.dups_ok;
            copy_array(data, RHS.data, data_count, RHS.data_count);
            copy_array(subset, RHS.subset, child_count, RHS.child_count);
            return *this;
        }
        void insert(const T& entry){
            loose_insert(entry);
            if(data_count > MAXIMUM){
                BTree<T>* temp = new BTree<T>(*this);
                data_count = 0;
                child_count = 0;
                subset[0] = temp;
                fix_excess(0);
            }
        }
        void remove(const T& entry){
            loose_remove(entry);
            if(data_count <= 0){
                
            }
        }

        void clear_tree();                          //clear this object (delete all nodes etc.)
        void copy_tree(const BTree<T>& other);      //copy other into this object

        bool contains(const T& entry){
            int m = first_ge(data, data_count, entry);
            if(m > 0 && data[m - 1] == entry) return true;
            if(is_leaf()) return false;
            return subset[m]->contains(entry);
        }
        T& get(const T& entry){
            assert(contains(entry));
            int m = first_ge(data, data_count, entry);
            if(m > 0 && data[m - 1] == entry) return data[m-1];
            return subset[m]->get(entry);
        }
        T* find(const T& entry){
            assert(contains(entry));
            int m = first_ge(data, data_count, entry);
            if(m > 0 && data[m - 1] == entry) return &data[m-1];
            return subset[m]->find(entry);
        }
        int size() const;                           //count the number of elements in the tree
        bool empty() const{ return data_count == 0; }

        void print_tree(int level = 0, std::ostream &outs=std::cout) const{
            for(int i = data_count - 1; i >= 0; i--){
                if(!is_leaf()) subset[i + 1]->print_tree(level + 1, outs);
                if(i == data_count-1) std::cout << std::endl << std::setw(level * 8) << std::setfill(' ') << "__";
                std::cout << std::endl << std::endl << std::setw(level * 8) << std::setfill(' ') << data[i] << ' ';
                if(i == 0) std::cout << std::endl << std::setw(level * 8) << std::setfill(' ') << "__";
            }
            if(!is_leaf()) subset[0]->print_tree(level + 1, outs);
        }

        friend std::ostream& operator<<(std::ostream& outs, const BTree<T>& print_me){
            print_me.print_tree(0, outs);
            return outs;
        }
    //put private here when done
        static const int MINIMUM = 1;
        static const int MAXIMUM = 2 * MINIMUM;

        bool dups_ok;                                   //true if duplicate keys may be inserted
        int data_count;                                 //number of data elements
        T data[MAXIMUM + 1];                            //holds the keys
        int child_count;                                //number of children
        BTree* subset[MAXIMUM + 2];                     //subtrees

    private:
        bool is_leaf() const {return child_count==0;}   //true if this is a leaf node
        void loose_insert(const T& entry){
            int i = first_ge(data, data_count, entry);
            bool found = (i < data_count && data[i] == entry);
            if(found) return;
            if(is_leaf()){
                insert_item(data, i, data_count, entry);
            }else{
                subset[i]->loose_insert(entry);
                if(subset[i]->data_count > MAXIMUM) fix_excess(i);
            }
        }
        void fix_excess(int i){
            insert_item(subset, i + 1, child_count, new BTree<T>());
            split(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count);
            T item;
            detach_item(subset[i]->data, subset[i]->data_count, item);
            if(!subset[i]->is_leaf()){
                BTree* child;
                split(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);
                detach_item(subset[i]->subset, subset[i]->child_count, child);
                insert_item(subset[i+1]->subset, 0, subset[i+1]->child_count, child);
            }
            ordered_insert(data, data_count, item);
        }
        //remove element functions:
        void loose_remove(const T& entry){

        }
        void fix_shortage(int i);                       //fix shortage of data elements in child i

        void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry
        void rotate_left(int i);                        //transfer one element LEFT from child i
        void rotate_right(int i);                       //transfer one element RIGHT from child i
        void merge_with_next_subset(int i);             //merge subset i with subset i+1
};

#endif /* BTREE_H */