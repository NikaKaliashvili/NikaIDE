#include "include/nikaide.h"

int main()
{
    // Initialize window
    NikaIDE::InitWindow("NikaIDE v1.0.5",50,50,600,600);
    
    // Handle events
    NikaIDE::PollEvents();

    //LogInfo("This is an info message");
    //LogWarning("This is a warning message");
    //LogError("This is an error message");
}