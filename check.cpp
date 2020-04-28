#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

ld sec = 0.0;
const int TIME_QUAM = 500;

void cal_sec(char* file) {
    // freopen(file, "r", stdin);
    ifstream my_file;
    my_file.open(file);
    int n = 10;
    for (int i = 0; i < 10; ++i) {
        string s1;
        int x;
        ld d1, d2;
        while (my_file >> s1) {
            if (s1 == "1]") break;
        }
        my_file >> x >> d1 >> d2;
        // cerr << "s1 = " << s1 << " , s2 = " << s2 << " , s3 = " << s3 << " , x = " << x << " , d1 = " << d1 << " , d2 = " << d2 << endl;
        sec += (d2 - d1);
    }
    my_file.close();
    sec /= 10;
    // fclose(stdin);
}

struct INPUT {
    string name;
    int r, e;
    void input(ifstream &ss) {
        ss >> name >> r >> e;
    }
    void output() {
        cerr << "(name, r, e) = (" << name << ", " << r << ", " << e << ")" << endl;
    }
};

string policy;
int n;

vector<INPUT> inputs;

void read_input(char* file) {
    // freopen(file, "r", stdin);
    ifstream my_file;
    my_file.open(file);
    my_file >> policy;
    my_file >> n;
    for (int i = 0; i < n; ++i) {
        INPUT input;
        input.input(my_file);
        inputs.push_back(input);
        // input.output();
    }
    my_file.close();
}

struct OUTPUT {
    string name;
    int pid;
    void input(ifstream &ss) {
        ss >> name >> pid;
    }
    void output() {
        cerr << "(name, pid) = (" << name << ", " << pid << ")" << endl;
    }
};

vector<OUTPUT> outputs;

void read_output(char* file) {
    // cerr << "file = " << file << endl;
    ifstream my_file;
    my_file.open(file);
    for (int i = 0; i < n; ++i) {
        OUTPUT output;
        output.input(my_file);
        outputs.push_back(output);
        // output.output();
    }
    my_file.close();
}

struct DMESG {
    int pid;
    ld st, ed;
    void input(ifstream &ss) {
        string a;
        while (ss >> a) {
            if (a == "1]") break;
        }
        ss >> pid >> st >> ed;
    }
    void output() {
        cerr << fixed << setprecision(9) << "(pid, st, ed) = (" << pid << ", " << st << ", " << ed << ")" << endl;
    }
};

vector<DMESG> dmesgs;

void read_dmesg(char* file) {
    //freopen(file, "r", stdin);
    ifstream my_file;
    my_file.open(file);
    for (int i = 0; i < n; ++i) {
        DMESG dmesg;
        dmesg.input(my_file);
        dmesgs.push_back(dmesg);
        // dmesg.output();
    }
    // fclose(stdin);
    my_file.close();
}

typedef pair<int, int> pii;
#define F first
#define S second
#define MP make_pair

