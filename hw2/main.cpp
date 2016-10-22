#include "Module.h"
#include "Skewed.h"
#include "helpers.h"

#include <vector>
#include <cmath>
#include <algorithm>

int main()
{
    std::vector<Module::Module> modules = read_input();

    std::cout << "FIRST:\n";
    std::cout << "INITIAL:\n";
    std::cout << cost(TEST_CASE_ONE, modules);
    std::cout << std::endl << "FINAL:\n";
    std::cout << simAnn(TEST_CASE_ONE, modules);
    std::cout << std::endl << std::endl;

    std::cout << "SECOND:\n";
    std::cout << "INITIAL:\n";
    std::cout << cost(TEST_CASE_TWO, modules);
    std::cout << std::endl << "FINAL:\n";
    std::cout << simAnn(TEST_CASE_TWO, modules);
    std::cout << std::endl << std::endl;

    std::cout << "THIRD:\n";
    std::cout << "INITIAL:\n";
    std::cout << cost(TEST_CASE_THREE, modules);
    std::cout << std::endl << "FINAL:\n";
    std::cout << simAnn(TEST_CASE_THREE, modules);

    return 0;
}

std::vector<Module::Module> read_input()
{
    std::ifstream fin;
    std::string line = "";
    std::string name = "";
    double area = 0;
    double ratio = 0;
    double height = 0;
    double width = 0;
    
    std::vector<Module::Module> gen_modules;
    
    fin.open(INPUT_FILE);
    if(!fin.is_open())
    {
        std::string err = "Could not open input file: " + std::string(INPUT_FILE);
        //throw(err);
        std::cerr << err << std::endl;
        exit(1);
    }
    
    while(std::getline(fin, line))
    {
        if(line != "")
        {
            std::stringstream ss_line(line);
            ss_line >> name;
            ss_line >> area;
            ss_line >> ratio;
            height = std::sqrt(area * ratio);
            width = height / ratio;
            std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::toupper(c); } );
            Module::Module curr(name, area, ratio, width, height);
            gen_modules.push_back(curr);
        }
    }
    
    return gen_modules;
}

std::string cost(std::string NPE, const std::vector<Module::Module>& modules)
{
    std::stringstream ss;
    std::transform(NPE.begin(), NPE.end(), NPE.begin(), [](unsigned char c){ return std::toupper(c); } );
    
    Skewed::Skewed tree(NPE);
    
    for(unsigned int i = 0; i < modules.size(); i ++)
    {
        tree.Replace(modules[i]);
    }

    ss << tree.Get_Post_Order() << std::endl;
    ss << tree.Find_Optimal() << std::endl;

    return ss.str();
}

double getCost(std::string NPE, const std::vector<Module::Module>& modules)
{
    Skewed::Skewed tree(NPE);
    for(unsigned int i = 0; i < modules.size(); i++)
    {
        tree.Replace(modules[i]);
    }
    return tree.Find_Optimal();
}

std::string simAnn(std::string NPE, const std::vector<Module::Module>& modules)
{
    if(INIT_TEMP < 0)
    {
        INIT_TEMP *= -1;
    }
    std::transform(NPE.begin(), NPE.end(), NPE.begin(), [](unsigned char c){ return std::toupper(c); } );

    double TEMP = INIT_TEMP;
    std::string curr_place = NPE;
    std::string new_place = "";
    std::string best_solution = NPE;
    double curr_place_cost = 0.0;
    double new_place_cost = 0.0;
    double best_solution_cost = getCost(best_solution, modules);
    double delta_cost = 0.0;
    int moves = 0;
    int uphill_moves = 0;
    int rejected_moves = 0;
    int CAPITAL_N = N_MOVES * modules.size();

    //while( TEMP > FINAL_TEMP )
    while( (TEMP > FINAL_TEMP) && (((double)rejected_moves / (double)(moves + 1)) < 0.95) )
    {
        moves = 0;
        while( (uphill_moves < CAPITAL_N) && (moves < 2*CAPITAL_N) )
        {
            new_place = Rand_Move(curr_place);
            new_place_cost = getCost(new_place, modules);
            curr_place_cost = getCost(curr_place, modules);
            delta_cost = new_place_cost - curr_place_cost;
            if((delta_cost < 0))
            {
                curr_place = new_place;
                if(curr_place_cost < best_solution_cost)
                {
                    best_solution = curr_place;
                }
            }
            else if(exp(delta_cost / TEMP * -1) > getRandomZeroOne())
            {
                curr_place = new_place;
                uphill_moves++;
            }
            else
            {
                rejected_moves++;
            }
            moves++;
        }
        TEMP = schedule(TEMP);
    }

    return cost(curr_place, modules);
}
