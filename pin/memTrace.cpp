#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::ofstream;
using std::ios;
using std::string;
using std::endl;

ofstream outFile;

VOID ReadContent(ADDRINT *addr)
{
    ADDRINT value;
    PIN_SafeCopy(&value, addr, sizeof(ADDRINT));
    // Write to a file since cout and cerr maybe closed by the application
    outFile.setf(ios::showbase);
    outFile << "Address 0x" << (unsigned long long)addr << ":\t" << value << endl;
    return;
}

VOID Instruction(INS ins, VOID *v)
{
    if (INS_IsMov(ins) && INS_OperandIsMemory(ins, 1) && INS_MemoryBaseReg(ins) == REG_RIP)
    {
        INS_InsertCall(ins,
                       IPOINT_BEFORE,
                       AFUNPTR(ReadContent),
                       IARG_MEMORYREAD_EA,
                       IARG_END);
    }
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                            "o", "globalTrace.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    outFile.close();
}

INT32 Usage()
{
    cerr << "This tool dump heap memory information (global variable) ..." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

int main(int argc, char *argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    outFile.open(KnobOutputFile.Value().c_str());
    
    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);
    
    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}