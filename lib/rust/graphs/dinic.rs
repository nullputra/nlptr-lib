/// Dinic
///
/// # Refs
/// - https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/maxflow.rs, rust-lang-ja Developers
use std::cmp::min;
use std::collections::VecDeque;
use std::iter;
use std::{
    fmt,
    iter::{Product, Sum},
    ops::{
        Add, AddAssign, BitAnd, BitAndAssign, BitOr, BitOrAssign, BitXor, BitXorAssign, Div,
        DivAssign, Mul, MulAssign, Not, Rem, RemAssign, Shl, ShlAssign, Shr, ShrAssign, Sub,
        SubAssign,
    },
};
pub trait Integral:
    'static
    + Send
    + Sync
    + Copy
    + Ord
    + Not<Output = Self>
    + Add<Output = Self>
    + Sub<Output = Self>
    + Mul<Output = Self>
    + Div<Output = Self>
    + Rem<Output = Self>
    + AddAssign
    + SubAssign
    + MulAssign
    + DivAssign
    + RemAssign
    + Sum
    + Product
    + BitOr<Output = Self>
    + BitAnd<Output = Self>
    + BitXor<Output = Self>
    + BitOrAssign
    + BitAndAssign
    + BitXorAssign
    + Shl<Output = Self>
    + Shr<Output = Self>
    + ShlAssign
    + ShrAssign
    + fmt::Display
    + fmt::Debug
    + fmt::Binary
    + fmt::Octal
    + Zero
    + One
    + BoundedBelow
    + BoundedAbove
{
}
pub trait Zero {
    fn zero() -> Self;
}
pub trait One {
    fn one() -> Self;
}
pub trait BoundedBelow {
    fn min_value() -> Self;
}
pub trait BoundedAbove {
    fn max_value() -> Self;
}
macro_rules! impl_integral {
    ($($ty:ty),*) => {
        $(
            impl Zero for $ty {
                #[inline]
                fn zero() -> Self {
                    0
                }
            }
            impl One for $ty {
                #[inline]
                fn one() -> Self {
                    1
                }
            }
            impl BoundedBelow for $ty {
                #[inline]
                fn min_value() -> Self {
                    Self::min_value()
                }
            }
            impl BoundedAbove for $ty {
                #[inline]
                fn max_value() -> Self {
                    Self::max_value()
                }
            }
            impl Integral for $ty {}
        )*
    };
}
impl_integral!(i8, i16, i32, i64, i128, isize, u8, u16, u32, u64, u128, usize);
impl<Cap> Dinic<Cap>
where
    Cap: Integral,
{
    pub fn new(n: usize) -> Dinic<Cap> {
        Dinic {
            _n: n,
            pos: Vec::new(),
            g: iter::repeat_with(Vec::new).take(n).collect(),
        }
    }
    pub fn add_edge(&mut self, from: usize, to: usize, cap: Cap) -> usize {
        assert!(from < self._n);
        assert!(to < self._n);
        assert!(Cap::zero() <= cap);
        let m = self.pos.len();
        self.pos.push((from, self.g[from].len()));
        let rev = self.g[to].len() + if from == to { 1 } else { 0 };
        self.g[from].push(_Edge { to, rev, cap });
        let rev = self.g[from].len() - 1;
        self.g[to].push(_Edge {
            to: from,
            rev,
            cap: Cap::zero(),
        });
        m
    }
}
#[derive(Debug, PartialEq, Eq)]
pub struct Edge<Cap: Integral> {
    pub from: usize,
    pub to: usize,
    pub cap: Cap,
    pub flow: Cap,
}
impl<Cap> Dinic<Cap>
where
    Cap: Integral,
{
    pub fn get_edge(&self, i: usize) -> Edge<Cap> {
        let m = self.pos.len();
        assert!(i < m);
        let _e = &self.g[self.pos[i].0][self.pos[i].1];
        let _re = &self.g[_e.to][_e.rev];
        Edge {
            from: self.pos[i].0,
            to: _e.to,
            cap: _e.cap + _re.cap,
            flow: _re.cap,
        }
    }
    pub fn edges(&self) -> Vec<Edge<Cap>> {
        let m = self.pos.len();
        (0..m).map(|i| self.get_edge(i)).collect()
    }
    pub fn change_edge(&mut self, i: usize, new_cap: Cap, new_flow: Cap) {
        let m = self.pos.len();
        assert!(i < m);
        assert!(Cap::zero() <= new_flow && new_flow <= new_cap);
        let (to, rev) = {
            let _e = &mut self.g[self.pos[i].0][self.pos[i].1];
            _e.cap = new_cap - new_flow;
            (_e.to, _e.rev)
        };
        let _re = &mut self.g[to][rev];
        _re.cap = new_flow;
    }
    pub fn flow(&mut self, s: usize, t: usize) -> Cap {
        self.flow_with_capacity(s, t, Cap::max_value())
    }
    pub fn flow_with_capacity(&mut self, s: usize, t: usize, flow_limit: Cap) -> Cap {
        let n_ = self._n;
        assert!(s < n_);
        assert!(t < n_);
        assert_ne!(s, t);
        assert!(Cap::zero() <= flow_limit);
        let mut calc = FlowCalculator {
            graph: self,
            s,
            t,
            level: vec![0; n_],
            iter: vec![0; n_],
            que: VecDeque::new(),
        };
        let mut flow = Cap::zero();
        while flow < flow_limit {
            calc.bfs();
            if calc.level[t] == -1 {
                break;
            }
            calc.iter.iter_mut().for_each(|e| *e = 0);
            while flow < flow_limit {
                let f = calc.dfs(t, flow_limit - flow);
                if f == Cap::zero() {
                    break;
                }
                flow += f;
            }
        }
        flow
    }
    pub fn min_cut(&self, s: usize) -> Vec<bool> {
        let mut visited = vec![false; self._n];
        let mut que = VecDeque::new();
        que.push_back(s);
        while let Some(p) = que.pop_back() {
            visited[p] = true;
            for e in &self.g[p] {
                if e.cap != Cap::zero() && !visited[e.to] {
                    visited[e.to] = true;
                    que.push_back(e.to);
                }
            }
        }
        visited
    }
}
struct FlowCalculator<'a, Cap> {
    graph: &'a mut Dinic<Cap>,
    s: usize,
    t: usize,
    level: Vec<i32>,
    iter: Vec<usize>,
    que: VecDeque<usize>,
}
impl<Cap> FlowCalculator<'_, Cap>
where
    Cap: Integral,
{
    fn bfs(&mut self) {
        self.level.iter_mut().for_each(|e| *e = -1);
        self.level[self.s] = 0;
        self.que.clear();
        self.que.push_back(self.s);
        while !self.que.is_empty() {
            let v = *self.que.front().unwrap();
            self.que.pop_back();
            for e in &self.graph.g[v] {
                if e.cap == Cap::zero() || self.level[e.to] >= 0 {
                    continue;
                }
                self.level[e.to] = self.level[v] + 1;
                if e.to == self.t {
                    return;
                }
                self.que.push_back(e.to);
            }
        }
    }
    fn dfs(&mut self, v: usize, up: Cap) -> Cap {
        if v == self.s {
            return up;
        }
        let mut res = Cap::zero();
        let level_v = self.level[v];
        for i in self.iter[v]..self.graph.g[v].len() {
            self.iter[v] = i;
            let &_Edge {
                to: e_to,
                rev: e_rev,
                ..
            } = &self.graph.g[v][i];
            if level_v <= self.level[e_to] || self.graph.g[e_to][e_rev].cap == Cap::zero() {
                continue;
            }
            let d = self.dfs(e_to, min(up - res, self.graph.g[e_to][e_rev].cap));
            if d <= Cap::zero() {
                continue;
            }
            self.graph.g[v][i].cap += d;
            self.graph.g[e_to][e_rev].cap -= d;
            res += d;
            if res == up {
                return res;
            }
        }
        self.iter[v] = self.graph.g[v].len();
        res
    }
}
#[derive(Default)]
pub struct Dinic<Cap> {
    _n: usize,
    pos: Vec<(usize, usize)>,
    g: Vec<Vec<_Edge<Cap>>>,
}
struct _Edge<Cap> {
    to: usize,
    rev: usize,
    cap: Cap,
}
