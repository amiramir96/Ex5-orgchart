#include "Node.hpp"

namespace ariel
{

    NodeRef search_node(NodeRef curr, std::string val)
    { /* find node with val as its string content, the function is a recursive */
        if (curr.get()->get_val() == val)
        { // stop temp -> found
            return curr;
        } else{
            for (auto n : curr.get()->get_childs())
            { // loop over all childs and go 1 step deeper
                NodeRef res = search_node(n, val);
                if (res != NULL)
                {
                    return res;
                }
            }
        }
        return NULL; // no childs or nothing has been found -> null
    }

}