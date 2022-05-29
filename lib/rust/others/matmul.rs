/// Matrix Mul (行列累乗)
///
/// # Refs
/// - http
fn matmul(a: &Vec<Vec<i64>>, b: &Vec<Vec<i64>>) -> Vec<Vec<i64>> {
    let mut res = vec![vec![0; b[0].len()]; a.len()];
    for i in 0..a.len() {
        for k in 0..b.len() {
            for j in 0..b[0].len() {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}
