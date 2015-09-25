
#include <catch.hpp>

#include "../igraphpp/igraph.hpp"

#define N 10

TEST_CASE("Matrix", "[Matrix]") {
  using igraph::Matrix;
  using igraph::Vector;
  using igraph::VectorView;

  Matrix empty;
  CHECK(empty.empty());

  Matrix mat(N, N);
  CHECK_FALSE(mat.empty());
  CHECK(mat.ncol() == N);
  CHECK(mat.nrow() == N);
  CHECK(mat.size() == N * N);
  mat.null();
  CHECK(mat.isnull());
  CHECK_FALSE(mat.contains(1));

  for (long int i = 0; i < N; ++i)
    for (long int j = 0; j < N; ++j)
      mat(i, j) = i + j * N + 1;

  Vector seq(1, N * N);
  double flat[N * N];
  mat.copy_to(flat);

  CHECK(seq == VectorView(flat, N * N));

  CHECK(mat.min() == 1);
  CHECK(mat.max() == N * N);
  long int imin, jmin, imax, jmax;
  mat.which_minmax(&imin, &jmin, &imax, &jmax);
  CHECK(imin == 0);
  CHECK(jmin == 0);
  CHECK(imax == N - 1);
  CHECK(jmax == N - 1);

  Matrix mat2(mat);
  CHECK(mat2.size() == 100);

  Matrix sq(2, 2);
  mat2 = sq;
  CHECK(mat2.size() == 4);
}