ld cal_optimal() {
    vector<pii> v;
    for (auto i: inputs) {
        v.push_back(MP(i.r, i.e));
    }
    sort(v.begin(), v.end());
    if (policy == "FIFO") {
        int ret = 0;
        int now = 0;
        for (pii p: v) {
            if (p.F >= now) {
                ret += p.S;
                now = p.F + p.S;
            }
            else {
                ret += (now + p.S) - p.F;
                now += p.S;
            }
        }
        return ret * 1.0 / 500 * sec;
    }
    else if (policy == "SJF") {
        set<pii> st;
        int ret = 0;
        int left = 0;
        int now = 0;
        int ptr = 0;
        for (int now_t = 0; ; ++now_t) {
            while (ptr < n && v[ptr].F == now_t) {
                st.insert(make_pair(v[ptr].S, v[ptr].F));
                ++ptr;
            }
            if (left == 0) {
                if (!st.empty()) {
                    pii p = *(st.begin());
                    st.erase(st.begin());
                    ret += (now_t - p.S + p.F);
                    left = p.F;
                }
            }
            if (left != 0) {
                --left;
            }
            if (left == 0 && ptr == n && st.empty()) {
                break;
            }
        }
        return ret * 1.0 / 500 * sec;
    }
    else if (policy == "RR") {
        queue<int> que;
        int left = 0;
        int run_id = -1;
        int ret = 0;
        int ptr = 0;
        for (int now_t = 0; ; ++now_t) {
            while (ptr < n && v[ptr].F == now_t) {
                que.push(ptr);
                ++ptr;
            }
            if (left == 0) {
                if (run_id == -1) {
                    if (que.empty()) continue;
                    int t = que.front(); que.pop();
                    left = min(v[t].S, 500);
                    v[t].S -= left;
                    run_id = t;
                }
                else {
                    if (v[run_id].S > 0) {
                        que.push(run_id);
                    }
                    else {
                        ret += (now_t - v[run_id].F);
                    }
                    if (que.empty()) {
                        if (ptr == n) {
                            break;
                        }
                    }
                    int t = que.front(); que.pop();
                    left = min(v[t].S, 500);
                    v[t].S -= left;
                    run_id = t;
                }
            }
            if (left > 0) {
                --left;
            }
        }
        return ret * 1.0 / 500 * sec;
    }
    else if (policy == "PSJF") {
        set<pii> st;
        int ptr = 0;
        int ret = 0;
        for (int now_t = 0; ; ++now_t) {
            while (ptr < n && v[ptr].F == now_t) {
                st.insert(make_pair(v[ptr].S, ptr));
                ++ptr;
            }
            if (!st.empty()) {
                pii p = *st.begin();
                st.erase(st.begin());
                p.F--;
                if (p.F == 0) {
                    ret += now_t - v[p.S].F + 1;
                }
                else {
                    st.insert(p);
                }
            }
            if (st.empty() && ptr == n) break;
        }
        return ret * 1.0 / 500 * sec;
    }
    else {
        fprintf(stderr, "unknown policy %s\n", policy.c_str());
        assert(0);
    }
}

int base_time;
ld base;

void cal_base() {
    ld mn_dmesg = 1e100;
    int mn_ready = INT_MAX;
    for (auto i: dmesgs) {
        mn_dmesg = min(mn_dmesg, i.st);
    }
    for (auto i: inputs) {
        mn_ready = min(mn_ready, i.r);
    }
    base = mn_dmesg;
    base_time = mn_ready;
}

ld find_ready_time(int pid) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (inputs[i].name == outputs[j].name && outputs[j].pid == pid) {
                return base + (inputs[i].r - base_time) * 1.0 / 500 * sec;
            }
        }
    }
}

ld cal_real() {
    ld ret = 0;
    int j = 0;
    for (auto i: dmesgs) {
        ret += (i.ed - find_ready_time(i.pid));
        cerr << "pid = " << i.pid << " , delta = " << fixed << setprecision(9) << i.ed - find_ready_time(i.pid) << endl;
    }
    return ret;
}

void show(ld optimal, ld real) {
    cout << fixed << setprecision(9) << "optimal is " << optimal << " seconds, real is " << real << " seconds, ratio = " << real / optimal << endl;
}

int main (int argc, char** argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: ./check [TIME_MEASUREMENT_DMESG] [INPUT] [OUTPUT] [DMESG]");
        return 0;
    }
    cerr << argv[1] << ' ' << argv[2] << ' ' << argv[3] << ' ' << argv[4] << endl;
    cal_sec(argv[1]);
    cerr << fixed << setprecision(9) << "seconds = " << sec << endl;
    read_input(argv[2]);
    read_output(argv[3]);
    read_dmesg(argv[4]);
    cal_base();
    cout << "File " << argv[3] << " : ";
    show(cal_optimal(), cal_real());
}

