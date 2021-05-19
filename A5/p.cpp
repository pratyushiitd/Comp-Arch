#include <vector>
#include <iostream>
// class instruction
// {
//     string type;
//     string p1,p2,p3;
//     instruction(string instrc){

//     }
// }
string getinstructiontype(string instruction)
{
    return 'lw';
}
string getfirstinstrpos(string instruction)
{
    return "$r1";
}
bool isnewinstruction()
{
    return false;
}
void insertoDRAMqueue()
{
}
void processDRAMqueue()
{
}
class DRAM_queue
{
public:
    vector<pair<string, int>> queue;
    DRAM_queue()
    {
    }
    void insert(string instruction, int core)
    {
        this->queue.push_back(make_pair(instruction, core));
    }
    void processDRAMqueue(int clock, vector<string> thiscycleinfo)
    {
    }
};

void simulate(vector<vector<string>> instructions)
{
    // instructions = ith position contains instruction vector of ith processor
    int clock = 0;
    int n = instructions.size();
    bool complete = false;
    vecto<vector<vector<string>>> cycleinfoofalln;
    DRAM_queue DQ = new DRAM_queue();
    vector<int> programcounter = {0};
    while (!complete)
    {
        clock++;
        for (int i = 0; i < n; i++)
        {
            vector<string> thiscyleinfo;
            //
            string currentinstruction = instrctions[i][programcounter[i]];
            if (isnewinstruction())
            {

                string instructiontype = getinstructiontype(currentinstruction);
                if (instructiontype == "lw" || instructiontype == "sw")
                {
                    thiscycleinfo.push_back(currentinstruction + " DRAM request issued");
                    DQ.insertoDRAMqueue(instruction, i);
                }
                else if (instructiontype == "add" || instructiontype == "sub" || instructiontype = "mul")
                {
                    thiscycleinfo.push_back(currentinstruction);
                }
                else if (instructiontype == "addi")
                {
                    thiscycleinfo.push_back(currentinstruction);
                }
                programcounter[i]++;
            }
            processDRAMqueue(clock, thiscycleinfo);
            //
            cycleinfoofalln[i].push_back(thiscycleinfo);
        }
    }
}

int main(int argc, char const *argv[])
{

    return 0;
}
