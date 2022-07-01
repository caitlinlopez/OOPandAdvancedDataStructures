// CLASS IMPLEMENTED: statistician (see stats.h for documentation)
#include <cassert>					//provides assert
#include "statistician.h"
#include <iostream>
#include <algorithm>


using namespace std;
using namespace coen79_lab2; 	
namespace coen79_lab2 				//header definition
{
    //function implementation
    void statistician::next(double r)
    {
        total += r; 				//add to sum
        size++;   					//add to total
        if(length() == 1){
            min = r; 
			max = r;
        }
        else {  					//sets max and min
            if(r > max){
                max = r;
            }
            else if(r < min){
                min = r;
            }
        }
    }
    void statistician::reset()		//reset values to 0
    {
        total = 0.0; 
		size = 0; 	
    }
    
    double statistician::sum() const
    {
        return total; 				//return number of total items
    }
    
    double statistician::mean() const
    {
        assert(length() > 0);
        return sum()/size; 			//return sum
    }
    
    double statistician::minimum() const
    {
        assert(length() > 0);
        
        return min;  				//return minimum
    }
    
    double statistician::maximum() const
    {
        return max; 				//return maximum
    }
    
    
    bool operator == (const statistician& s1, const statistician& s2)
    {
        return (s1.length() == s2.length() &&  //checks that all of the attributes are equal
                s1.mean() == s2.mean() &&
                s1.sum() == s2.sum() &&
                s1.minimum() == s2.minimum() &&
                s1.maximum() == s2.maximum());
        
    }
    
    statistician operator+(const statistician& s1, const statistician& s2){
        
        statistician c;
        //add private variables and set it equal to c's private variables
        c.total = s1.total + s2.total;
        c.size = s1.size + s2.size;
        c.min = (s1.min<s2.min)?s1.min:s2.min;
        c.max = (s1.max>s2.max)?s1.max:s2.max;
        
        return c;
        
    }
    
    statistician operator *(double scale, const statistician& s){
        //multiply some of the private variables with scale
        statistician c;
        c.total = (scale * s.total);
        
        c.size = s.size;
        c.min = (scale * s.max);
        c.max = (scale * s.min);
        
        
   
        return c;
    }
    
}