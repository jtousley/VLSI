#include "Module.h"
#include "Skewed.h"
#include "helpers.h"

std::random_device random_dev;
std::mt19937 mt_gen(I_SEED);
//std::mt19937 mt_gen(random_dev());
std::uniform_real_distribution<double> temp_distribution(0.0, 1.0);
std::uniform_int_distribution<int> move_type_distribution(0, 2);
std::uniform_int_distribution<int> length_distribution(0, INT_MAX);

double INIT_TEMP = -1.0;
const double FINAL_TEMP = 0.0;
const double CHIP_RATIO = 2.0;
const int N_MOVES = 10;
double RATIO = 0.85;
const double LAMBDA_Tf = 0.005;
const int I_SEED = 3;   // random number seed, does not actually produce random values
const int SIZE = 6;     // n
const double VALUE = 0.99;      // P
const double EPSILON = 0.001;


double schedule(double t)
{
    if( t < LAMBDA_Tf * INIT_TEMP )
    {
        RATIO = 0.1;
    }
    return t * RATIO;
}

double getRandomZeroOne()
{
    return temp_distribution(mt_gen);
}

int getRandomZeroTwo()
{
    return move_type_distribution(mt_gen) + 1;
}

int getPseudoRand()
{
    return length_distribution(mt_gen);
}

bool isOperator(char val)
{
    return (val == 'H' || val == 'V') ? true : false;
}

int getNextOperandRight(std::string curr, int index)
{
    for(unsigned int i = index + 1; i < curr.size(); i++)
    {
        if((!isOperator(curr[i])))
        {
            return i;
        }
    }
    return -1;
}

int getNextOperandLeft(std::string curr, int index)
{
    for(int i = index - 1; i >= 0; i--)
    {
        if((!isOperator(curr[i])))
        {
            return i;
        }
    }
    return -1;
}

int getNextOperatorRight(std::string curr, int iter)
{
    int toRet = iter;
    if(iter >= (int)curr.size())
    {
        return toRet;
    }
    for(unsigned int i = iter + 1; i < curr.size(); i++)
    {
        if((isOperator(curr[i])))
        {
            toRet = i;
        }
        else
        {
            return toRet;
        }
    }
    return toRet;
}

int getNextOperatorLeft(std::string curr, int iter)
{
    int toRet = iter;

    for(int i = iter - 1; i >= 0; i--)
    {
        if((isOperator(curr[i])))
        {
            toRet = i;
        }
        else
        {
            return toRet;
        }
    }
    return toRet;
}

std::string Rand_Move(std::string curr)
{
    int move_type = getRandomZeroTwo();
    std::string toRet = curr;

    if(move_type == 1) // m1 move
    {
        bool found = false;
        while(!found)
        {
            int iter = getPseudoRand() % (curr.length() - 1);
            if(!isOperator(curr[iter]))
            {
                int index = 0;
                if((index = getNextOperandRight(curr, iter)) != -1)
                {
                    toRet = m1_swap(curr, iter, index);
                    found = true;
                }
                else if((index = getNextOperandLeft(curr, iter)) != -1)
                {
                    toRet = m1_swap(curr, index, iter);
                    found = true;
                }
            } // if operand 
        } // while
    } // if move type

    else if(move_type == 2)
    {
        bool found = false;
        while(!found)
        {
            int iter = (getPseudoRand() % curr.length() - 1);
            if(isOperator(curr[iter]))
            {
                int index = 0;
                if((index = getNextOperatorRight(curr, iter)))
                {
                    toRet = m2_swap(curr, iter, index);
                    found = true;
                }
                else if((index = getNextOperatorLeft(curr, iter)))
                {
                    toRet = m2_swap(curr, index, iter);
                    found = true;
                }
            } // if operator
            else
                continue;
        } // while
    } // move type

    else if(move_type == 3)
    {
        bool isNPE = false;
        bool found = false;
        while(!isNPE && found)
        {
            int iter = (getPseudoRand() % curr.length() - 1);
            int index = 0;
            if(isOperator(curr[iter])) // is operator
            {
                if((index = getNextOperandRight(curr, iter)) != -1)
                {
                    if( (int)std::abs(index - iter) == 1 )
                    {
                        toRet = m3_swap(curr, iter, index);
                        found = true;
                    }
                }
                else if( (index = getNextOperandLeft(curr, iter)) != -1 )
                {
                    if( (int)std::abs(index - iter) == 1 )
                    {
                        toRet = m3_swap(curr, index, iter);
                        found = true;
                    }
                }
            }
            else if(!isOperator(curr[iter])) // is operand
            {
                if( (index = getNextOperatorRight(curr, iter)) != -1 )
                {
                    if( (int)std::abs(index - iter) == 1 )
                    {
                        toRet = m3_swap(curr, iter, index);
                        found = true;
                    }
                }
                else if( (index = getNextOperatorLeft(curr, iter)) != -1 )
                {
                    if( (int)std::abs(index - iter) == 1 )
                    {
                        toRet = m3_swap(curr, index, iter);
                        found = true;
                    }
                }
            }
            isNPE = checkNPE(toRet);
        }
    }
    else
    {
        std::cout << "Error, bad move type" << std::endl;
    }

    return toRet;
}

std::string m1_swap(std::string input, int first, int second)
{
    std::string toRet = input;
    char temp = toRet[first];
    toRet[first] = toRet[second];
    toRet[second] = temp;

    return toRet;
}

char complementOperator(char input)
{
    if(input == 'H')
    {
        return 'V';
    }
    else
    {
        return 'H';
    }
}

std::string m2_swap(std::string input, int first, int second)
{
    std::string toRet = input;
    for(int i = first; i <= second; i++)
    {
        toRet[i] = complementOperator(toRet[i]);
    }
    return toRet;
}

std::string m3_swap(std::string input, int first, int second)
{
    std::string toRet = input;
    char temp = toRet[first];
    toRet[first] = toRet[second];
    toRet[second] = temp;

    return toRet;
}

bool checkNPE(std::string input)
{
    int operands = 0;
    int operators = 0;
    for(unsigned int i = 0; i < input.size(); i++)
    {
        if(isOperator(input[i]))
        {
            operators++;
        }
        else
        {
            operands++;
        }
        if( !(operands > operators) )
        {
            return false;
        }
    }
    return true;
}
