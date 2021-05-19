
#include <bits/stdc++.h>

using namespace std;

class MemoryUnit
{
public:
    MemoryUnit();
    void storeInstr(string instruction,int core);
    int getAddOfLabel(string label, int core);
    string getCurrInstr(int current, int core);
    void setData(string variable, int value, int core);
    int get_var_add(string variable, int core);
    int getData(string variable, int core);
    void setDataAdd(int address, int value, int core);
    int getDataAdd(int address, int core);
    void printMemDataContent(int N);
};