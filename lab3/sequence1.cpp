#include "sequence1.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cmath>

namespace coen79_lab3{
    
    bool sequence::is_item() const {
        if(current_index < used){
            return true;
        }
        return false;
    }
   void sequence::start(){
       current_index = 0;
    }
    
    void sequence::end(){
        current_index = used-1;		//iterator points to last item in sequence
    }
    
    void sequence::last(){
        current_index = CAPACITY-1;	//set to capacity-1, no matter the number of items in sequence
        
    }
       
    
    void sequence::advance(){
        assert(is_item());
        if(current_index < used){
            current_index++; 		//increase index
        }
    }
    
    void sequence::retreat(){
        if(current_index > 0){
            current_index--; 		//decrease index
        }
    }
    
    void sequence::insert(const value_type & entry){
        assert(size() < CAPACITY);
        if(used == 0){
            data[used] = entry;		//insert an item
            current_index = 0;
        }
        else {
        //insert an item in front of index
            for (int i = used; i >= current_index+1; --i){
                data[i] = data[i-1];
             }
            data[current_index] = entry;
          }
        
        used++; //increase size
    }
    void sequence::attach(const value_type & entry){
        assert(size() < CAPACITY);
        
        if (!is_item()){	 //if there isn't a current item, place in end
            data[used] = entry;
        }
        else {
        for (int i = used; i > current_index +1; --i){
            data[i] = data[i-1];
            //shift everything right and make space to add entry behind current_index
        }
        data[current_index+1] = entry;
            current_index = current_index+1;
        }
        used++; //increase size
        }
    
    void sequence::remove_current(){
        assert(is_item() == true);
        
        for (int i = current_index+1; i<used; ++i){
            data[i-1] = data[i]; //shift item left
        }
        used--; //decrease used by 1
    }
    
    void sequence::insert_front(const value_type & entry) {
        assert(size() < CAPACITY);
        current_index = 0;
        insert(entry);
        used++; //increase size
    }
    
    void sequence::attach_back(const value_type & entry){
        assert(size() < CAPACITY);
        data[used] = entry; //attach at the end
        used++; //increase size
    }
   
    void sequence::remove_front(){
        for (int i = 0; i<used-1; ++i){
            data[i] = data[i+1]; //shift everything left
        }
        used--;			//decrease used
    }
    
    sequence::value_type sequence::current() const{
        assert(is_item());
        return data[current_index]; //return item
    }
    
    sequence::value_type sequence::operator[] (int index)const {
        assert(index < used);
        return data[index]; //return item from given index
    }
    
    double sequence::mean() const{
        double sum = 0.0;
        for (int i = 0; i < used; ++i){
            sum += data[i];
        }
        return sum/size();
    }
    double sequence::standardDeviation() const {
        
        double stanDev = 0.0;
        for (int i = 0; i<used; ++i){
            stanDev += pow(data[i]-mean(),2);
        }
        return sqrt(stanDev/used); 
    }
    
    sequence operator +=(const sequence& lhs, const sequence& rhs){
        sequence n(lhs);	 //copy of lhs
        int start = lhs.used;
        n.used = lhs.used + rhs.used;
        
        for (int i = 0; i < rhs.used; ++i){ //add everything from rhs to lhs
            n.data[start] = rhs.data[i];
            start++;
        }
        return n;		//return copy of lhs
    }
   
    sequence operator +(const sequence& lhs, const sequence& rhs){
        sequence answer;
        assert(lhs.size()+ rhs.size() <= sequence::CAPACITY);
        answer += lhs;
        answer += rhs;
        return answer;
    }
    
    sequence::value_type summation(const sequence &s){
        double total = 0.0;
        for (int i = 0; i < s.size(); ++i){
            total += s.data[i];
        }
        return total;
    }
   
}