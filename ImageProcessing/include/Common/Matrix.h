#pragma once

#include <cstddef>
#include <vector>

/**
 * @class Matrix.
 * @brief Class implements matrix.
 * @tparam TNumRows Number of rows in matrix.
 * @tparam TNumCols Number of columns in matrix.
 */
template<std::size_t TNumRows, std::size_t TNumCols>
class Matrix final
  {
  static_assert(TNumRows * TNumCols > 0, "Incorrect matrix size");

  public:
    /**
     * @brief Default constructor.
     */
    Matrix();

    /**
     * @brief Gets number of rows in matrix.
     */
    std::size_t NumbefOfRows() const noexcept;

    /**
     * @brief Gets number of columns in matrix.
     */
    std::size_t NumbefOfCols() const noexcept;

    /**
     * @brief Gets element at given position.
     * @param[in] i_row Row number.
     * @param[in] i_row Column number.
     * @return Value at given position.
     */
    double& At(int i_row, int i_col);

    /**
     * @brief Gets element at given position.
     * @param[in] i_row Row number.
     * @param[in] i_row Column number.
     * @return Value at given position.
     */
    double At(int i_row, int i_col) const;

  private:
    std::vector<std::vector<double>> m_data;
  };

///////////////////////////////////////////////////////////////////////////////

template<std::size_t TNumRows, std::size_t TNumCols>
Matrix<TNumRows, TNumCols>::Matrix()
  {
  m_data = std::vector<std::vector<double>>(TNumRows, std::vector<double>(TNumCols, 0.0));
  }

///////////////////////////////////////////////////////////////////////////////

template<std::size_t TNumRows, std::size_t TNumCols>
std::size_t Matrix<TNumRows, TNumCols>::NumbefOfRows() const noexcept
  {
  return m_data.size();
  }

///////////////////////////////////////////////////////////////////////////////

template<std::size_t TNumRows, std::size_t TNumCols>
std::size_t Matrix<TNumRows, TNumCols>::NumbefOfCols() const noexcept
  {
  return m_data[0].size();
  }

///////////////////////////////////////////////////////////////////////////////

template<std::size_t TNumRows, std::size_t TNumCols>
double& Matrix<TNumRows, TNumCols>::At(int i_row, int i_col)
  {
  return m_data[i_row][i_col];
  }

///////////////////////////////////////////////////////////////////////////////

template<std::size_t TNumRows, std::size_t TNumCols>
double Matrix<TNumRows, TNumCols>::At(int i_row, int i_col) const
  {
  return m_data[i_row][i_col];
  }

///////////////////////////////////////////////////////////////////////////////
