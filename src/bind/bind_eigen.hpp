#pragma once

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <Eigen/Dense>
#include <iostream>

namespace {

/** pybind11 向け RowMajor 行列 */
using RMatrixXd =
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

/**
 * @brief 値渡しの例.
 * 値を標準出力.
 * @param m 対象の行列
 */
void print_array(RMatrixXd m) { std::cout << m << std::endl; }

/**
 * @brief 値渡し -> view 戻しの例.
 * 行列のスカラー倍. 戻り値は copy ではない.
 * @param m 対象の行列
 * @param a 対象のスカラー
 * @return RMatrixXd スカラー倍した行列
 */
RMatrixXd modify_array(RMatrixXd m, double a) { return m * a; }

/**
 * @brief 参照渡しで inplace に書き換える例.
 * 行列のスカラー倍. 型・メモリ配置の一致が必要.
 * @param m 対象の行列 (書き換え対象)
 * @param a 対象のスカラー
 */
void modify_array_inplace(Eigen::Ref<RMatrixXd> m, double a) { m = m * a; }

/**
 * @brief 入出力で row-major と col-major を書き換える例.
 * 内容を標準出力. 変換はコピーコンストラクタで可能. 行列のサイズに注意.
 * @param r_mat 対象の row-major 行列
 * @return RMatrixXd col-major -> row-major で元に戻した行列
 */
RMatrixXd print_col_matrix(RMatrixXd r_mat) {
  // row-major と col-major はコピーコンストラクタで変換可能
  Eigen::MatrixXd c_mat = r_mat;
  std::cout << c_mat << std::endl;
  // 出力も戻り値の型を row-major で設定しておけば自動でキャスト
  return c_mat;
}

/**
 * @brief Matrix の stdd::vector を使う例.
 * 行列の冪乗のリストを作成.
 * std::vector には Eigen::aligned_allocator の指定が必要.
 * @param r_matrix 対象の行列
 * @param max_pow ベキの最大値
 * @return std::vector<RMatrixXd, Eigen::aligned_allocator<RMatrixXd>>
 * 行列の冪乗のリスト
 */
std::vector<RMatrixXd, Eigen::aligned_allocator<RMatrixXd>> power_series(
    RMatrixXd r_matrix, int max_pow) {
  Eigen::MatrixXd matrix = r_matrix.transpose();

  std::vector<Eigen::MatrixXd, Eigen::aligned_allocator<Eigen::MatrixXd>>
      result;
  result.emplace_back(matrix);
  for (int idx = 1; idx < max_pow; ++idx) {
    result.emplace_back(result.back() * matrix);
  }

  std::vector<RMatrixXd, Eigen::aligned_allocator<RMatrixXd>> r_result;
  for (int idx = 0; idx < max_pow; ++idx) {
    r_result.emplace_back(result[idx].transpose());
  }
  return r_result;
}

namespace bind_eigen {
void bind_eigen(pybind11::module &m) {
  pybind11::module m_eigen = m.def_submodule("eigen");

  // description が英語だと Windows でビルド不可
  m_eigen.def("print_array", &print_array, "pass by value");
  m_eigen.def("modify_array", &modify_array, "pass by value, return by view");
  m_eigen.def("modify_array_inplace", &modify_array_inplace,
              "pass by reference (inplace)");
  m_eigen.def("print_col_matrix", &print_col_matrix, "row-major and col-major");
  m_eigen.def("power_series", &power_series, "Matrix by std::vector");
}
}  // namespace bind_eigen

}  // namespace