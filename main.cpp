#include <iostream>
#include <vector>
#include <sstream>
#include "dbmanager/TXTPlaneManager.h"
#include "Invoker.h"
int main() {
    const std::string fileName = "Plane.db.txt";
    TXTPlaneManager planeManager(fileName);
    Invoker h(planeManager);
    h.run();
    return 0;
}