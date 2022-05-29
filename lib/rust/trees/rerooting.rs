/// Rerooting
///
/// # Refs
/// - https://qiita.com/keymoon/items/2a52f1b0fb7ef67fb89e, keymoon, vain0x
#[allow(dead_code)]
fn rerooting<
    T: Clone + PartialEq + std::fmt::Debug + Copy,
    E: IntoIterator<Item = (usize, usize)>,
    F: FnMut(T, T) -> T,
    G: FnMut(T, usize) -> T,
>(
    n: usize,
    edge_paths: E,
    id: T,
    mut merge: F,
    mut op_node: G,
) -> Vec<T> {
    assert_eq!(merge(id, id), id);
    let mut edges = vec![vec![]; n];
    let mut edge_idx = vec![vec![]; n];
    for (u, v) in edge_paths {
        edge_idx[u].push(edges[v].len());
        edge_idx[v].push(edges[u].len());
        edges[u].push(v);
        edges[v].push(u);
    }
    if n == 0 {
        return vec![];
    } else if n == 1 {
        return vec![op_node(id, 0)];
    }
    // init ordered tree
    const NO_PAR: usize = std::usize::MAX;
    let (par, ordered) = {
        let mut par = vec![0; n];
        let mut ordered = vec![0; n];
        let mut idx = 0;
        let mut st = vec![0];
        par[0] = NO_PAR;
        while let Some(u1) = st.pop() {
            ordered[idx] = u1;
            idx += 1;
            for &u2 in edges[u1].iter() {
                if u2 == par[u1] {
                    continue;
                }
                st.push(u2);
                par[u2] = u1;
            }
        }
        (par, ordered)
    };
    // from leaf
    let mut dp = (0..n)
        .map(|i| vec![id; edges[i].len()])
        .collect::<Vec<_>>();
    for i in (1..n).rev() {
        let u = ordered[i];
        let mut acc = id;
        let mut par_idx = NO_PAR;
        for j in 0..edges[u].len() {
            if edges[u][j] == par[u] {
                par_idx = j;
                continue;
            }
            acc = merge(acc, dp[u][j]);
        }
        dp[par[u]][edge_idx[u][par_idx]] = op_node(acc, u);
    }
    // to leaf
    let mut res = vec![id; n];
    let mut rev_acc = vec![];
    for &u in ordered.iter().take(n) {
        let deg = edges[u].len();
        let mut acc = id;
        rev_acc.clear();
        rev_acc.extend(std::iter::repeat(id).take(deg));
        for i in (1..deg).rev() {
            rev_acc[i - 1] = merge(rev_acc[i], dp[u][i]);
        }
        for i in 0..deg {
            dp[edges[u][i]][edge_idx[u][i]] =
                op_node(merge(acc, rev_acc[i]), u);
            acc = merge(acc, dp[u][i]);
        }
        res[u] = op_node(acc, u);
    }
    res
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn merge_max_works() {
        let n = 12;
        let edge_paths = vec![
            (0, 1),
            (0, 4),
            (0, 6),
            (1, 2),
            (1, 3),
            (4, 5),
            (6, 10),
            (6, 11),
            (6, 7),
            (7, 8),
            (7, 9),
        ];
        let merge = std::cmp::max;
        let op_node = |x, _u| x + 1;
        let res = rerooting(n, edge_paths, 0, merge, op_node);
        assert_eq!(res, &[4, 5, 6, 6, 5, 6, 4, 5, 6, 6, 5, 5]);
    }
    #[test]
    fn abc220_f() {
        // https://atcoder.jp/contests/abc220/tasks/abc220_f
        // sample input 3
        let n = 6;
        let edge_paths = vec![
            (0, 1),
            (0, 2),
            (0, 3),
            (0, 4),
            (0, 5),
        ];
        // 処理の意味を分かりやすくするために struct で書きましたが,
        // コンテスト中は tuple で書いた方が楽です.
        #[derive(PartialEq, Debug, Copy, Clone)]
        struct T {
            dist: i64,
            sub: usize,
        }
        impl T {
            fn new(dist: i64, sub: usize) -> Self {
                T { dist, sub }
            }
        }
        let merge = |x: T, y: T| T::new(x.dist + y.dist, x.sub + y.sub);
        let op_node = |x: T, _u| T::new(x.dist + x.sub as i64, x.sub + 1);
        let res = rerooting(n, edge_paths, T::new(0, 0), merge, op_node);
        assert_eq!(res.iter().map(|x| x.dist).collect::<Vec<i64>>(), [5, 9, 9, 9, 9, 9]);
    }
}
