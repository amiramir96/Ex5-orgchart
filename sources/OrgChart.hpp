#pragma once
#include "Node.hpp"
#include "myIter.hpp"

using std::ostream;

namespace ariel 
{    

    class OrgChart
    {

        public:
            OrgChart() : mc(0){}
            ~OrgChart() = default;

            OrgChart add_root(std::string);
            OrgChart add_sub(std::string, std::string);
            friend ostream& operator<<(ostream &out, const OrgChart&);
            // Iterator begin_level_order();

            //getters-setters
            size_t get_mc(){return mc;}
            void increase_mc(){mc++;}
            NodeRef get_root() const {return root;}

            MyIter begin_preorder();
            MyIter end_preorder();
            MyIter begin();
            MyIter end();
            MyIter begin_level_order();
            MyIter end_level_order();
            MyIter begin_reverse_order();
            MyIter reverse_order();

        private:
            NodeRef root;  
            size_t mc; // mode counter
            std::list<NodeRef> level_order; // return level_order.begin()  
            std::list<NodeRef> reverse_level_order;
    };
}