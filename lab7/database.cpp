// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    // constructor
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // copy constructor
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
		used_slots = src.used_slots;
		aloc_slots = src.aloc_slots;
        company_array = new company[aloc_slots];
        *company_array = *src.company_array;
    }
    
    // assignment operator
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
		if(this == &rhs)
            return *this;
        delete[] company_array;                                                             // delete memory from heap
        company_array = new company[rhs.aloc_slots];                                        // create new array with size of rhs
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);    
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
		std::cout << "copying elements of database...";
        return *this;
    }
    
    // destructor
    database::~database() {
        delete[] company_array;
        used_slots = 0;
        aloc_slots = 0;
    }
    
    // reserve more space
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Can??t allocate less than we are using.
        
        company* tmp = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, tmp);
        delete[] company_array;
        aloc_slots = new_capacity;
        company_array = tmp;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        if(used_slots == aloc_slots)                            // reserve another slot if inserting but full
            reserve(aloc_slots + 1);
        company insert = company(entry);                        
        company_array[used_slots++] = insert;                   // add insert object into array
        return true;
    }
    
    // add product to company
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        size_type index = search_company(company);                                          
        if(index == COMPANY_NOT_FOUND)
            return false;
        else {
            company_array[index].insert(product_name, price);                               // insert product and price into last item of company
            return true;
        }
        
    }
    
    // delete company from companies
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        if(company_index == COMPANY_NOT_FOUND)                                              // make sure company exists
            return false;
        for(size_type i = company_index; i < used_slots-1; i++) 
            company_array[i] = company_array[i+1];
        used_slots--;
        return true;
    }
    
    // delete product from company
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type index = search_company(cName);
        if(index == COMPANY_NOT_FOUND)                                                      // check that company exists
            return false;
        return company_array[index].erase(pName);                                           // return if the product was deleted or not
    }
    
    
    // search for a company in companies
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        for(size_type i = 0; i < used_slots; i++)                                           // loop through companies
            if(company_array[i].get_name() == company)                                      // if company is found return its index
                return i;                                                                   
        return COMPANY_NOT_FOUND;															// return company not found
    }
    
    // print a company's items
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    //print all companies
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
