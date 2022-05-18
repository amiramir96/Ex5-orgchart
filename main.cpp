#include "OrgChart.hpp"

using namespace ariel;

int main()
{
    OrgChart CS_ariel;
    CS_ariel.add_root("boaz ben moshe");
    CS_ariel.add_sub("boaz ben moshe", "gil ben arzi");
    CS_ariel.add_sub("boaz ben moshe", "amit dvir");
    CS_ariel.add_sub("boaz ben moshe", "dan hefez & elad horev");
    CS_ariel.add_sub("boaz ben moshe", "dan hefez & elad horev");
    CS_ariel.add_sub("dan hefez & elad horev", "michael");
    CS_ariel.add_sub("dan hefez & elad horev", "shani");
    CS_ariel.add_sub("shani", "probability 2");
    CS_ariel.add_sub("michael", "algo2");
    CS_ariel.add_sub("amit dvir", "yuval");
    CS_ariel.add_sub("gil ben arzi", "ivegeni (ashem mishpha kashe midai lebitui xD)");
    CS_ariel.add_sub("ivegeni (ashem mishpha kashe midai lebitui xD)", "class sys_prog_b");
    CS_ariel.add_sub("ivegeni (ashem mishpha kashe midai lebitui xD)", "class sys_prog_a");
    
    OrgChart sys_prog_b;
    sys_prog_b.add_root("harel segal");
    sys_prog_b.add_sub("harel segal", "haim mashu");
    sys_prog_b.add_sub("harel segal", "mor basan");
    sys_prog_b.add_sub("mor basan", "tal");
    sys_prog_b.add_sub("mor basan", "nofar");
    sys_prog_b.add_sub("mor basan", "ivgeni");
    sys_prog_b.add_sub("nofar", "hanfanim");
    sys_prog_b.add_sub("ivgeni", "not alot of students");
    sys_prog_b.add_sub("ivgeni", "students who didnt catched spot at another classes :P");

    std::cout <<"we have two OrgChart ready groups: CS_ariel && sys_prog_b"<<std::endl;
    
    int flag = '\0';
    std::cout << "to print CS_ariel preorder press 1, levelorder press 2, reverselevel order press 3"<< std::endl;
    std::cout << "to print sys_prog_b preorder press 4, levelorder press 5, reverselevel order press 6"<< std::endl;
    std::cout << "press 10 to quit" << std::endl;

    for(;;)
    {
        std::cin >> flag;
        std::cout << std::endl;

        if (flag == 1)
        {
            for (auto preit = CS_ariel.begin_preorder(); preit != CS_ariel.end_preorder(); preit++)
            {
                std::cout << *preit << ", ";
            }
        }
        else if (flag == 2)
        {
            std::cout << CS_ariel;
        }
        else if (flag == 3)
        {
            for (auto r_it = CS_ariel.begin_reverse_order(); r_it != CS_ariel.reverse_order(); r_it++)
            {
                std::cout << *r_it << ", ";
            }
        }
        else if (flag == 4)
        {
            for (auto psys_it = sys_prog_b.begin_preorder(); psys_it != CS_ariel.end_preorder(); psys_it++)
            {
                std::cout << *psys_it << ", ";
            }
        }
        else if (flag == 5)
        {
            std::cout << sys_prog_b;
        }
        else if (flag == 6)
        {
            for (auto rsys_it = sys_prog_b.begin_reverse_order(); rsys_it != CS_ariel.reverse_order(); rsys_it++)
            {
                std::cout << *rsys_it << ", ";
            }
        }
        else if (flag == 10)
        {break;}
    }
    std::cout << "cya next time ^^\n" << std::endl;

    return 1;
}