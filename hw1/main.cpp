#include "Module.h"
#include "Skewed.h"
#include <vector>
#include <cmath>
#include <algorithm>

#define INPUT_FILE "input_file.txt"
#define TEST_CASE_ONE "12V3V4V5V6V7V8V9VaVbVcVdVeVfVgViVjVkVlV"
#define TEST_CASE_TWO "12H3H4H5H6H7H8H9HaHbHcHdHeHfHgHiHjHkHlH"
#define TEST_CASE_THREE "213546H7VHVa8V9HcVHgHibdHkVHfeHVlHVjHVH"

std::vector<Module::Module> read_input();
std::string cost();


int main()
{
    std::cout << cost();
    
    return 0;
}

std::string cost()
{
    std::vector<Module::Module> modules = read_input();
    std::string TEST_ONE = TEST_CASE_ONE;
    std::string TEST_TWO = TEST_CASE_TWO;
    std::string TEST_THREE = TEST_CASE_THREE;
    std::stringstream ss;
    std::transform(TEST_ONE.begin(), TEST_ONE.end(), TEST_ONE.begin(), [](unsigned char c){ return std::toupper(c); } );
    std::transform(TEST_TWO.begin(), TEST_TWO.end(), TEST_TWO.begin(), [](unsigned char c){ return std::toupper(c); } );
    std::transform(TEST_THREE.begin(), TEST_THREE.end(), TEST_THREE.begin(), [](unsigned char c){ return std::toupper(c); } );
    
    Skewed::Skewed tree_one(TEST_ONE);
    Skewed::Skewed tree_two(TEST_TWO);
    Skewed::Skewed tree_three(TEST_THREE);
    
    for(unsigned int i = 0; i < modules.size(); i ++)
    {
        tree_one.Replace(modules[i]);
        tree_two.Replace(modules[i]);
        tree_three.Replace(modules[i]);
    }

    ss << "FIRST:\n";
    ss << tree_one.Get_Post_Order() << std::endl;
    ss << tree_one.Find_Optimal() << std::endl;
    ss << "SECOND:\n";
    ss << tree_two.Get_Post_Order() << std::endl;
    ss << tree_two.Find_Optimal() << std::endl;
    ss << "THIRD:\n";
    ss << tree_three.Get_Post_Order() << std::endl;
    ss << tree_three.Find_Optimal() << std::endl;

    return ss.str();
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
            //width = std::sqrt(area/ratio);
            //height = area / width;
            std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::toupper(c); } );
            Module::Module curr(name, area, ratio, width, height);
            gen_modules.push_back(curr);
        }
    }
    
    return gen_modules;
}

