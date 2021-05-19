#include <bits/stdc++.h>
#include "MemoryUnit.h"
#define fo(i, N) for (int i = 0 ; i < N; i++)
using namespace std;

string *InstructionMemory = new string[64000]; //Instructions
string *MemArray = new string[1048576]; //DRAM
// string MemArray[100];
int currInstrId[64] = {0};
int currVarId[64] = {0};
const int Partition =  16384; //16 rows to one core 1024 x 32
map<string, int> addofLabels[64];
map<string, int> addofVars[64];
int getIndexofChar(string str, char c);
template <class T>
string to_string(T t, ios_base &(*f)(ios_base &));
MemoryUnit :: MemoryUnit()
{
    for (int it = 0; it < 1048576; it++)
        MemArray[it] = "";
    fo(i, 1000*64){
        InstructionMemory[i] = "";
    }
    for(int i = 0; i<64; i++) {
        currInstrId[i] = 1000 * i;
        currVarId[i] = Partition * i;
    }
}
void MemoryUnit :: storeInstr(string instruction,int core)
{
    
    if (instruction.find(":") != string::npos)
    {
        //cout << "instr -> " << "XX" << (instruction.substr(0, getIndexofChar(instruction, ':'))) << "XX" << " id-> " << currInstrId << endl;
        addofLabels[core].insert(pair<string, int>(instruction.substr(0, getIndexofChar(instruction, ':')), currInstrId[core]));
    }
    else
    {
        InstructionMemory[currInstrId[core]] = instruction;

        currInstrId[core]+=1;
    }
}
int MemoryUnit :: getAddOfLabel(string label, int core)
{
    if (addofLabels[core].find(label) == addofLabels[core].end())
    {
        cout << endl;
        cout << "INVALID Branch Detected!! : " << label << endl;
        throw exception();
    }
    return addofLabels[core].at(label);
}
string MemoryUnit :: getCurrInstr(int current, int core)
{
    return InstructionMemory[current + 1000*core];
}
void MemoryUnit :: setData(string variable, int value, int core)                //Modified
{
    if (addofVars[core].find(variable) == addofVars[core].end())
    {
        addofVars[core][variable] = currVarId[core];
        currVarId[core]+=4;
    }
    //valofVars[addofVars[variable]] = value;
    MemArray[addofVars[core][variable]] = to_string(value);
}
int MemoryUnit :: get_var_add(string variable, int core){
    if (addofVars[core].find(variable) == addofVars[core].end())
    {
        cout << "INVALID variable Accessed!! " << endl;
        throw exception();
    }
    return addofVars[core][variable];
}
int MemoryUnit :: getData(string variable, int core)
{
    if (addofVars[core].find(variable) == addofVars[core].end())
        throw exception();
    
    //return ValofVars[addofVars[variable]];
    stringstream ss(MemArray[addofVars[core][variable]]);
    int val; ss >> val;
    return val;
}
void MemoryUnit :: setDataAdd(int address, int value, int core)
{
    MemArray[address + Partition*core] = to_string(value);
}
int MemoryUnit :: getDataAdd(int address, int core)
{
    if (MemArray[address + Partition*core] == ""){
        return 0;
    }
    stringstream ss(MemArray[address + Partition*core]);
    int val; ss >> val;
    return val;
}
void MemoryUnit :: printMemDataContent(int N)

{
    cout << "Memory content at the end of the execution" << endl << endl;
    for(int cr = 0; cr < N; cr++){
        cout << "Core #" << cr+1 << ":" << endl;
        for (int y = Partition * cr; y < (cr+1) * Partition; y+=4)
        {
            if (MemArray[y] == "") continue;
            stringstream ss(MemArray[y]); int val; ss >> val; 
            cout << y % Partition << '-' << (y+3) % Partition <<":" << ' ' << to_string<long>(val, hex) << endl;
        }
        cout << endl;
    } 
}
int getIndexofChar(string str, char c){
    int a = 0;
    while (str[a] != c){
        a++;
    }
    return a;
}
template <class T>
string to_string(T t, ios_base &(*f)(ios_base &)) // DONT change its name. will not work.
{
    ostringstream oss;
    oss << f << t;
    return oss.str();
}