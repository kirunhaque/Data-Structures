#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>

/**
 * class List<T>
 *
 * General description:  class for storing and manipulating sequences of items
 *    where item type is specified via template.
 *
 * Underlying organization:  the implementation uses a singly-linked list data structure
 *    with pointers to both the front (first node) and back (last node) of the list.
 *
 *    A private struct Node is used to represent individual nodes in a list.
 */


template <typename T>
class List
{
private:
    // struct for singly-linked list nodes
    struct Node
    {
        T data;
        Node *next;
        
        Node(const T &d = T{}, Node *n = nullptr)
        : data{d}, next{n} {}
    };
    /* Data members of List class:  a front and back pointer */
    Node *front;
    Node *back;
    
    int listLength = 0;
    void print_reverse(Node* ptr) const{
        if(ptr == nullptr){
            return;
        }
        print_reverse(ptr->next);
        std::cout << ptr->data << " ";
    }
    void suffixHelper(Node* ptr, List<T> *other, T &value) const {
        if (ptr == nullptr){
            return;
        }
        suffixHelper(ptr->next, other, value);
        if(ptr->data > value){
            value = ptr->data;
        }
        other->push_front(value);
    }
    
public:
    // constructor
    List() {
        front = nullptr;
        back = nullptr;
    }
    
    // destructor
    ~List() {
        clear();
    }
    /**
     * Disclaimer:  C++ conventions tell us that we should have a couple
     * of additional constructors here (a copy constructor, assignment operator
     * etc.)
     *
     * However, to keep things simple for now we will ignore that convention
     * (since the exposure to C++ is pretty variable it seems -- some students
     * having taken 141 before last semester; some students coming from 107,
     * etc.)
     */
    
    /**
     * function: clear
     * desc:  makes the calling list empty (but the list still
     *        exists).
     */
    void clear()
    {
        Node *p = front;
        Node *pnext;
        
        while (p != nullptr)
        {
            pnext = p->next;
            delete p;
            listLength--;
            p = pnext;
        }
        front = back = nullptr;
    }
    
    /**
     * TODO
     *
     * function: length
     * desc:  returns the length of the calling list
     *
     * REQUIREMENTS:  this is a working implementation, but
     *   it takes linear time.
     *
     *   Your job (todo):  make modifications so that this
     *     operation becomes constant time (O(1)).
     *
     *   This task is different from most others in that most of
     *       the "real" work you do to make this work
     *    in O(1) time will be in _other_ functions which affect
     *    the length of lists.
     *
     *    HINT:  you are free to add data members to the List class...
     *           maybe for "bookkeeping"??
     */
    int length() const
    {
        int n = 0;
        /* Node *p = front;
         int n = 0;
         
         while (p != nullptr)
         {
         n++;
         p = p->next;
         } */
        n = listLength;
        return n;
    }
    
public:
    /**
     * function: is_empty
     * desc:   Returntrue if the list is empty, false otherwise.
     */
    bool is_empty() const
    {
        return front == nullptr;
    }
    
    /**
     * function: print
     * desc:  self-evident:  simply prints the elements/values of the list in order.
     */
    void print() const
    {
        Node *p = front;
        
        std::cout << "[ ";
        while (p != nullptr)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << "]\n";
    }
    
    /**
     * function: push_front
     * desc:  adds a new element to the front of the list (calling object) containing val.
     *        Equivalently, you can think of this as an "prepend" operation.
     */
    void push_front(const T &data)
    {
        front = new Node(data, front);
        if (back == nullptr)
            back = front;
        listLength++;
    }
    
    /**
     * function: pop_front
     * desc:  if the list (calling object) is non-empty, the first element (front of list)
     *        is removed and the value it stored is 'passed back' to the caller via the reference
     *        parameter val.  In this case (non-empty list), true is returned for success.
     *
     *        Otherwise (the list is empty), false is returned and the reference parameter val has
     *        no meaning.
     */
    bool pop_front(T &val)
    {
        Node *tmp;
        
        if (front == nullptr)
            return false;
        val = front->data;
        
        tmp = front;
        front = front->next;
        delete tmp;
        listLength--;
        if (front == nullptr)
            back = nullptr;
        return true;
    }
    
