// Union Find
//
// # Refs
// - https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/dsu.rs, rust-lang-ja Developers
struct UnionFind {
    n: usize,
    par: Vec<i32>,
}
#[allow(dead_code)]
impl UnionFind {
    fn new(n: usize) -> Self {
        UnionFind {
            n,
            par: vec![-1; n],
        }
    }
    fn unite(&mut self, mut x: usize, mut y: usize) -> bool {
        assert!(x < self.n && y < self.n);
        x = self.find(x);
        y = self.find(y);
        if x == y {
            return false;
        }
        if self.par[x] > self.par[y] {
            std::mem::swap(&mut x, &mut y);
        }
        self.par[x] += self.par[y];
        self.par[y] = x as i32;
        true
    }
    fn find(&mut self, x: usize) -> usize {
        assert!(x < self.n);
        if self.par[x] < 0 {
            x
        } else {
            self.par[x] = self.find(self.par[x] as usize) as i32;
            self.par[x] as usize
        }
    }
    fn same(&mut self, x: usize, y: usize) -> bool {
        assert!(x < self.n && y < self.n);
        self.find(x) == self.find(y)
    }
    fn groups(&mut self) -> Vec<Vec<usize>> {
        let mut _find = vec![0; self.n];
        let mut _size = vec![0; self.n];
        for i in 0..self.n {
            _find[i] = self.find(i);
            _size[_find[i]] += 1;
        }
        let mut res = vec![vec![]; self.n];
        for i in 0..self.n {
            res[i].reserve(_size[i]);
        }
        for i in 0..self.n {
            res[_find[i]].push(i);
        }
        res.into_iter()
            .filter(|v| !v.is_empty())
            .collect::<Vec<Vec<usize>>>()
    }
    fn size(&mut self, x: usize) -> usize {
        assert!(x < self.n);
        let x = self.find(x);
        -self.par[x] as usize
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn uf_works() {
        let mut uf = UnionFind::new(4);
        uf.unite(0, 1);
        assert!(uf.same(0, 1));
        uf.unite(1, 2);
        assert!(uf.same(0, 2));
        assert_eq!(uf.size(0), 3);
        assert!(!uf.same(0, 3));
        assert_eq!(uf.groups(), vec![vec![0, 1, 2], vec![3]]);
    }
}
