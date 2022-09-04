#include <iostream>
// m columns, n lines
class Matrix {
public:
	Matrix(size_t m, size_t n, int value) : m_(m), n_(n), mx_(new int*[m]) {
		for (size_t i = 0; i < m; ++i) {
			for (size_t j = 0; j < n; ++j) {
				mx_[i][j] = value;
			}
		}
	}

	Matrix& operator=(Matrix&& new_matr) {
		if(this == std::addressof(new_matr)){
			return *this;
		}
		for (size_t i = 0; i < m_; ++i) {
			delete[] mx_[i];
		}
		delete[] mx_;
		mx_ = new_matr.mx_;
		new_matr.mx_ = nullptr;
		new_matr.n_ = 0;
		new_matr.m_ = 0;
		return *this;
	}

	Matrix& operator=(const Matrix& new_matr) {
		if(this == std::addressof(new_matr)){
			return *this;
		}
		for (size_t i = 0; i < m_; ++i) {
			delete[] mx_[i];
		}
		delete[] mx_;
		mx_ = new int*[new_matr.m_];

		for (size_t i = 0; i < new_matr.m_; ++i) {
			for (size_t j = 0; j < new_matr.n_; ++j) {
				mx_[i][j] = new_matr.mx_[i][j];
			}
		}
	}
	



	~Matrix() {
		for (size_t i = 0; i < m_; ++i) {
			delete[] mx_[i];
		}
		delete[] mx_;
	}
private:
	int** mx_;
	size_t m_;
	size_t n_;
};