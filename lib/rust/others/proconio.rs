/// Proconio
///
/// # Refs
/// - https://qiita.com/tanakh/items/0ba42c7ca36cd29d0ac8, tanakh
macro_rules! input {
    ($($r:tt)*) => {
        let stdin = std::io::stdin();
        let mut bytes = std::io::Read::bytes(std::io::BufReader::new(stdin.lock()));
        let mut it = move || -> String {
            bytes.by_ref()
                .map(|r| r.unwrap() as char)
                .skip_while(|c| c.is_whitespace())
                .take_while(|c| !c.is_whitespace())
                .collect()
        };
        inp!{it, $($r)*}
    };
}
macro_rules! inp {
    ($it:expr) => {};
    ($it:expr, ) => {};
    ($it:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = rd!($it, $t);
        inp!{$it $($r)*}
    };
}
macro_rules! rd {
    ($it:expr, ( $($t:tt),* )) => { ( $(rd!($it, $t)),* ) };
    ($it:expr, [ $t:tt ; $len:expr ]) => { (0..$len).map(|_| rd!($it, $t)).collect::<Vec<_>>() };
    ($it:expr, Chars) => { rd!($it, String).chars().collect::<Vec<char>>() };
    ($it:expr, Usize1) => { rd!($it, usize) - 1 };
    ($it:expr, [ $t:tt ]) => {{
        let len = rd!($it, usize);
        (0..len).map(|_| rd!($it, $t)).collect::<Vec<_>>()
    }};
    ($it:expr, $t:ty) => { $it().parse::<$t>().expect("Parse error") };
}
