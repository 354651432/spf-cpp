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
            }
        }
    }
}

int main(int argc, char const* argv[]) {

    initTopology(); // 不补全另一半有些解出不来，因为路径在一定方向上不连接

    Spf obj(topology);

    auto results = obj.run();

    for (int i = 0; i < results.size(); i++) {
        cout << "v" << i << ":" << results[i] << " ";
    }

    cout << endl;

    auto path = obj.getPath(8); // v1 到v8的距离
    for (auto pr : path) {
        char buf[1024] = {0};
        sprintf(buf, "v%d [%d]->", pr.first, pr.second);
        cout << buf << " ";
    }

    return 0;
}