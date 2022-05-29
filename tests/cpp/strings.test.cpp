#include <bits/stdc++.h>
using namespace std;

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "strings/manacher.hpp"
#include "strings/morris-pratt.hpp"
#include "strings/z-algorithm.hpp"

void morris_pratt_works() {
    string s;
    vector<int> model_ans;

    s = "atcoder";
    model_ans = {-1, 0, 0, 0, 0, 0, 0, 0};
    assert(morris_pratt(s) == model_ans);

    s = "aabaabaaa";
    model_ans = {-1, 0, 1, 0, 1, 2, 3, 4, 5, 2};
    assert(morris_pratt(s) == model_ans);

    s = "aabaabaaa";
    model_ans = {-1, -1, 1, -1, -1, 1, -1, -1, 5, 2};
    assert(morris_pratt(s, true) == model_ans);
}
void manacher_works() {
    string s;
    vector<int> model_ans;

    s = "atcoder";
    model_ans = {1, 1, 1, 1, 1, 1, 1};
    assert(manacher(s) == model_ans);

    s = "abaaababa";
    model_ans = {1, 2, 1, 4, 1, 2, 3, 2, 1};
    assert(manacher(s) == model_ans);
}
void z_algorithm_works() {
    string s, ptn;
    vector<int> model_ans;

    s = "atcoder";
    model_ans = {7, 0, 0, 0, 0, 0, 0};
    assert(z_algorithm(s) == model_ans);

    s = "ababa";
    model_ans = {5, 0, 3, 0, 1};
    assert(z_algorithm(s) == model_ans);

    s = "ababa";
    ptn = "aba";
    model_ans = {0, 2};
    assert(z_search(s, ptn) == model_ans);
}
int main() {
    morris_pratt_works();
    manacher_works();
    z_algorithm_works();
    cout << "Hello World\n";
    return 0;
}
