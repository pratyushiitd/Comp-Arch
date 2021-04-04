#include "stdio.h"
#include "iostream"
#include "fstream"
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
int row_access_delay = 10;
int col_access_delay = 2;
int partition = 1048576 / 2;
template <class T>
string to_string(T t, ios_base &(*f)(ios_base &)) // DONT change its name. will not work.
{
    ostringstream oss;
    oss << f << t;
    return oss.str();
}
int getIndexofChar(string str, char c){
    int a = 0;
    while (str[a] != c){
        a++;
    }
    return a;
}
int count_wht(string s){
    int cnt = 0;
    for(int it=0; it<s.length(); it++){
        s[it] == ' ' ? cnt+=1:cnt+=0;
    }
    return cnt;
}
string remove_extra_whitespaces(const string &input)
{
    string output;
    unique_copy(input.begin(), input.end(), back_insert_iterator<string>(output), [](char a, char b) { return isspace(a) && isspace(b); });
    if (output[0] == ' ')
    {
        output = output.substr(1);
    }
    for (int i = 0; i < output.length() - 1; i++)
    {
        if (output[i] == ',' && output[i + 1] != ' ')
        {
            output = output.substr(0, i + 1) + " " + output.substr(i + 1);
        }
    }

    return output;
}
vector<string> getInstrucVec(fstream &infile)
{
    vector<string> temp;
    string test2;
    while (getline(infile, test2))
    {
        temp.push_back(test2);
    }
    return temp;
}
class RegisterFile
{
    /*
    $zero     $0            Hardware set to 0
    $at       $1            Assembler temporary
    $v0 - $v1 $2 - $3       Function result (low/high)
    $a0 - $a3 $4 - $7       Argument Register 1
    $t0 - $t7 $8 - $15      Temporary registers
    $s0 - $s7 $16 - $23     Saved registers
    $t8 - $t9 $24 - $25     Temporary registers
    $k0 - $k1 $26 - $27     Reserved for OS kernel
    $gp       $28           Global pointer
    $sp       $29           Stack pointer
    $fp       $30           Frame pointer
    $ra       $31           Return address
    */
private:
    int regArray[32];
    string regNameArray[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

    int get_regno(string reg)
    {
        // cout << reg << endl;
        int regno = -1;
        if (reg.compare("$zero") == 0)
            regno = 0;
        else if (reg.compare("$at") == 0)
            regno = 1;
        else if (reg.compare("$v0") == 0)
            regno = 2;
        else if (reg.compare("$v1") == 0)
            regno = 3;
        else if (reg.compare("$a0") == 0)
            regno = 4;
        else if (reg.compare("$a1") == 0)
            regno = 5;
        else if (reg.compare("$a2") == 0)
            regno = 6;
        else if (reg.compare("$a3") == 0)
            regno = 7;
        else if (reg.compare("$t0") == 0)
            regno = 8;
        else if (reg.compare("$t1") == 0)
            regno = 9;
        else if (reg.compare("$t2") == 0)
            regno = 10;
        else if (reg.compare("$t3") == 0)
            regno = 11;
        else if (reg.compare("$t4") == 0)
            regno = 12;
        else if (reg.compare("$t5") == 0)
            regno = 13;
        else if (reg.compare("$t6") == 0)
            regno = 14;
        else if (reg.compare("$t7") == 0)
            regno = 15;
        else if (reg.compare("$s0") == 0)
            regno = 16;
        else if (reg.compare("$s1") == 0)
            regno = 17;
        else if (reg.compare("$s2") == 0)
            regno = 18;
        else if (reg.compare("$s3") == 0)
            regno = 19;
        else if (reg.compare("$s4") == 0)
            regno = 20;
        else if (reg.compare("$s5") == 0)
            regno = 21;
        else if (reg.compare("$s6") == 0)
            regno = 22;
        else if (reg.compare("$s7") == 0)
            regno = 23;
        else if (reg.compare("$t8") == 0)
            regno = 24;
        else if (reg.compare("$t9") == 0)
            regno = 25;
        else if (reg.compare("$k0") == 0)
            regno = 26;
        else if (reg.compare("$k1") == 0)
            regno = 27;
        else if (reg.compare("$gp") == 0)
            regno = 28;
        else if (reg.compare("$sp") == 0)
            regno = 29;
        else if (reg.compare("$fp") == 0)
            regno = 30;
        else if (reg.compare("$ra") == 0)
            regno = 31;
        // cout << "=" << regno << endl;
        if (regno == -1)
        {
            cout << endl;
            cout << "INVALID REGISTER DETECTED!! : " << reg << endl;
            throw exception();
        }
        return regno;
    }

public:
    RegisterFile()
    {
        for (int it = 0; it < 32; it++)
            regArray[it] = 0;
    }
    int get_register_data(string register_name)
    {
        // if (register_name[0] == '$')
        return regArray[get_regno(register_name)];
        // else
        //     return stoi(register_name);
    }
    void set_register_data(string register_name, int data)
    {
        if (register_name == "$zero")
        {
            cout << endl;
            cout << "$zero can not be set  " << endl;
            throw exception();
        }
        // cout << "register number: " << register_name << " " << data << " " << get_regno(register_name) << endl;
        regArray[get_regno(register_name)] = data;
    }
    void printRegisters()
    {
        cout << "Contents of Register file:\n";
        for (int i = 0; i < 31; i++)
        {
            cout << regNameArray[i] << ": " << to_string<long>(regArray[i], hex) << ", ";
            //cout << "$" << i  << ": " << to_string<long>(regArray[i], hex) << " ";
        }
        cout << regNameArray[31] << ": " << to_string<long>(regArray[31], hex) << endl;
        //cout << "$" << 31  << ": " << to_string<long>(regArray[31], hex) << endl;
    }
};
class MemoryUnit
{
public:
    string *MemArray = new string[1048576];
    // string MemArray[100];
    int currInstrId = 0;
    int currVarId = 0;
    int partition = 1048576 / 2;
    map<string, int> addofLabels;
    map<string, int> addofVars;
    //map<int, int> valofVars;
    MemoryUnit()
    {
        for (int it = 0; it < 1048576; it++)
            MemArray[it] = "";
        currInstrId = 0;
        currVarId = 1048576 / 2;
        partition = 1048576 / 2;
    }
    void storeInstr(string instruction)
    {
        
        if (instruction.find(":") != string::npos)
        {
            //cout << "instr -> " << "XX" << (instruction.substr(0, getIndexofChar(instruction, ':'))) << "XX" << " id-> " << currInstrId << endl;
            addofLabels.insert(pair<string, int>(instruction.substr(0, getIndexofChar(instruction, ':')), currInstrId));
        }
        else
        {
            MemArray[currInstrId] = instruction;

            currInstrId+=1;
        }
    }
    int getAddOfLabel(string label)
    {
        if (addofLabels.find(label) == addofLabels.end())
        {
            cout << endl;
            cout << "INVALID Branch Detected!! : " << label << endl;
            throw exception();
        }
        return addofLabels.at(label);
    }
    string getCurrInstr(int current)
    {
        return MemArray[current];
    }
    void setData(string variable, int value)                //Modified
    {
        if (addofVars.find(variable) == addofVars.end())
        {
            addofVars[variable] = currVarId;
            currVarId+=4;
        }
        //valofVars[addofVars[variable]] = value;
        MemArray[addofVars[variable]] = to_string(value);
    }
    int get_var_add(string variable){
        return addofVars[variable];
    }
    int getData(string variable)
    {
        if (addofVars.find(variable) == addofVars.end())
            return -1;
        
        //return ValofVars[addofVars[variable]];
        stringstream ss(MemArray[addofVars[variable]]);
        int val; ss >> val;
        return val;
    }
    void setDataAdd(int address, int value)
    {
        MemArray[address + partition] = to_string(value);
    }
    int getDataAdd(int address)
    {
        stringstream ss(MemArray[address + partition]);
        int val; ss >> val;
        return val;
    }
    void printMemDataContent()
    {
        cout << "Memory content at the end of the execution:" << endl;
        for (int y = partition; y < 2 * partition; y+=4)
        {
            if (MemArray[y] == "") continue;
            stringstream ss(MemArray[y]); int val; ss >> val; 
        cout << y - partition << '-' << y+3 - partition <<":" << ' ' << to_string<long>(val, hex) << endl;
        } 
    }
};
class RowBuffer
{
public:
    int row_no;
    int back_no;
    string reg;
    bool hault;
    int row_acc;
    int col_acc;
    int col_no;
    string message;
    map<int, int> M;
    RowBuffer(){
        row_no = -1;
        reg = "";
        hault = false;
        row_acc = 0;
        col_acc = 0;
        col_no = -1;
        back_no = -1;
        message = "";
    }
    void UpdateRowBuffer(int row,int col, string reg_s,bool hault, int br){
        if (row != row_no) {
            M[row] += 1;
        }
        row_no = row;
        reg = reg_s;
        hault = false;
        col_no = col;
        back_no = br;
    }
    void UpdateDelays(int r, int c){
        row_acc = r;
        col_acc = c;
    }
    void UpdateHault(bool b){
        hault = true;
    }
    void UpdateMessage(string s){
        message = s;
    }
    void print_buffers(){
        for (const auto &p : M){
            cout << "Row with starting address " << p.first * 1024 << " was loaded " << p.second << " times." << endl; 
        } 
    }
};
void print_req() {
    //cout << "==============================================================" << endl;
    //cout << "Clock cycle executed: " << Clock_cycle << endl;
    cout << "DRAM Request Issued" << endl; 
}
void print_rl(int r){
    cout << "Loading Row " << r << " in Row Buffer." << endl;
}
void print_wl(int r){
    cout << "Writing Back Row " << r << " in DRAM from Row Buffer." << endl;
}
void print_cl(int c){
    cout << "Accessing Column " << c << " in Row Buffer." << endl;
}
pair<int, string> getMemAdd(string add, RegisterFile &registerFile)
{

    size_t start = add.find_first_of("(");
    size_t end = add.find_first_of(")");
    int sz = end - start - 1;
    string reg = add.substr(start + 1, sz);
    stringstream ss(add.substr(0, start));
    int off;
    ss >> off;
    int add_memory = registerFile.get_register_data(reg);
    int final_add = off + add_memory;
    return make_pair(final_add, reg);
}
vector<string> parseInstr(string instruction)
{
    vector<string> ans;
    while (instruction.length() > 0 && (instruction[0] == ' ' || instruction[0] == '\t'))
    {
        instruction = instruction.substr(1);
    }
    while (instruction.length() > 0 && (instruction[instruction.length() - 1] == ' ' || instruction[instruction.length() - 1] == '\n' || instruction[instruction.length() - 1] == '\t'))
    {
        instruction = instruction.substr(0, instruction.length() - 1);
    }
    if (instruction.length() == 0){
        return ans;
    }
    if (instruction.find(":") != string::npos){
        ans.push_back(instruction);
        return ans;
    }
    if (instruction[0] == 'j')
    {
        ans.push_back("j");
        instruction = instruction.substr(1);
        while (instruction.length() > 0 && (instruction[0] == ' ' || instruction[0] == '\t'))
        {
            instruction = instruction.substr(1);
        }
        while (instruction.length() > 0 && (instruction[instruction.length()-1] == ' ' || instruction[instruction.length()-1] == '\t')){
            instruction = instruction.substr(0, instruction.length() - 1);
        }
        ans.push_back(instruction);
        return ans;
    }
    string instr;
    while (instruction.length() > 0 && instruction[0] != ' ')
    {
        instr += instruction[0];
        instruction = instruction.substr(1);
    }
    string registers = "";
    for (int i = 0; i < instruction.length(); i++)
    {
        if (instruction[i] != ' ')
        {
            registers += instruction[i];
        }
    }
    ans.push_back(instr);
    stringstream ss(registers);
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ',');
        ans.push_back(substr);
    }
    return ans;
}
bool chk_empty(string instruction){
    for(int i = 0; i < instruction.length(); i++){
        if ((instruction[i]!=' ') && (instruction[i] != '\t') && (instruction[i] != '\n')) {
            return false;
        }
    }
    return true;
}

