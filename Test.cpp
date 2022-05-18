#include "OrgChart.hpp"
#include "doctest.h"

using namespace ariel;

TEST_CASE("bad inputs")
{
    OrgChart organization;
    organization.add_root("CEO");
    SUBCASE("trying to add_sub to nont exist supervizor")
    {
        CHECK_THROWS(organization.add_sub("not_exist", "q"));
        CHECK_THROWS(organization.add_sub("not_at_all_exist", "q"));
        CHECK_NOTHROW(organization.add_sub("CEO", "~anything"));
    }
    SUBCASE("change root-> shouldnt throw")
    {
        CHECK_NOTHROW(organization.add_root("~anything"));
        CHECK_NOTHROW(organization.add_root("~anything_else"));
    }

    SUBCASE("empty organization")
    {
        OrgChart organization_empty;
        CHECK_NOTHROW(organization_empty.end());
        CHECK_NOTHROW(organization_empty.begin_preorder());
        CHECK_NOTHROW(organization_empty.begin_level_order());
        CHECK_NOTHROW(organization_empty.reverse_order());
    }

    SUBCASE("change root after adding childs will reset the whole organization")
    {
        organization.add_sub("CEO", "worker");
        organization.add_root("new_CEO");
        CHECK_THROWS(organization.add_sub("worker", "~anything"));
        CHECK_THROWS(organization.add_sub("CEO", "~anything"));
        CHECK_NOTHROW(organization.add_sub("new_CEO", "~any"));
    }
}

