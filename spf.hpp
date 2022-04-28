#include <map>
#include <vector>

using namespace std;

class Spf {
    // 邻接矩阵
    vector<vector<int>> G;

    // 点 => 是否为最优解
    map<int, bool> minBoolArr;
    // metric
    vector<int> minArr;

    map<int, int> pathLink; // 目标点 => 一个跳id

    void update() {
        int pt = getSpfPoint(); // 找到每次的起点

        map<int, int> neighbors = getNeighbors(pt); // pointId => metric 不在path里跟minPoint连接的点 : 邻居

        minBoolArr[pt] = true; // 标记为最优解

        for (pair<int, int> pr : neighbors) { //从v1发散到v1所有的邻居并更新min表
            int metric2src = minArr[pt]; // v1到起点的距离
            int metric2v1 = pr.second; // v1到邻居的距离
            int metric = metric2src + metric2v1; //邻居到起点的距离

            if (metric < minArr[pr.first] || minArr[pr.first] == 0) { // 发现更优解 如果需要多个解这里修改成 <=
                minArr[pr.first] = metric;
                pathLink[pr.first] = pt;
            }
        }
    }

    bool complete() {
        for (pair<int, bool> it : minBoolArr) {
            if (!it.second) {
                return false;
            }
        }

        return true;
    }

    int getSpfPoint() {
        // 第一次从起点开始寻找
        if (!minBoolArr[0]) {
            return 0;
        }

        int minPt = 0;
        int minValue = INT32_MAX;

        for (int pt = 0; pt < minArr.size(); pt++) {
            if (minBoolArr[pt]) {
                continue;
            }

            if (minArr[pt] > 0 && minArr[pt] < minValue) {
                minPt = pt;
                minValue = minArr[pt];
            }
        }

        if (minValue == INT32_MAX || minValue == 0) {
            throw "min value is invalid";
        }

        return minPt;
    }

    map<int, int> getNeighbors(int v1) {
        map<int, int> ret;
        for (int pt = 0; pt < minArr.size(); pt++) {
            if (minBoolArr[pt]) {
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

public:
    Spf(vector<vector<int>> G)
        : G(G) { }

    vector<int> run() {
        for (int i = 0; i < G.size(); i++) {
            minBoolArr[i] = false;
            minArr.push_back(0);
        }

        // minArr = G[0];

        do {
            update();
        } while (!complete());

        return minArr;
    }

    vector<pair<int, int>> getPath(int p) {
        if (pathLink.size() <= 0) {
            run();
        }

        vector<pair<int, int>> ret;

        int n = 0;
        int pt = p;
        while (pt > 0) {
            if (++n > 10000) {
                throw "too many result,maybe a loop";
            }

            ret.push_back({pt, G[pt][pathLink[pt]]});
            pt = pathLink[pt];
        }

        return ret;
    }
};