void msg_lw(string reg, RowBuffer &rowbuff, RegisterFile &regis){
    int address = rowbuff.row_no * 1024 + rowbuff.col_no;
    string s = "Loaded value from Memory address " + to_string(address) + "-" + to_string(address+3) + " in the register " + reg + "." + "\nValue in Register " + reg + " is: " + to_string(regis.get_register_data(reg));
    rowbuff.UpdateMessage(s);
}
void msg_sw(string reg, RowBuffer &rowbuff, MemoryUnit &mem){
    int address = rowbuff.row_no * 1024 + rowbuff.col_no;
    string s = "Saved value from Register " + reg + " in the Memory address " + to_string(address) + "-" + to_string(address+3) + "." +"\nValue at Memory address " + to_string(address) + "-" + to_string(address+3) + " is: " + to_string(mem.getDataAdd(address));
    rowbuff.UpdateMessage(s);
}
void print_currInstr(string s){
    cout << "Current Instructiion being executed: " << s << endl;
}
void processInstructions(vector<string> instructionVector, RegisterFile &registerFile, MemoryUnit &memory, RowBuffer &rowbuff)
{
    int part = 0;
    int executionOfInstructionCount[999] = {0};
    int Clock_cycle = 1;
    int programCounter = 0;
    for (int i = 0; i < instructionVector.size(); i++)
    {
        string temp = instructionVector[i];
        memory.storeInstr(temp);
    }
    string currentInstr = memory.getCurrInstr(0);
    while (currentInstr != "EOF" || rowbuff.row_acc != 0 || rowbuff.col_acc != 0)
    {
        cout << "==============================================================" << endl;
        //cout << "Current Instruction : " << currentInstr << endl;
        cout << "Clock cycle executed: " << Clock_cycle << endl;
        Clock_cycle++;
        if (rowbuff.row_acc != 0 || rowbuff.col_acc != 0){
                if (rowbuff.row_acc != 0 && (rowbuff.row_acc <= row_access_delay)) print_rl(rowbuff.row_no);
                else if ((rowbuff.row_acc <= 2 * row_access_delay) && (rowbuff.row_acc > row_access_delay)) print_wl(rowbuff.back_no);
                else print_cl(rowbuff.col_no);
            }
        //cout << rowbuff.row_acc << "XXX" << rowbuff.col_acc << "XXX" <<rowbuff.row_no << endl;
        if (rowbuff.col_acc == 1){
            cout << rowbuff.message << endl;
        }
        if (rowbuff.col_acc == 0){
            rowbuff.reg = "";
            rowbuff.hault = false;
            rowbuff.back_no = -1;
            // rowbuff.UpdateRowBuffer(rowbuff.row_no, rowbuff.col_no, "", false, -1);
            rowbuff.UpdateDelays(0, 0);
        }
        else if (rowbuff.col_acc >= 1){
            if (rowbuff.row_acc > 0){
                rowbuff.UpdateDelays(rowbuff.row_acc-1, rowbuff.col_acc);
            }
            else{
                rowbuff.UpdateDelays(rowbuff.row_acc, rowbuff.col_acc-1);
            }
        }
        // if (Clock_cycle >50){
        //     break;
        // }

        if (currentInstr == "EOF" || rowbuff.hault == true){
            continue;
        }
        vector<string> parametersVec = parseInstr(currentInstr);



        if (parametersVec[0] == "add")
        {
            string Rdest = parametersVec[1], Rsrc = parametersVec[2], Src = parametersVec[3];
            if (Rdest != rowbuff.reg && Rsrc != rowbuff.reg && Src != rowbuff.reg){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                int ans = registerFile.get_register_data(Rsrc) + registerFile.get_register_data(Src);
                registerFile.set_register_data(Rdest, ans);
                cout << "Updated value of " << Rdest << " to "<< ans << '.' << endl;
                programCounter++;
            }
            else{
                    rowbuff.UpdateHault(true);
                }
        }
        else if (parametersVec[0] == "sub")
        {
            string Rdest = parametersVec[1], Rsrc = parametersVec[2], Src = parametersVec[3];
            if (Rdest != rowbuff.reg && Rsrc != rowbuff.reg && Src != rowbuff.reg){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                int ans = registerFile.get_register_data(Rsrc) - registerFile.get_register_data(Src);
                registerFile.set_register_data(Rdest, ans);
                cout << "Updated value of " << Rdest << " to "<< ans << '.' << endl;
                programCounter++;
            }
            else{
                    rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "mul")
        {
            string Rdest = parametersVec[1], Rsrc = parametersVec[2], Src = parametersVec[3];
            if (Rdest != rowbuff.reg && Rsrc != rowbuff.reg && Src != rowbuff.reg){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                int ans = registerFile.get_register_data(Rsrc) * registerFile.get_register_data(Src);
                registerFile.set_register_data(Rdest, ans);
                cout << "Updated value of " << Rdest << " to "<< ans << '.' << endl;
                programCounter++;
            }
            else{
                rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "beq")
        {
            string Rsrc1 = parametersVec[1], Src2 = parametersVec[2], label = parametersVec[3];
            if (rowbuff.reg != Rsrc1 && rowbuff.reg != Src2){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                if (registerFile.get_register_data(Rsrc1) == registerFile.get_register_data(Src2))
                {  
                    programCounter = memory.getAddOfLabel(label);
                    cout << "Jumping to label: " << label << endl;
                }
                else {programCounter++;}
            }
            else{
                rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "bne")
        {
            string Rsrc1 = parametersVec[1], Src2 = parametersVec[2], label = parametersVec[3];
            if (rowbuff.reg != Rsrc1 && rowbuff.reg != Src2){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                if (registerFile.get_register_data(Rsrc1) != registerFile.get_register_data(Src2))
                {
                    programCounter = memory.getAddOfLabel(label);
                    cout << "Jumping to label: " << label << endl;
                }
                else
                {
                    programCounter++;
                }
            }
            else{
                rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "slt")
        {
            string Rdest = parametersVec[1], Rsrc1 = parametersVec[2], Src2 = parametersVec[3];
            if (Rdest != rowbuff.reg && Rsrc1 != rowbuff.reg && Src2 != rowbuff.reg){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                if (registerFile.get_register_data(Rsrc1) < registerFile.get_register_data(Src2))
                {
                    registerFile.set_register_data(Rdest, 1);
                    cout << "Updated value of " << Rdest << " to "<< 1 << '.' << endl;
                }
                else
                {
                    registerFile.set_register_data(Rdest, 0);
                    cout << "Updated value of " << Rdest << " to "<< 0 << '.' << endl;
                }
                programCounter++;
            }
            else{
                rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "j")
        {
            string label = parametersVec[1];
            print_currInstr(currentInstr);
            executionOfInstructionCount[programCounter]++;
            if (label.find("$") != string::npos){
                programCounter = getMemAdd(label, registerFile).first;
            }
            else if (isdigit(label[0])){
                stringstream ss(label);
                int instr_add; 
                ss >> instr_add; 
                programCounter = instr_add;
                cout << "Jumping to instruction address: " << instr_add << endl;
            }
            else{
                programCounter = memory.getAddOfLabel(label);
                cout << "Jumping to label: " << label << endl;
            }
        }
        else if (parametersVec[0] == "lw")
        {
            string Rdest = parametersVec[1], mem = parametersVec[2];
            if ((rowbuff.row_acc == 0) && (rowbuff.col_acc == 0)){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
            if (mem.find("(") == string::npos || mem.find(")") == string::npos)
            {
                if (isdigit(mem[0]) == true){
                    stringstream ss(mem);
                    int val; ss >> val;
                    if ((val + part) / 1024 != rowbuff.row_no){
                        //cout << "Hello2"<< endl;
                        print_req();
                        if (rowbuff.row_no == -1){
                            rowbuff.UpdateRowBuffer((val + part) / 1024, (val+part) %1024, Rdest, false, -1 );
                            rowbuff.UpdateDelays(row_access_delay, col_access_delay);
                        }
                        else{
                            //cout << "Hello3"<< endl;
                            int curr = rowbuff.row_no;
                            rowbuff.UpdateRowBuffer((val + part) / 1024, (val+part) %1024, Rdest, false, curr );
                            rowbuff.UpdateDelays(2 * row_access_delay, col_access_delay);
                        }
                    }
                    else{
                        //COLUMN
                        print_req();
                        rowbuff.UpdateRowBuffer(rowbuff.row_no, (val+part) %1024, Rdest, false, -1 );
                        rowbuff.UpdateDelays(0, col_access_delay);
                    }
                    registerFile.set_register_data(Rdest, memory.getDataAdd(val));
                }
                else{
                    int add = memory.get_var_add(mem);
                    if (add / 1024 != rowbuff.row_no){
                        //cout << "Hello2"<< endl;
                        print_req();
                        if (rowbuff.row_no == -1){
                            rowbuff.UpdateRowBuffer(add / 1024, add %1024, Rdest, false, -1 );
                            rowbuff.UpdateDelays(row_access_delay, col_access_delay);
                        }
                        else{
                            //cout << "Hello3"<< endl;
                            int curr = rowbuff.row_no;
                            rowbuff.UpdateRowBuffer(add / 1024, add %1024, Rdest, false, curr );
                            rowbuff.UpdateDelays(2 * row_access_delay, col_access_delay);
                        }
                    }
                    else{
                        //COLUMN
                        print_req();
                        rowbuff.UpdateRowBuffer(rowbuff.row_no, add %1024, Rdest, false, -1 );
                        rowbuff.UpdateDelays(0, col_access_delay);
                    }
                    registerFile.set_register_data(Rdest, memory.getData(mem));
                }
            }
            else
            {
                int mem_add = getMemAdd(mem, registerFile).first + part;
                if (mem_add/ 1024 != rowbuff.row_no){
                        //cout << "Hello2"<< endl;
                        if (rowbuff.row_no == -1){
                            print_req();
                            rowbuff.UpdateRowBuffer(mem_add / 1024, mem_add %1024, Rdest, false, -1 );
                            rowbuff.UpdateDelays(row_access_delay, col_access_delay);
                        }
                        else{
                            //cout << "Hello3"<< endl;
                            int curr = rowbuff.row_no;
                            print_req();
                            rowbuff.UpdateRowBuffer(mem_add/ 1024, mem_add %1024, Rdest, false, curr );
                            rowbuff.UpdateDelays(2 * row_access_delay, col_access_delay);
                        }
                    }
                    else{
                        //COLUMN
                        print_req();
                        rowbuff.UpdateRowBuffer(rowbuff.row_no, mem_add %1024, Rdest, false, -1 );
                        rowbuff.UpdateDelays(0, col_access_delay);
                    }
                registerFile.set_register_data(Rdest, memory.getDataAdd(mem_add - part));
            }
            programCounter++;
            msg_lw(Rdest, rowbuff, registerFile);
            }
            else{
                rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "sw")
        {
            string Rdest = parametersVec[1], mem = parametersVec[2];
            if ((rowbuff.row_acc == 0) && (rowbuff.col_acc == 0)){
                //cout << "Hello1"<< endl;
                //cout << brk << "sda";
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
            if (mem.find("(") == string::npos || mem.find(")") == string::npos)
            {
                if (isdigit(mem[0]) == true){
                    stringstream ss(mem);
                    int val; ss >> val;
                    if ((val + part) / 1024 != rowbuff.row_no){
                        //cout << "Hello2"<< endl;
                        print_req();
                        if (rowbuff.row_no == -1){
                            rowbuff.UpdateRowBuffer((val + part) / 1024, (val+part) %1024, "", false, -1 );
                            rowbuff.UpdateDelays(row_access_delay, col_access_delay);
                        }
                        else{
                            //cout << "Hello3"<< endl;
                            int curr = rowbuff.row_no;
                            rowbuff.UpdateRowBuffer((val + part) / 1024, (val+part) %1024, "", false, curr );
                            rowbuff.UpdateDelays(2 * row_access_delay, col_access_delay);
                        }
                    }
                    else{
                        //COLUMN
                        print_req();
                        rowbuff.UpdateRowBuffer(rowbuff.row_no, (val+part) %1024, "", false, -1 );
                        rowbuff.UpdateDelays(0, col_access_delay);
                    }
                    memory.setDataAdd(val, registerFile.get_register_data(Rdest));
                }
                else{
                    int add = memory.get_var_add(mem);
                    if (add / 1024 != rowbuff.row_no){
                        print_req();
                        if (rowbuff.row_no == -1){
                            
                            //cout << "Hello4"<< endl;
                            rowbuff.UpdateRowBuffer(add / 1024, add %1024, "", false, -1 );
                            rowbuff.UpdateDelays(row_access_delay, col_access_delay);
                        }
                        else{
                            //cout << "Hello5"<< endl;
                            int curr = rowbuff.row_no;
                            rowbuff.UpdateRowBuffer(add / 1024, add %1024, "", false, curr );
                            rowbuff.UpdateDelays(2 * row_access_delay, col_access_delay);
                        }
                    }
                    else{
                        //COLUMN
                        print_req();
                        rowbuff.UpdateRowBuffer(rowbuff.row_no, add %1024, "", false, -1 );
                        rowbuff.UpdateDelays(0, col_access_delay);
                    }
                    memory.setData(mem, registerFile.get_register_data(Rdest));
                }
            }
            else
            {
                //cout << "Hello6"<< endl;
                int mem_add = getMemAdd(mem, registerFile).first;
                string reg = getMemAdd(mem, registerFile).second;
                //cout << mem_add << "VVS" << endl;
                if (mem_add / 1024 != rowbuff.row_no){
                    print_req();
                        if (rowbuff.row_no == -1){
                            //cout << "Hello7"<< endl;
                            rowbuff.UpdateRowBuffer(mem_add / 1024, mem_add %1024, reg, false, -1 );
                            rowbuff.UpdateDelays(row_access_delay, col_access_delay);
                        }
                        else{
                            //cout << "Hello8"<< endl;
                            int curr = rowbuff.row_no;
                            rowbuff.UpdateRowBuffer(mem_add / 1024, mem_add %1024, reg, false, curr );
                            rowbuff.UpdateDelays(2 * row_access_delay, col_access_delay);
                        }
                    }
                    else{
                        //COLUMN
                        print_req();
                        rowbuff.UpdateRowBuffer(rowbuff.row_no, mem_add %1024, "", false, -1);
                        rowbuff.UpdateDelays(0, col_access_delay);
                    }
                memory.setDataAdd(mem_add, registerFile.get_register_data(Rdest));
            }
            programCounter++;
            msg_sw(Rdest, rowbuff, memory);
            }
            else{
                //cout << "Hello9"<< endl;
                rowbuff.UpdateHault(true);
            }
        }
        else if (parametersVec[0] == "addi")
        {
            string Rdest = parametersVec[1], Rsrc = parametersVec[2];
            if (Rdest != rowbuff.reg && Rsrc != rowbuff.reg){
                print_currInstr(currentInstr);
                executionOfInstructionCount[programCounter]++;
                int ans = registerFile.get_register_data(Rsrc) + stoi(parametersVec[3]);
                registerFile.set_register_data(Rdest, ans);
                cout << "Updated value of " << Rdest << " to "<< ans << '.' << endl;
                programCounter++;
            }
            else{
                rowbuff.UpdateHault(true);
            }
        }
        else
        {
            cout << endl;
            cout << "INVALID INSTRUCTION DETECTED!! " << parametersVec[0] << endl;
            throw exception();
        }
        //registerFile.printRegisters();
        currentInstr = memory.getCurrInstr(programCounter);
    }
    cout << "===========================================" << endl;
    cout << "Program execution completed" << endl;
    cout << "Total clock cycles consumed: " << Clock_cycle-1 << endl;
    cout << "===========================================" << endl;
    registerFile.printRegisters();
    cout << "===========================================" << endl;
    memory.printMemDataContent();
    cout << "===========================================" << endl;
    cout << "Count of row buffer updates: "<< endl;
    rowbuff.print_buffers();
    cout << "===========================================" << endl;
    cout << "Number of times each instruction was executed: " << endl;
    int j = 0;
    for (int i = 0; i < instructionVector.size(); i++)
    {
        if (instructionVector[i].find(":") == string::npos && (chk_empty(instructionVector[i])==false) && instructionVector[i]!="EOF")
        {
            cout << instructionVector[i] << endl;
            cout << executionOfInstructionCount[j] << endl;
            j++;
        }
    }
}
int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);                
    cout.tie(NULL);
    // Input file section
    fstream infile;
    fstream outfile;
    outfile.open("../output.txt", ios::out);
    if (argc < 2)
    {
        infile.open("../input.txt", ios::in);
    }
    else
    {
        infile.open(argv[1]);
    }
    vector<string> instructionVector;
    string test2;
    // cout << "XX" << '\t' << "YY" << endl;
    // cout << "XX" << '\n' << "YY" << endl;
    // cout << "XX" << ' ' << "YY" << endl;
    // cout << "XX" << '\r' << "YY" << endl;
    while (getline(infile, test2))
    {
        //cout << test2.length() << endl;
        if (chk_empty(test2) == true){
            continue;
        }
        //cout << "BB" << test2 << "BB" << endl;
        instructionVector.push_back(test2);
    }

    for (int i = 0; i < instructionVector.size(); i++)
    {
        outfile << instructionVector[i] << instructionVector[i][instructionVector[i].length() - 1] << endl;
    }
    // Declarations
    instructionVector.push_back("EOF");
    RegisterFile registerFile;
    MemoryUnit memory;
    RowBuffer rowbuff;
    processInstructions(instructionVector, registerFile, memory, rowbuff);
    return 0;
}