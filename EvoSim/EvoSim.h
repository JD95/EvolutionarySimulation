#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the EvoSim_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// EvoSim_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef EvoSim_EXPORTS
#define EvoSim_API __declspec(dllexport)
#else
#define EvoSim_API __declspec(dllimport)
#endif

// This is an example of a class exported from the EvoSim.dll
class EvoSim_API CEvoSim
{
public:
    CEvoSim();
    // TODO: add your methods here.
};

// This is an example of an exported variable
extern EvoSim_API int nEvoSim;

// This is an example of an exported function.
EvoSim_API int fnEvoSim(void);
