#include <bits/stdc++.h>
#include "RegisterFile.h"
using namespace std;


template <class T>
string to_string(T t, ios_base &(*f)(ios_base &)) // DONT change its name. will not work.
{
    ostringstream oss;
    oss << f << t;
    return oss.str();
}
int regArray[64][32];
string regNameArray[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};    
int RegisterFile :: get_regno(string reg)
{
    // cout << reg << endl;
    int regno = -1;
    if    (reg.compare("$zero") == 0) regno = 0;
    else if (reg.compare("$at") == 0) regno = 1;
    else if (reg.compare("$v0") == 0) regno = 2;
    else if (reg.compare("$v1") == 0) regno = 3;
    else if (reg.compare("$a0") == 0) regno = 4;
    else if (reg.compare("$a1") == 0) regno = 5;
    else if (reg.compare("$a2") == 0) regno = 6;
    else if (reg.compare("$a3") == 0) regno = 7;
    else if (reg.compare("$t0") == 0) regno = 8;
    else if (reg.compare("$t1") == 0) regno = 9;
    else if (reg.compare("$t2") == 0) regno = 10;
    else if (reg.compare("$t3") == 0) regno = 11;
    else if (reg.compare("$t4") == 0) regno = 12;
    else if (reg.compare("$t5") == 0) regno = 13;
    else if (reg.compare("$t6") == 0) regno = 14;
    else if (reg.compare("$t7") == 0) regno = 15;
    else if (reg.compare("$s0") == 0) regno = 16;
    else if (reg.compare("$s1") == 0) regno = 17;
    else if (reg.compare("$s2") == 0) regno = 18;
    else if (reg.compare("$s3") == 0) regno = 19;
    else if (reg.compare("$s4") == 0) regno = 20;
    else if (reg.compare("$s5") == 0) regno = 21;
    else if (reg.compare("$s6") == 0) regno = 22;
    else if (reg.compare("$s7") == 0) regno = 23;
    else if (reg.compare("$t8") == 0) regno = 24;
    else if (reg.compare("$t9") == 0) regno = 25;
    else if (reg.compare("$k0") == 0) regno = 26;
    else if (reg.compare("$k1") == 0) regno = 27;
    else if (reg.compare("$gp") == 0) regno = 28;
    else if (reg.compare("$sp") == 0) regno = 29;
    else if (reg.compare("$fp") == 0) regno = 30;
    else if (reg.compare("$ra") == 0) regno = 31;
    if (regno == -1)
    {
        cout << endl;
        cout << "INVALID REGISTER DETECTED!! : " << reg << endl;
        throw exception();
    }
    return regno;
}

RegisterFile :: RegisterFile()
{
    for(int i = 0; i < 64; i++){
    for (int it = 0; it < 32; it++) regArray[i][it] = 0;
    }
}
int RegisterFile :: get_register_data(int core, int register_num)
{
    return regArray[core][register_num];
}
void RegisterFile :: set_register_data(int core, int register_num, int data)
{
    if (register_num == 0)
    {
        cout << endl;
        cout << "$zero can not be set  " << endl;
        throw exception();
    }
    regArray[core][register_num] = data;
}
void RegisterFile :: printRegisters(int N)
{
    for(int j = 0; j < N; j++){
        cout << "Core #" << to_string(j+1) << " : Contents of Register file" << "\n";
        for (int i = 0; i < 31; i++)
        {
            cout << regNameArray[i] << ": " << to_string<long>(regArray[j][i], hex) << ", ";
        }
        cout << regNameArray[31] << ": " << to_string<long>(regArray[j][31], hex) << endl << endl;
    }
}