    /**
     * function: push_back
     * desc:  adds a new element to the end of the list (calling object) containing val.
     *        Equivalently, you can think of this as an "append" operation.
     */
    void push_back(const T &val)
    {
        Node *tmp = new Node(val, nullptr);
        listLength++;
        if (front == nullptr)
        {
            front = back = tmp;
        }
        else
        {
            back->next = tmp;
            back = tmp;
        }
    }
    
    /**
     * function: remove_first
     * desc:  removes first occurrence of x (if any) in given list (calling object).
     *        if a match is found (and removed), true is returned.
     *        Otherwise (no match found), false is returned and the list is unchanged.
     */
    bool remove_first(const T &x)
    {
        Node *p, *tmp;
        T dummy;
        
        if (front == nullptr)
            return false;
        if (front->data == x)
        {
            pop_front(dummy);
            return true;
        }
        p = front;
        while (p->next != nullptr)
        {
            if (x == p->next->data)
            {
                tmp = p->next;
                p->next = tmp->next;
                if (tmp == back)
                    back = p;
                delete tmp;
                listLength--;
                return true;
            }
            p = p->next;
        }
        return false;
    }
    
    /**
     * function: slow_remove_all
     * desc:  removes all occurrences of x (if any) in given list (calling object).
     *        returns number of matches found/deleted.  Relative order of undeleted elements
     *        is unchanged.
     *
     * approach:  repeatedly calls remove_first until it fails.
     *
     * Note:  function is designated with the slow_ prefix because, in the worst case, it can
     *        take quadratic time.
     */
    int slow_remove_all(const T &x)
    {
        int n = 0;
        
        while (remove_first(x))
            n++;
        return n;
    }
    
    /**
     * function: is_sorted
     * desc:  returns true if elements in list are in sorted order from
     *        smallest to largest (duplicates allowed); returns false otherwise.
     *
     * Note:  requires that type T has the > operator defined on it (perhaps via
     *        operator overloading as in the case of the string class)
     */
    bool is_sorted() const
    {
        Node *p = front;
        
        while (p != nullptr && p->next != nullptr)
        {
            if (p->data > p->next->data)
                return false;
            p = p->next;
        }
        return true;
    }
    
    /** TODO
     *    function:  count
     *     description:  Counts number of occurrences
     *             of x in the list and returns that count.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     */
    int count(const T &x) const
    {
        Node *temp = front;
        int count = 0;
        while(temp != NULL){
            if(temp->data == x){
                count++;
            }
            temp = temp->next;
        }
        if (count > 0) return count;
        return 0;
    }
    
    /* TODO
     *
     *  function:
     *
     *  if list is empty, we do nothing and return false
     *  otherwise, the last element in the list is removed, its
     *      value (data field) is assigned to the reference parameter
     *      data (so the removed element can be 'passed-back' to the
     *      caller) and true is returned.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     *
     */
    bool pop_back(T &data)
    {
        Node *temp = front;
        Node* ptr;
        if(temp == NULL){
            return false;
        }
        if(temp->next == NULL){
            data = temp->data;
            front = NULL;
            back = NULL;
            return true;
        }
        while(temp->next->next != NULL){
            temp = temp->next;
        }
        ptr = temp;
        temp = temp->next;
        data = temp->data;
        listLength--;
        delete temp;
        back = ptr;
        back->next = NULL;
        return true;
    }
    
    /**
     * TODO:
     *   function:  equal_to
     *   description:  returns true if calling List and parameter
     *      List other contain exactly the same sequence of values.
     *      Returns false otherwise.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is MIN(len1,len2)
     *    and len1 and len2 are the respective lengths of the two lists.
     **/
    bool equal_to(const List<T> &other) const
    {
        Node* temp1 = front;
        Node* temp = other.front;
        if (this->length() == other.length()) {
            if (this->length() == 0) {
                return true;
            }
            while( temp != nullptr){
                if (temp->data != temp1->data){
                    return false;
                }
                temp = temp->next;
                temp1 = temp1->next;
            }
            return true;
        }
        else{
            return false;
        }
        return false; // placeholder
    }
    
    /**
     * TODO:  print in reverse order
     *
     * Try to do without looking at notes!
     * Hints:  recursive helper function
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     */
    void print_rev() const
    {
        Node* p = front;
        std::cout << " [ ";
        print_reverse(p);
        std::cout << " ] " <<std::endl;
    }
    
