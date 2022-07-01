#include <iostream>
#include <algorithm>        //for copy function
#include <cassert>          //for assert function
#include "sequence.h"
#include "node.h"

using namespace std;

namespace coen79_lab6
{

    // constructor implementation
    sequence::sequence() {
        init();
    }

    // copy constructor
    sequence::sequence(const sequence& source) {
        init();
        *this = source;
    }

    // destructor
    sequence::~sequence() {
        list_clear(head_ptr);                               
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    void sequence::start() {
        cursor = head_ptr;                                  // cursor at the beginning
        precursor = NULL;                                   
    }

    void sequence::end() {
        if(many_nodes == 0)                                 // return if empty
            return;
        cursor = tail_ptr;                                  // set cursor at tail
        if(head_ptr == tail_ptr)                            // if there's only one node, set precursor to null
            precursor = NULL;                               
        else
            precursor = list_locate(head_ptr, many_nodes-1);        
    }

    void sequence::advance() {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type& entry) {
        if(!is_item() || precursor == NULL) {               // if empty or no current item
            list_head_insert(head_ptr, entry);              // insert at front of list
            if(tail_ptr == NULL)                             // if no tail, set tail to front
                tail_ptr = head_ptr;
            cursor = head_ptr;                              // set current to head
            precursor = NULL;                               
            many_nodes++;
        }
        else {                                              // if list is not empty and current item exists
            list_insert(precursor, entry);                  // insert into precursor
            cursor = precursor->link();                     // point precursor to cursor
            many_nodes++;
        }
    }

    void sequence::attach(const value_type& entry) {
        if(head_ptr == NULL) {                              // if empty
            //cout << "1";
            list_head_insert(head_ptr, entry);              // insert into head pointer
            tail_ptr = head_ptr;                            // tail is also at head now
            cursor = head_ptr;                              // put cursor at head
            precursor = NULL;                               // precursor is NULL
        }
        else if(cursor == NULL) {                           // if cursor NULL, then precursor is at tail
            //cout << "cursor is null if statement";
            list_insert(tail_ptr, entry);                   // insert into tail
            cursor = tail_ptr->link();
            precursor = tail_ptr;                           // precursor now at old tail
            tail_ptr = tail_ptr->link();                    // update tail pointer
        }
        else {                                              // else, insert into middle somewhere
            //cout << "3";
            list_insert(cursor, entry);                     // insert where cursor is
            precursor = cursor;                             // set precursor to old cursor
            cursor = cursor->link();                        // update cursor
            if(cursor->link() == NULL)                      // if cursor is now NULL, then tail is at cursor
                tail_ptr = cursor;
        }
        many_nodes++;
    }

    void sequence::operator=(const sequence& source) {
        if(this == &source)                                 
            return;
        list_copy(source.head_ptr, head_ptr, tail_ptr);     // copy from source to head-to-tail
        many_nodes = source.many_nodes;                     // copy many nodes
        start();                                            // call start(), setting all things to null/0
        node* tmp = source.head_ptr;                        // temporary node, since we can't edit source
        while(tmp != source.cursor) {                       //loop until we find the source's cursor
            advance();                                      
            tmp = tmp->link();                              
        }
    }

    void sequence::remove_current() {
        
		assert(is_item());                                  // check that cursor points to something first
        if(cursor == head_ptr) {                            
            if(head_ptr == tail_ptr) {                      //if only one object
                list_head_remove(head_ptr);                 //delete head
                head_ptr = NULL;                            // set all to NULL
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
            else {                                          // if size > 1 and at front
                list_head_remove(head_ptr);                 // remove head
                cursor = head_ptr;                          // point to new head
                precursor = NULL;                           // precursor is NULL
            }
        }
        else if(cursor == tail_ptr) {                       // else, cursor at end
            list_remove(precursor);                         // list_remove deletes node after precursor
            tail_ptr = precursor;                           // then shift tail pointer left once
            cursor = NULL;                                  // cursor is now NULL
        }
        else {                                              // else, cursor in middle
            list_remove(precursor);                         // remove node after precursor
            cursor = cursor->link();                        
        }
        many_nodes--;
		
    }

    sequence::size_type sequence::size() const {
        return many_nodes;
    }

    bool sequence::is_item() const {
        if(cursor == NULL)                                  //check if cursor points to anything
            return false;
        else
            return true;
    }
    
    sequence::value_type sequence::current() const {
        assert(is_item());
        return cursor->data();
    }

    // default private member variable initialization function.
    void sequence::init() {
        head_ptr = NULL;            //initialize pointers to NULL
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;             //initialize many_nodes to 0
    }
    
}