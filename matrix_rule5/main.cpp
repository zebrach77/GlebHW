#include <iostream>
//n lines, m columns
template <typename T>
class Matrix {
public:
	Matrix(size_t n, size_t m) {
		allocate(n, m);
	}
	Matrix(T value, size_t n, size_t m) {
		allocate(n, m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				matrix_[i][j] = value;
			}
		}
	}

	Matrix(const Matrix& matrix) {
		allocate(matrix.n_, matrix.m_);
		for (size_t i = 0; i < matrix.n_; ++i) {
			for (size_t j = 0; j < matrix.m_; ++j) {
				matrix_[i][j] = matrix.matrix_[i][j];
			}
		}
	}

	Matrix(Matrix&& matrix) {
		matrix_ = matrix.matrix_;
		m_ = matrix.m_;
		n_ = matrix.n_;
		matrix.matrix_ = nullptr;
		matrix.m_ = 0;
		matrix.n_ = 0;
	}



	Matrix& operator=(Matrix&& matrix) {
		if (std::addressof(matrix) == this) {
			return *this;
		}
		clear();
		matrix_ = matrix.matrix_;
		m_ = matrix.m_;
		n_ = matrix.n_;
		matrix.matrix_ = nullptr;
		matrix.m_ = 0;
		matrix.n_ = 0;
		return *this;
	}

	Matrix& operator=(const Matrix& matrix) {
		if (std::addressof(matrix) == this) {
			return *this;
		}
		clear();
		allocate(matrix.n_, matrix.m_);
		for (size_t i = 0; i < matrix.n_; ++i) {
			for (size_t j = 0; j < matrix.m_; ++j) {
				matrix_[i][j] = matrix.matrix_[i][j];
			}
		}
		return *this;
	}

	~Matrix() {
		clear();
	}



	friend std::istream& operator>>(std::istream& in, Matrix& matrix_inp) {
		for (size_t i = 0; i < matrix_inp.n_; ++i) {
			for (size_t j = 0; j < matrix_inp.m_; ++j) {
				in>>matrix_inp.matrix_[i][j];
			}
		}
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix_out) {
		for (size_t i = 0; i < matrix_out.n_; ++i) {
			for (size_t j = 0; j < matrix_out.m_; ++j) {
				out<<matrix_out.matrix_[i][j]<<" ";
			}
			out<<"\n";
		}
		return out;
	}


	Matrix& operator*=(const Matrix& matrix2) {
		if(m_ != matrix2.n_) {
			throw std::runtime_error("Matrices' sizes do not match!");
		}
		Matrix new_matrix(0, n_, matrix2.m_);
		for(size_t i = 0; i < n_; ++i) {
			for (size_t j = 0; j < matrix2.m_; ++j) {
				for(size_t c = 0; c < m_; ++c) {
					new_matrix.matrix_[i][j] += matrix_[i][c] * matrix2.matrix_[c][j];
				}
			}
		}
		*this = std::move(new_matrix);
		return *this;
	}

	Matrix operator*(const Matrix& matrix2) const {
		Matrix temp(*this);
		temp *= matrix2;
		return temp;
	}

	Matrix& operator+=(const Matrix& matrix2) {
		if(m_ != matrix2.m_ || n_ != matrix2.n_) {
			throw std::runtime_error("Matrices' sizes do not match!");
		}
		for (size_t i = 0; i < n_; ++i) {
			for (size_t j = 0; j < m_; ++j) {
				matrix_[i][j] += matrix2.matrix_[i][j];
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& matrix2) const {
		Matrix temp(*this);
		temp += matrix2;
		return temp;
	}

	Matrix& operator-=(const Matrix& matrix2) {
		if(m_ != matrix2.m_ || n_ != matrix2.n_) {
			throw std::runtime_error("Matrices' sizes do not match!");
		}
		for (size_t i = 0; i < n_; ++i) {
			for (size_t j = 0; j < m_; ++j) {
				matrix_[i][j] -= matrix2.matrix_[i][j];
			}
		}
		return *this;
	}

	Matrix operator-(const Matrix& matrix2) const {
		Matrix temp(*this);
		temp -= matrix2;
		return temp;
	}

	Matrix& operator*=(const T value) {
		for (size_t i = 0; i < n_; ++i) {
			for (size_t j = 0; j < m_; ++j) {
				matrix_[i][j] *= value;
			}
		}
		return *this;
	}

	Matrix operator*(const T value) const {
		Matrix temp(*this);
		temp *= value;
		return temp;
	}

	void transpose() {
		T** matrix_new = new int*[m_];
		for (size_t i = 0; i < m_; ++i) {
			matrix_new[i] = new T[n_];
			for(size_t j = 0; j < n_; ++j) {
				matrix_new[i][j] = matrix_[j][i];
			}
		}
		std::swap(n_, m_);
		clear();
		matrix_ = matrix_new;
	}

	T determinant() {
		if (m_ != n_) {
			throw std::runtime_error("Matrix is not square.");
		}

	}



private:
	T** matrix_;
	size_t n_;
	size_t m_;

	void clear() {
		if (matrix_) {
			for(size_t i = 0; i < n_; ++i) {
				delete[] matrix_[i];
			}
			delete[] matrix_;
		}
	}
	void allocate(size_t n, size_t m) {
		n_ = n;
		m_ = m;
		matrix_ = new int*[n];
		for (size_t i = 0; i < n; ++i) {
			matrix_[i] = new T[m];
		}
	}
	T minor(const size_t* arr_i, const size_t* arr_j, size_t length) {
		if (length == 1) {
			return matrix_[arr_i[0]][arr_j[0]];
		}
		if (length == 2) {
			return matrix_[arr_i[0]][arr_j[0]]*matrix_[arr_i[1]][arr_j[1]] - matrix_[arr_i[0]][arr_j[1]]*matrix_[arr_i[1]][arr_j[0]];
		}
		
	}
};


int main() {
	size_t n;
	size_t m;
	std::cin>>n>>m;
	Matrix<int> M1(n, m);
	Matrix<int> M2(m, n);
	std::cin>>M1>>M2;
//	std::cout<<M1*M2<<"\n";
	std::cout<<M2<<"\n";
	M2.transpose();
	std::cout<<M2<<"\n";
	std::cout<<M1 * 5 + M2;
}