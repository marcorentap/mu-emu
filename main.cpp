#include "core/vm.cpp"
#include <iostream>

int main() {
    MuVM vm = MuVM(32, 1024 * 1024);
    vm.PrintSomething("something");
    vm.Step();
    vm.Run();

    char thing[4];
    int x = 9;
    vm.MemWrite(0, &x, 4);
    vm.MemRead(thing, 0, 4);
    std::cout << *(int*) thing << std::endl;
}