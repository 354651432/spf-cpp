#pragma once
#include "spf.hpp"

template <class T>
class Graph {
    vector<T> V;
    vector<vector<int>> G;

    vector<vector<int>> transform(const vector<vector<int>>& src, vector<int> ids) {
        vector<vector<int>> ret;
        for (int i : ids) {
            vector<int> arr;
            for (int j : ids) {
                arr.push_back(src[i][j]);
            }
            ret.push_back(arr);
        }
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

    int find(vector<int> vec, int p) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == p) {
                return i;
            }
        }

        throw "find err";
    }

public:
    Graph(vector<T> V, vector<vector<int>> G)
        : V(V)
        , G(G) { }

    vector<pair<T, int>> getSortPath(T p1, T p2) {
        vector<int> vids;

        int p1Idx = getIdx(p1);
        int p2Idx = getIdx(p2);

        vids.push_back(p1Idx); // transformedId => sourceId
        for (T v : V) {
            if (v == p1) {
                continue;
            }
            vids.push_back(getIdx(v));
        }

        Spf obj(transform(G, vids));
        obj.run();

        auto paths = obj.getPath(find(vids, p2Idx));

        vector<pair<T, int>> ret;

        int metrix = 0;
        for (auto pr : paths) {
            // int id = find(vids, pr.first);
            ret.push_back({V[vids[pr.first]], metrix});
            metrix += pr.second;
        }

        ret.push_back({p1, metrix}); // 补上终点

        return ret;
    }
};