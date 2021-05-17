#include <iostream>
#include <Windows.h>
#include "ProcessInfo.h"
#include "ProcessList.h"
#include "Injector.h"

int main()
{
    std::cout << "AstraPfizer1!\n";
    ProcessList* lp = new ProcessList();
    Injector* injector = new Injector();
    lp->refreshProcess();
    lp->printList();
    injector->setDll();
    injector->loadProcess();
    injector->inject();
}