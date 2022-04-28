#include "graph.hpp"
#include "shortPath.hpp"
#include "spf4graph.hpp"

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void initTopology() {
    for (int i = 0; i < topology.size(); i++) {
        for (int j = 0; j < topology[i].size(); j++) {
            topology[j][i] = topology[i][j];
            if (i != j && topology[j][i] == 0) {
            }
        }
    }
}

int main(int argc, char const* argv[]) {

    initTopology(); // 不补全另一半有些解出不来，因为路径在一定方向上不连接

    ShortPath alorObj(topology, 8, 0);
    auto metric = alorObj.getMetric();

    cout << metric << endl;

    for (auto it : alorObj.getPath()) {
        cout << it << " ";
    }

    return 0;
}