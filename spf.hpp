#include <map>
#include <vector>

using namespace std;

class Spf {
public:
    // 邻接矩阵
    vector<vector<int>> G;

    // 点 => 是否为最优解
    map<int, bool> path;
    // metric
    vector<int> min;

    void run() {
        min = G[0];

        for (int i = 0; i < min.size(); i++) {
            path[i] = false;
        }
        path[0] = true; // 起点不需要寻找

        while (!complete()) {
            update();
        }
    }

    void update() {
        int v1 = getMinPoint(); // 找到每次的起点
        map<int, int> lbs = getLabers(v1); // pointId => metric 不在path里跟minPoint连接的点 : 邻居

        path[v1] = true; // 标记为最优解

        for (pair<int, int> pr : lbs) { //从v1发散到v1所有的邻居并更新min表
            int metric2src = min[v1]; // v1到起点的距离
            int metric2v1 = pr.second; // v1到邻居的距离
            int metric = metric2src + metric2v1; //邻居到起点的距离

            if (metric < min[pr.first] || min[pr.first] == 0) { // 发现更优解
                min[pr.first] = metric;
            }
        }
    }

    bool complete() {
        for (pair<int, bool> it : path) {
            if (!it.second) {
                return false;
            }
        }

        return true;
    }

    int getMinPoint() {
        int minPt = 0;
        int minValue = INT32_MAX;

        for (int pt = 0; pt < min.size(); pt++) {
            if (path[pt]) {
                continue;
            }

            if (min[pt] > 0 && min[pt] < minValue) {
                minPt = pt;
                minValue = min[pt];
            }
        }

        if (minValue == INT32_MAX || minValue == 0) {
            throw "min value is invalid";
        }

        return minPt;
    }

    map<int, int> getLabers(int v1) {
        map<int, int> ret;
        for (int pt = 0; pt < min.size(); pt++) {
            if (path[pt]) {
                continue;
            }

            if (pt == v1) {
                continue;
            }

            if (G[pt][v1] > 0) { // 与v1连接的pt点
                ret[pt] = G[pt][v1];
            }
        }

        return ret;
    }
};