#include "include/nikaide.h"

int main()
{
    // Initialize window
    NikaIDE::InitWindow("NikaIDE v1.0.0",50,50,600,500);

    // Handle events
    NikaIDE::PollEvents();

    //LogInfo("This is an info message");
    //LogWarning("This is a warning message");
    //LogError("This is an error message");
}