    /* TODO
     *  For full credit, you cannot allocate any new memory!
     *
     *  description:  self-evident
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length
     *    of the list.)
     */
    void reverse()
    {
        //check for empty list
        if (front == nullptr) return;
        
        //check for single list
        if (front->next == nullptr) return;
        
        Node* current = front;
        Node *prev = nullptr;
        Node* nextNode = nullptr;
        while(current != nullptr){
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        back = front;
        front = prev;
        //back->next = nullptr;
        
        /*  while(current != nullptr){
         current->next = prev;
         prev = current;
         current = tmp;
         tmp = tmp->next;
         }
         //tmp->next = current;
         back->next = nullptr;
         front = tmp;
         //back->next = nullptr; */
    }
    
    /** TODO
     *   function:  fast_remove_all
     *   description:  same behavior/semantics as
     *      slow_remove_all.  However, this function
     *      must guarantee linear time worst case
     *      runtime (hence, "fast").
     *
     *   REQUIREMENT:  linear worst-case runtime.
     *
     *   Note:  your solution may be either recursive or
     *   iteratieve.
     **/
    
    int fast_remove_all(const T &x)
    {
        Node *p, *tmp;
        T dummy;
        int count = 0;
        if (front == nullptr)
            return 0;
        if (front->data == x) {
            pop_front(dummy);
            count++;
        }
        p = front;
        while (p->next != nullptr)
        {
            if (x == p->next->data)
            {
                tmp = p->next;
                p->next = tmp->next;
                if (tmp == back)
                    back = p;
                delete tmp;
                count++;
                continue;
            }
            p = p->next;
        }
        listLength = listLength - count;
        return count;
    }
    
    
    
    /** TODO
     * function:  insert_sorted
     *
     * description:  assumes given list is already in sorted order from
     *     smallest to largest and inserts x into the appropriate position
     *        retaining sorted-ness.
     * Note 1:  duplicates are allowed.
     *
     * Note 2:  if given list not sorted, behavior is undefined/implementation
     *         dependent.  We blame the caller.
     *         So... you don't need to check ahead of time if it is sorted.
     *
     *
     * REQUIREMENTS:
     *
     *   O(n) runtime
     */
    void insert_sorted(const T &x)
    {
        
        // case for empty list
        if (front == nullptr) {
            push_front(x);
            return;
        }
        Node* prev = front;
        Node * current = front->next;
        // case for first node
        
        if(x >= back->data){
            push_back(x);
            return;
        }
        ///WORK ON THIS
        //CHECK FOR THE FIRST NODE AND LAST NODE AND FOR STRINGS
        while ( current != nullptr){
            // case for first node
            if( x <= prev->data) {
                push_front(x);
                return;
            }
            if(current->data <= x && current->next->data > x){
                Node* newNode= new Node(x, current->next);
                current->next = newNode;
                listLength++;
                if(newNode->next == nullptr){
                    back = newNode;
                }
                return;
            }
            prev = prev->next;
            current = current->next;
        }
    }
    
    /** TODO
     * function:  merge_with
     *
     * description:  assumes both list a and b are in
     *     sorted (non-descending) order and merges them
     *     into a single sorted list with the same
     *     elements.
     *
     *     This single sorted list is stored in a while
     *     b becomes empty.
     *
     *     if either of given lists are not sorted,
     *     we blame the caller and the behavior is
     *     implementation dependent -- i.e., don't worry
     *     about it!
     *
     *      Condition in which both parameters are the same
     *      list (not merely "equal"), the function simply
     *      does nothing and returns.  This can be tested
     *      with simple pointer comparison.
     *
     *     Example:
     *
     *         a:  [2 3 4 9 10 30]
     *         b:  [5 8 8 11 20 40]
     *
     *         after call a.merge_with(b):
     *
     *           a:  [2 3 4 5 8 8 9 10 11 20 30 40]
     *           b:  []
     *
     *
     * REQUIREMENTS:
     *
     *     Runtime Must be linear in the length of the
     *     resulting merged list (or using variables above,
     *     O(a.length()+b.length()).
     *
     *  should not allocate ANY new list
     *     nodes -- it should just re-link existing
     *     nodes.
     */
    void merge_with(List<T> &other)
    {
        int newLength = listLength + other.listLength;
        Node*temp1 = front;
        Node*temp2 = other.front;
        Node* newSort;
        if (front == nullptr) {
            front = temp2;
            back = other.back;
            other.front = nullptr;
            other.back = nullptr;
            listLength = newLength;
            return;
        }
        if (other.front == nullptr) {
            front = temp1;
            return;
        }
        if(temp1 && temp2){
            if(temp1->data <= temp2->data){
                newSort = temp1;
                temp1 = newSort->next;
            }
            else{
                newSort = temp2;
                temp2 = newSort->next;
            }
        }
        front = newSort;
        while(temp1 && temp2){
            if (temp1->data <= temp2->data){
                newSort->next = temp1;
                newSort = temp1;
                temp1 = newSort->next;
            }
            else{
                newSort->next = temp2;
                newSort = temp2;
                temp2 = newSort->next;
            }
        }
        
        if (temp1 == nullptr){
            newSort->next = temp2;
            back = other.back;
        }
        if (temp2 == nullptr){
            newSort->next = temp1;
        }
        listLength = newLength;
        other.front = other.back = nullptr;
        return;
    }
    
    /**
     * TODO
     * function:  clone
     *
     * description:  makes a "deep copy" of the given list a
     *   and returns it (as a List pointer).
     *
     * NOTE:  this functionality would normally be folded into
     *  a "copy constructor"
     *
     */
    List<T> *clone() const
    {
        
        List<T> *newList = new List<T>();
        Node* currentList = front;
        Node* toList = nullptr;
        
        if(currentList == nullptr) return newList;
        newList->front = new Node(currentList->data, nullptr);
        toList = newList->front;
        currentList = currentList->next;
        
        while(currentList != nullptr){
            toList->next = new Node(currentList->data, nullptr);
            currentList = currentList->next;
            toList = toList->next;
        }
        
        newList->back = toList;
        newList->listLength = listLength;
        return newList;
        
        return nullptr;
    }
    
    /**
     * TODO
     * function:  prefix
     *
     * description:  removes the first k elements from the
     *               calling list which are used to form a new list
     *                    which is then returned.
     *
     *        if n is the length of the given list, we have the
     *        following boundary conditions:
     *
     *          if k==0:
     *                calling list unchanged and an empty list returned
     *          if k>=n:
     *                calling becomes empty and a list containing
     *                all elements previously in lst is returned.
     *
     *        examples:
     *
     *          EX1:  lst:  [2, 3, 9, 7, 8]
     *            k:    3
     *
     *            call:
     *
     *              List<int> * pre = lst.prefix(3);
     *
     *            after call:
     *               lst:  [7, 8]
     *               returned list (prefix):  [2, 3, 9]
     *
     *          EX2  lst:  [2, 3, 9, 7, 8]
     *            k:    0
     *
     *          call:
     *
     *              List<int> * pre = lst.prefix(3);
     *
     *            after call:
     *               lst:  [2, 3, 9, 7, 8]  (unchanged)
     *               returned list:  []
     *
     *          EX3  lst:  [2, 3, 9, 7, 8]
     *            k:    5
     *
     *          call:
     *
     *              List<int> * pre = lst.prefix(5);
     *
     *            after call:
     *               lst:  []
     *               returned list:  [2, 3, 9, 7, 8]
     *
     * REQUIREMENTS:
     *
     *    RUNTIME:  THETA(n) worst case where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned prefix should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be
     *                  allocated or deallocated; you should just
     *                  "re-use" the existing nodes.  HOWEVER, you will
     *                       need to allocate a List object for the returned
     *                       prefix (but, again, the underlying Nodes should be
     *                       re-used from the calling list).
     */
    
    
    List<T> *prefix(unsigned int k)
    {
        
        int count = 0;
        List<T> *prefixList = new List<T>();
        if(front == nullptr) return nullptr;
        if (k == 0) return prefixList;
        
        Node* temp = front;
        Node* p;
        if (k >= length()) {
            prefixList->front = front;
            prefixList->back = back;
            front = back = nullptr;
            prefixList->listLength = listLength;
            listLength = 0;
            return prefixList;
        }
        prefixList->front = temp;
        p = prefixList->front;
        front = front->next;
        while( count < k-1 ){
            p->next = front;
            front = front->next;
            count++;
            p = p->next;
        }
        p->next = nullptr;
        prefixList->back = p;
        prefixList->listLength = k;
        listLength -= k;
        return prefixList;
        // return nullptr;
        
        
        /*  int count = 0;
         List<T> *prefixList = new List<T>();
         Node* temp = front;
         if(front == nullptr) return nullptr;
         if (k == 0) return prefixList;
         
         if (k >= length()) {
         prefixList->front = front;
         prefixList->back = back;
         front = back = nullptr;
         prefixList->listLength = listLength;
         listLength = 0;
         return prefixList;
         }
         prefixList->front = temp;
         while(count < k){
         temp = temp->next;
         count++;
         }
         
         front = temp->next;
         temp->next = nullptr;
         prefixList->back = temp;
         prefixList->listLength = k;
         listLength -= k;
         return prefixList;
         */
    }
    
    /**
     * TODO
     * function:  filter_leq
     *
     * description:  removes all elements of the given list (lst) which
     *        are less than or equal to a given value (cutoff)
     *
     *        A list containing the removed elements is returned.
     *
     * examples:
     *
     *    EX1:     lst:  [4, 9, 2, 4, 8, 12, 7, 3]
     *        cutoff:  4
     *
     *        after call:
     *            lst:  [9, 8, 12, 7]
     *            returned list:  [4, 2, 4, 3]
     *
     *       -----------------------------------------
     *    EX2:     lst:  [6, 5, 2, 1]
     *        cutoff:  6
     *
     *        after call:
     *            lst:  []
     *             returned list:  [6, 5, 2, 1]
     *
     * REQUIREMENTS:
     *
     *    RUNTIME:  THETA(n) where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned list should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
     *           you should just "re-use" the existing nodes.  HOWEVER, you will
     *           need to allocate a LIST structure itself (i.e., for the returned
     *           list).
     *
     */
    List<T> *filter_leq(const T &cutoff)
    {
        List<T> *newList = new List<T>();
        Node* temp = front;
        Node* newNode;
        int counter = 0;
        
        if (front == nullptr) return newList;
        //Condition if the first node that is <= to the cutoff is in the middle of the node.
        while( temp->next != nullptr){
            //Check if the first node is <= to the cutoff
            if(temp->next->data <= cutoff){
                counter++;
                newNode = temp->next;
                temp->next = temp->next->next;
                newNode->next = nullptr;
                if(newList->front == nullptr){
                    newList->front = newList->back = newNode;
                }
                else{
                    newList->back->next = newNode;
                    newList->back = newNode;
                }
            }
            else{
                temp = temp->next;
            }
        }
        if (front->data <= cutoff){
            counter++;
            temp = front;
            front = front->next;
            temp->next = newList->front;
            newList->front = temp;
        }
        listLength -= counter;
        newList->listLength = counter;
        return newList;
    }
    
    /**
     * TODO
     * function:  concat
     *
     * description:  concatenates the calling list with parameter list (other)
     *    The resulting concatenation is reflected the calling list; the
     *    parameter list (other) becomes empty.
     *
     *    example:
     *
     *    EX1:  a: [2, 9, 1]
     *          b: [5, 1, 2]
     *
     *          call:
     *                a.concat(b);
     *
     *    after call:
     *
     *        a: [2, 9, 1, 5, 1, 2]
     *        b: []
     *
     * REQUIREMENTS:
     *
     *     runtime:  O(1)
     *
     *     sanity:  this operation makes sense when a and b
     *        are distinct lists.  For example, we don't
     *        want/allow the caller to do something like
     *        this:
     *
     *            List<int> *my_list = new List<int>();;
     *
     *            my_list->push_front(my_lst, 4);
     *            my_list->push_front(my_lst, 2);
     *
     *            my_lst->concat(my_lst);
     *
     *        your implementation must detect if it is being
     *        called this way.  If so the function does nothing
     *        and (optionally) prints an error message to
     *        stderr.
     *
     */
    void concat(List<T> &other)
    {
        if (this == &other)
        {
            std::cerr << "warning:  List::concat():  calling object same as parameter";
            std::cerr << "\n          list unchanged\n";
            return;
        }
        if (other.front == nullptr) return;
        
        if (front == nullptr) {
            front = other.front;
            back = other.back;
            listLength = other.listLength;
            other.listLength = 0;
            other.front = nullptr;
            other.back = nullptr;
            return;
        }
        listLength = listLength + other.listLength;
        back->next = other.front;
        back = other.back;
        other.front = nullptr;
        other.back = nullptr;
        other.listLength = 0;
        //delete &other;
        std::cout << "List::concat(): no error...\n";
    }
    
    /**
     * TODO
     *
     * function:  compare_with
     * description: compares the calling list with parameter list (other)
     *    "LEXICALLY" (essentially a generalization of dictionary
     *    ordering).
     *
     *    link:  https://en.wikipedia.org/wiki/Lexicographical_order
     *
     *    Return Value:
     *
     *       o if the two lists are identical, 0 is returned.
     *       o if the calling list is lexically BEFORE the other list,
     *             -1 is returned
     *       o otherwise, the other list is lexically before the calling
     *             list and 1 (positive one) is returned.
     *
     *    Properties and examples:
     *
     *        The empty list is lexically before all non-empty lists
     *          (you can say it is "less than" all non-empty lists).
     *
     *        Examples (using mathematical notation):
     *
     *          [2 5 1] < [3 1 1 1 1]    (think dictionary ordering!)
     *
     *          [4 1 3] < [4 1 3 0 0 0]  (prefix: just like "car" is before
     *                                            "cartoon" in the dictionary).
     *
     *          [4 5 6 1 2 3 9 9 9] < [4 5 6 1 4 0 0]
     *                   ^                     ^
     *                      (they have a common prefix of length 4; but at
     *                      the fifth position they differ and the left list
     *                      is the winner (smaller) -- no need to look further)
     *
     *
     *        Templates?
     *
     *          Since List is a template class, the elements of a particular
     *          list need not be integers.  For example, we could have
     *          lists of strings.
     *
     *          Good news:  the exact same principle applies because
     *          strings can be compared just like integers can be compared!
     *
     *          Great news:  you don't need to think about this at all!
     *          The exact same code you would write if you assumed the element
     *          type is integer will work for other types like strings.
     *
     *          Why?  Because, for example, all of these operators:
     *
     *                   <, <=, ==, > and >=
     *
     *          all work on strings.  They are not 'built-in' to C++, but
     *          the class string has "overloaded" these operators (they
     *          result in an appropriate function call).
     *
     *          (In a subsequent exercise, we will do this kind of
     *          overloading ourselves!)
     *
     *        Examples with lists of strings:
     *
     *          ["egg", "goat"] < ["egg", "globe", "apple"]
     *
     *          ["zebra", "fun"] < ["zebra", "funny"]
     *
     *        [Yes, the components of these lists are THEMSELVES compared
     *        lexically, but the string class is doing those comparisons)
     *
     */
    int compare_with(const List<T> &other) const
    {
        Node* temp;
        Node* otherList = other.front;
        temp = front;
        while (temp != nullptr && otherList != nullptr){
            if(temp->data > otherList->data){
                return 1;
            }
            else if (temp->data < otherList->data){
                return -1;
            }
            else{
                temp = temp->next;
                otherList = otherList->next;
            }
        }
        if (temp == nullptr && otherList != nullptr){
            return -1;
        }
        else if(temp != nullptr && otherList == nullptr){
            return 1;
        }
        return 0;
    }
    
    /*
     * TODO
     *
     * function:  suffix_maxes
     *
     * desc:  constructs a new list of the same length as the calling object
     *        with the value stored at position i of the new list is the MAXIMUM
     *        value in the suffix (or tail) of the calling list starting from
     *        position i.
     *
     *        This new list is returned and the calling list is unchanged.
     *
     *        Example:
     *
     *          Given List:  [6, -18, 12, 4, 1, 7, 2, 5  4]
     *                                    ^^^^^^^^^^^^^^^^
     *
     *          New list:    [12, 12, 12, 7, 7, 7, 5, 5, 4]
     *                                    ^
     *
     *              (as a sub-example, the marked entry in the new list
     *              (marked with '^') is the max of the marked suffix in the
     *              given list (marked with a bunch of '^'s).
     *
     * REQUIREMENTS:
     *
     *        Total Runtime:   O(n)
     *        Calling list is unchanged.
     *
     */
    
    List<T> *suffix_maxes() const
    {
        List<T> *newlist;
        newlist = new List<T>();
        if(front == nullptr){
            return newlist;
        }
        T lastVal = back->data;
        newlist->suffixHelper(front, newlist, lastVal);
        return newlist;
    }
    /**
     * func:  checksum
     * desc:  Performs and XOR of all node pointers and returns result as
     *        an unsigned int.
     *
     * NOTES: YOU MAY NOT TOUCH OR MODIFY THIS FUNCTION!!
     */
    unsigned long int checksum()
    {
        unsigned long int s = 0;
        Node *p = front;
        
        while (p != nullptr)
        {
            s = s ^ ((unsigned long int)p);
            p = p->next;
        }
        return s;
    }
    
};

#endif
