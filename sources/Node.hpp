#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <list>
#include <stdexcept>
#include <memory>
#include <map>

namespace ariel
{

    class Node
    {
        using NodeRef = std::shared_ptr<Node>;
        public:
            /* just defulats */
            Node() : parent(nullptr){}
            Node(std::string& word){content = word;}
            ~Node() = default;

            /* getters-setters */
            NodeRef get_parent(){return parent;}
            void set_parent(NodeRef p){parent = std::move(p);}
            
            std::string get_val(){return content;}
            void set_val(std::string& val){content = val;}

            std::vector<NodeRef> get_childs(){return all_childs;}
            void add_child(NodeRef n){all_childs.push_back(n);}

            int level;

        private:
            NodeRef parent; // the origin node which come before this.
            std::vector<NodeRef> all_childs; // all nodes that this -> points to. 
            std::string content; // the value of the node
    };
    using NodeRef = std::shared_ptr<Node>;
    NodeRef search_node(NodeRef curr, std::string val); // check if val is related as sun to curr, if yes, return its node

}