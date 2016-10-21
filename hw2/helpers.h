#ifndef HELPERS_H
#define HELPERS_H

#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

extern double INIT_TEMP;
extern const double FINAL_TEMP;
extern const double CHIP_RATIO;
extern const int N_MOVES;
extern double RATIO;
extern const double LAMBDA_Tf;
extern const int I_SEED;
extern const int SIZE;   
extern const double VALUE;
extern const double EPSILON;

double schedule(double t);
double getRandomZeroOne();
int getRandomZeroTwo();
bool isOperator(char val);
std::string Rand_Move(std::string curr);
int getNextOperandRight(std::string curr, int index);
int getNextOperandLeft(std::string curr, int index);
int getNextOperatorRight(std::string curr, int iter);
int getNextOperatorLeft(std::string curr, int iter);
std::vector<Module::Module> read_input();
double getCost(std::string NPE, std::vector<Module::Module>& modules);
void simAnn(const std::vector<Module::Module>& modules);
std::string m1_swap(std::string, int first, int second);
std::string m2_swap(std::string, int first, int second);
std::string m3_swap(std::string, int first, int second);
char complementOperator(char input);
bool checkNPE(std::string input);
std::string cost(std::string NPE, const std::vector<Module::Module>& modules);
std::string simAnn(std::string NPE, const std::vector<Module::Module>& modules);

#endif
