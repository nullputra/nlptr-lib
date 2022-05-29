/// Dijkstra
///
/// 単一始点最短経路問題を解く.
/// 始点 s と辺に非負の重みの付いた有向グラフを受け取り, 各 t に対する s-t 最短路長を返す.
#[allow(dead_code)]
fn dijkstra(s: usize, edges: &[Vec<(usize, i64)>]) -> Vec<i64> {
    const INF: i64 = std::i64::MAX;
    let mut dists = vec![INF; edges.len()];
    dists[s] = 0;
    use std::collections::BinaryHeap;
    let mut hp = BinaryHeap::new();
    hp.push((0, s));
    while let Some((d1, v1)) = hp.pop() {
        let d1 = -d1;
        if dists[v1] < d1 {
            continue;
        }
        for &(v2, d2) in edges[v1].iter() {
            if dists[v2] > d1 + d2 {
                dists[v2] = d1 + d2;
                hp.push((-dists[v2], v2));
            }
        }
    }
    dists
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn dijkstra_works() {
        // 重み付き有向辺
        let uvc = vec![(1, 2, 1), (1, 4, 2), (2, 3, 1), (3, 4, 1), (4, 5, 1)];

        let n = 5;
        let mut edges = vec![vec![]; n];
        for &(u, v, c) in uvc.iter() {
            edges[u - 1].push((v - 1, c));
        }
        // 始点 s = 0 で dijkstra
        let dists = dijkstra(0, &edges);
        assert_eq!(dists, vec![0, 1, 2, 2, 3]);
    }
}
