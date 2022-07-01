#include "random.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2{
    void rand_gen::set_seed(int newSeed){
        seed = newSeed;
    }
    int rand_gen::next(){
        seed = (multiplier *seed+increment) % modulus;
        
        return seed;
    }
    
    void rand_gen::print_info(){
        printf("Seed: %d\nMultiplier: %d\nIncrement: %d\nModulus: %d\n", seed, multiplier, increment, modulus);
    }
}