#include "graph.hpp"
#include "spf.hpp"

#include <iostream>

using namespace std;

void initTopology() {
    for (int i = 0; i < topology.size(); i++) {
        for (int j = 0; j < topology[i].size(); j++) {
            topology[j][i] = topology[i][j];
            if (i != j && topology[j][i] == 0) {
                // topology[j][i] = INT32_MAX;
            }
            // cout << topology[i][j] << "\t";
        }
        cout << endl;
    }
}

int main(int argc, char const* argv[]) {

    Spf obj;
    initTopology();
    obj.G = topology;
    obj.run();

    for (int metric : obj.min) {
        cout << metric << " ";
    }

    return 0;
}
