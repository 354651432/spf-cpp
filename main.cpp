#include "graph.hpp"
#include "spf.hpp"

#include <cstdio>
#include <iostream>
#include <string>

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
        // cout << endl;
    }
}

int main(int argc, char const* argv[]) {

    Spf obj;
    initTopology(); // 不补全另一半有些解出不来，因为路径在一定方向上不连接
    obj.G = topology;
    obj.run();

    for (int metric : obj.min) {
        cout << metric << " ";
    }

    cout << endl;

    for (auto pr : obj.reslove) {
        string str('\n', 1024);
        sprintf((char*)str.c_str(), " %d -> %d", pr.first, pr.second);
        cout << str << endl;
    }

    return 0;
}
