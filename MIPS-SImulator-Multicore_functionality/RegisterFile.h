#include <bits/stdc++.h>

using namespace std;

class RegisterFile
{
public:    
    int get_regno(string reg);
    RegisterFile();
    int get_register_data(int core, int register_num);
    void set_register_data(int core, int register_num, int data);
    void printRegisters(int N);
};