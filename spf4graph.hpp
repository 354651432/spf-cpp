#pragma once
#include "spf.hpp"

template <class T>
class Graph {
    vector<T> V;
    vector<vector<int>> G;

    vector<vector<int>> transform(int p1Idx) {
        auto ret = G;

        swap(ret[0], ret[p1Idx]);

        for (auto& vs : ret) {
            swap(vs[0], vs[p1Idx]);
        }

        return ret;
    }

    vector<T> transformV(int p1Idx) {
        auto ret = V;
        swap(ret[0], ret[p1Idx]);

        return ret;
    }

    int getIdx(T p) {
        for (int i = 0; i < V.size(); i++) {
            if (V[i] == p) {
                return i;
            }
        }
        throw "p is not in V";
    }

public:
    Graph(vector<T> V, vector<vector<int>> G)
        : V(V)
        , G(G) { }

    vector<pair<T, int>> getSortPath(T p1, T p2) {

        int p1Idx = getIdx(p1);
        int p2Idx = getIdx(p2);
        vector<T> vArr1 = transformV(p1Idx);
        Spf obj(transform(p1Idx));
        obj.run();

        auto paths = obj.getPath(getIdx(p2));

        vector<pair<T, int>> ret;

        int metrix = 0;
        for (auto pr : paths) {
            ret.push_back({vArr1[pr.first], metrix});
            metrix += pr.second;
        }

        ret.push_back({p1, metrix}); // 补上终点

        return ret;
    }
};