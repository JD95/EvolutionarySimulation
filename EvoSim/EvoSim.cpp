// EvoSim.cpp : Defines the exported functions for the DLL application.
//

#include "EvoSim.h"

// This is an example of an exported variable
EvoSim_API int nEvoSim=0;

// This is an example of an exported function.
EvoSim_API int fnEvoSim(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see EvoSim.h for the class definition
CEvoSim::CEvoSim()
{
    return;
}
