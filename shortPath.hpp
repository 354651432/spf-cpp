#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class ShortPath {
    vector<vector<int>> G;
    int p1, p2;

    vector<int> path;
    int metric;

    vector<int> getTerminal(const vector<int>& state, int p) {
        vector<int> ret;
        for (int i = 0; i < G.size(); i++) {
            if (find(state.begin(), state.end(), i) != state.end()) {
                continue;
            }

            if (G[p][i] > 0) {
                ret.push_back(i);
            }
        }

        return ret;
    }

    int getMetric(vector<int> state) {
        int sum = 0;
        for (int i = 0; i < state.size() - 1; i++) {
            sum += G[state[i]][state[i + 1]];
        }

        return sum;
    }

    void update(vector<int> state) {
        if (find(state.begin(), state.end(), p2) != state.end()) {
            int sum = getMetric(state);
            if (sum < metric || metric == 0) {
                metric = sum;
                path = state;
            }
            return;
        }

        if (state.size() > 20) {
            throw "call too match times";
        }

        int pt = state.back();

        auto terminal = getTerminal(state, pt);

        for (int it : terminal) {
            vector<int> state1 = state;
            state1.push_back(it);
            update(state1);
        }
    }

public:
    int getMetric() {
        return metric;
    }

    vector<int> getPath() {
        return path;
    }

    ShortPath(vector<vector<int>> G, int p1, int p2)
        : G(G)
        , p1(p1)
        , p2(p2)
        , metric(0) {
        update({p1});
    }
};