TEST_CASE("good inputs")
{
    OrgChart organization;
    organization.add_root("CEO").add_sub("CEO", "1st_child").add_sub("CEO", "2nd_child");
    organization.add_sub("CEO", "3rd_child");
    organization.add_sub("1st_child", "child_of_1st");
    organization.add_sub("3rd_child", "child_of_3rd");
    
    SUBCASE("iterators run from start to end excatly on all the nodes")
    {
        int organization_size = 6;
        int level_order_iterates=0, reverse_order_iterates=0, pre_order_iterates=0;
        
        SUBCASE("pre_order:")
        {
            for(auto preit = organization.begin_preorder(); preit != organization.end_preorder(); preit++)
            {
                pre_order_iterates++;
            }
            CHECK_EQ(pre_order_iterates, organization_size);
        }

        SUBCASE("level_order:")
        {
            for(auto levelit = organization.begin_level_order(); levelit != organization.end_level_order();levelit++)
            {
                level_order_iterates++;
            }
            CHECK_EQ(level_order_iterates, organization_size);
        }

        SUBCASE("reverse_level_order")
        {
            for(auto rlevelit = organization.begin_reverse_order(); rlevelit != organization.reverse_order(); rlevelit++)
            {
                reverse_order_iterates++;
            }
            CHECK_EQ(reverse_order_iterates, organization_size);
        }

    }

    SUBCASE("check consistency of iterators -> not running on random")
    {
        SUBCASE("pre_order:")
        {
            auto preit2 = organization.begin_preorder();
            for(auto preit1 = organization.begin_preorder(); preit1 != organization.end_preorder(); preit1++, preit2++)
            {
                CHECK_EQ(true, preit1 == preit2);
            }
        }
        SUBCASE("level_order:")
        {
            auto levelit2 = organization.begin_level_order();
            for(auto levelit1 = organization.begin_level_order(); levelit1 != organization.end_level_order(); levelit1++, levelit2++)
            {
                CHECK_EQ(true, levelit1 == levelit2);
            }
        }

        SUBCASE("reverse_level_order")
        {
            auto rlevelit2 = organization.begin_reverse_order();
            for(auto rlevelit1 = organization.begin_reverse_order(); rlevelit1 != organization.reverse_order(); rlevelit1++, rlevelit2++)
            {
                CHECK_EQ(true, rlevelit1 == rlevelit2);
            }
        }
    }

    SUBCASE("check that traversal of iterators is currect")
    {
        OrgChart organization_3;
        organization_3.add_root("a");
        organization_3.add_sub("a", "b");
        organization_3.add_sub("b", "c");
        organization_3.add_sub("c", "d");
        organization_3.add_sub("d", "e");
        organization_3.add_sub("e", "f");

        SUBCASE("pre_order:")
        {
            auto p_it = organization_3.begin_preorder(); // a->b->c->d->e->f
            CHECK_EQ(*p_it, "a");
            p_it++;
            CHECK_EQ(*p_it, "b");
            p_it++;
            CHECK_EQ(*p_it, "c");
            p_it++;
            CHECK_EQ(*p_it, "d");
            p_it++;
            CHECK_EQ(*p_it, "e");
            p_it++;
            CHECK_EQ(*p_it, "f");

            auto p_it_org = organization.begin_preorder(); 
            /*
                organization.add_root("CEO");                                       CEO
                organization.add_sub("CEO", "1st_child");                   1st_child   2nd_child   3rd_child
                organization.add_sub("CEO", "2nd_child");           child_of_1st                        child_of_3rd
                organization.add_sub("CEO", "3rd_child");
                organization.add_sub("1st_child", "child_of_1st");
                organization.add_sub("3rd_child", "child_of_3rd");
            */
            CHECK_EQ(*p_it_org, "CEO");
            p_it_org++;
            CHECK_EQ(*p_it_org, "3rd_child");
            p_it_org++;
            CHECK_EQ(*p_it_org, "child_of_3rd");
            p_it_org++;
            CHECK_EQ(*p_it_org, "2nd_child");
            p_it_org++;
            CHECK_EQ(*p_it_org, "1st_child");
            p_it_org++;
            CHECK_EQ(*p_it_org, "child_of_1st");


        }
        
        SUBCASE("level_order:")
        {
            auto l_it = organization_3.begin_level_order();
            CHECK_EQ(*l_it, "a");
            l_it++;
            CHECK_EQ(*l_it, "b");
            l_it++;
            CHECK_EQ(*l_it, "c");
            l_it++;
            CHECK_EQ(*l_it, "d");
            l_it++;
            CHECK_EQ(*l_it, "e");
            l_it++;
            CHECK_EQ(*l_it, "f");

            auto l_it_org = organization.begin_level_order(); 
            CHECK_EQ(*l_it_org, "CEO");
            l_it_org++;
            CHECK_EQ(*l_it_org, "1st_child");
            l_it_org++;
            CHECK_EQ(*l_it_org, "2nd_child");
            l_it_org++;
            CHECK_EQ(*l_it_org, "3rd_child");
            l_it_org++;
            CHECK_EQ(*l_it_org, "child_of_1st");
            l_it_org++;
            CHECK_EQ(*l_it_org, "child_of_3rd");
        }

        
        SUBCASE("reverse_level_order")
        {
            auto l_it = organization_3.begin_reverse_order();
            CHECK_EQ(*l_it, "f");
            l_it++;
            CHECK_EQ(*l_it, "e");
            l_it++;
            CHECK_EQ(*l_it, "d");
            l_it++;
            CHECK_EQ(*l_it, "c");
            l_it++;
            CHECK_EQ(*l_it, "b");
            l_it++;
            CHECK_EQ(*l_it, "a");

            auto l_it_org = organization.begin_reverse_order(); 
            CHECK_EQ(*l_it_org, "child_of_3rd");
            l_it_org++;
            CHECK_EQ(*l_it_org, "child_of_1st");
            l_it_org++;
            CHECK_EQ(*l_it_org, "3rd_child");
            l_it_org++;
            CHECK_EQ(*l_it_org, "2nd_child");
            l_it_org++;
            CHECK_EQ(*l_it_org, "1st_child");
            l_it_org++;
            CHECK_EQ(*l_it_org, "CEO");
        }
    }
}

TEST_CASE("editting object meanwhile we iterate on will throws an runtime_error exception")
{
    OrgChart organization;
    organization.add_root("CEO");
    organization.add_sub("CEO", "1st_child");
    organization.add_sub("CEO", "2nd_child");
    organization.add_sub("CEO", "3rd_child");
    organization.add_sub("1st_child", "child_of_1st");
    organization.add_sub("3rd_child", "child_of_3rd");
    
    
    SUBCASE("pre_order:")
    {
        auto p_it = organization.begin_preorder();
        p_it++;
        organization.add_sub("CEO","4th_child");
        CHECK_THROWS(p_it++);
    }
    
    SUBCASE("level_order:")
    {
        auto l_it = organization.begin_level_order();
        l_it++;
        organization.add_sub("CEO","4th_child");
        CHECK_THROWS(l_it++);
    }
    
    SUBCASE("reverse_level_order")
    {
        auto rl_it = organization.begin_reverse_order();
        rl_it++;
        organization.add_sub("CEO","4th_child");
        CHECK_THROWS(rl_it++);
    }
}


