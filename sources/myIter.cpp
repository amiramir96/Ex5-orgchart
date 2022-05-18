#include "myIter.hpp"
#include "OrgChart.hpp"
#include <queue>
#include <stack>

namespace ariel
{

    void MyIter::preOrderTraversal(NodeRef curr)
    {
        if (curr == nullptr){return;}
        this->ordered_nodes.push_back(curr);

        std::stack<NodeRef> helper;
        for (NodeRef n : curr.get()->get_childs())
        {
            helper.push(n);
        }

        while (!helper.empty())
        {
            NodeRef temp = helper.top();
            this->ordered_nodes.push_back(temp);
            helper.pop();
            
            for (NodeRef n : temp.get()->get_childs())
            {
                helper.push(n);
            }
        }
    }

    void MyIter::levelOrderTraversal(NodeRef curr)
    {
        if (curr == nullptr){return;}
        this->ordered_nodes.push_back(curr);
        
        std::queue<NodeRef> helper;
        for (NodeRef n : curr.get()->get_childs())
        {
            helper.push(n);
        }

        while (!helper.empty())
        {
            NodeRef temp = helper.front();
            this->ordered_nodes.push_back(temp);
            helper.pop();
            
            for (NodeRef n : temp.get()->get_childs())
            {
                helper.push(n);
            }
        }
    }

    MyIter::MyIter(OrgChart& org, int traversal_decision) : iter_mc(org.get_mc()), my_org(&org)
    {
       if (traversal_decision == PRE_ORDER)
       {
            preOrderTraversal(org.get_root());
       } 
       else if (traversal_decision == LEVEL_ORDER)
       {
           levelOrderTraversal(org.get_root());
       }
       else if (traversal_decision == REVERSE_LEVEL_ORDER)
       {
           levelOrderTraversal(org.get_root());
           this->ordered_nodes.reverse();
       }
       else
       { // our default is pre_order
            preOrderTraversal(org.get_root());
       }
    }

    MyIter::MyIter(OrgChart& org, std::list<NodeRef> plist) : 
    iter_mc(org.get_mc()), ordered_nodes(plist), my_org(&org){}

    
// -------------
    /* this both functions forward iter to its next item 
        THIS FUNCTIONS THROWS runntime_error exception if the origin OrgChart obj has been edited along the run */
    MyIter& MyIter::operator++()
    {
        if (this->iter_mc != this->my_org->get_mc())
        {
            throw std::runtime_error("OrgChart object has been edited, cannot keep iterating over it\n");
        }
        this->ordered_nodes.pop_front();
        return *this;
    }

    MyIter MyIter::operator++(int dummy_for_post_increament)
    {
        if (this->iter_mc != this->my_org->get_mc())
        {
            throw std::runtime_error("OrgChart object has been edited, cannot keep iterating over it\n");
        }
        MyIter it = *this;
        this->ordered_nodes.pop_front();
        return it;
    }

// ---------

    // bool iter
    bool MyIter::operator==(const MyIter& diff) const 
    { /* compare between the nodes they pointed on */
        return this->ordered_nodes.front() == diff.ordered_nodes.front();
    }
    bool MyIter::operator!=(const MyIter& diff) const 
    { /* just !eq xD */
        return !(*this == diff);
    }

// ------
    /* get instantly the value of the curr node */ 
    std::string MyIter::operator*()
    {
        std::string ans;
        if (this->ordered_nodes.empty())
        {
            return ans;
        }else {
            return this->ordered_nodes.front().get()->get_val();
        } 
    }

    std::string* MyIter::operator->()
    { /* return pointer to string so the '->' will work*/
        std::string ans;
        if (this->ordered_nodes.empty())
        {
            return nullptr;
        }else {
            std::string* temp = new std::string; // without new, its will randomaly jump to seg_fault
            temp[0] = this->ordered_nodes.front().get()->get_val(); 
            return temp;
        } 
    // ----------
    }

}