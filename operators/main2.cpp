#include <iostream>


class Complex {
public:
	Complex() : re_(0), im_(0){}
	Complex(double a, double b) : re_(a) , im_(b){}
	friend std::istream& operator>>(std::istream& in, Complex& c) {
		in >> c.re_ >> c.im_;
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const Complex& c) {
		out<<c.re_<<" "<<c.im_<<"\n";
		return out;
	}

	Complex operator=(const Complex& c) {
		re_ = c.re_;
		im_ = c.im_;
		return *this;
	}
	Complex& operator+=(const Complex& c) {
		re_ += c.re_;
		im_ += c.im_;
		return *this;
	}

	Complex operator+(const Complex& a) const {
		Complex c = a;
		c += *this;
		return c;
	}

	Complex operator-() const {
		return Complex(-re_, -im_);
	}

	Complex& operator-=(const Complex& c) {
		return *this += -c;
	}

	Complex operator-(const Complex& a) const {
		Complex c = *this;
		return c -= a;
	}

	Complex& operator*=(const Complex& c) {
		re_ = re_*c.re_ - im_*c.im_;
		im_ = re_*c.im_ + c.re_*im_;
		return *this;
	}

	Complex operator*(const Complex& a) const {
		Complex c = *this;
		return c *= a;
	}

	Complex operator*() const {
		Complex c = *this;
		c.im_ = -im_;
		return c;
	}

	Complex& operator/=(const Complex& c) {
		Complex abs = c* *c;
		re_ /= abs.re_;
		im_ /= abs.re_;
		return *this;
	}

	Complex operator/(const Complex& a) const {
		Complex c = *this;
		return c /= a;
	}

	Complex& operator^=(int64_t p) {
		if (p == 0) {
			re_ = 1;
			im_ = 0;
			return *this;
		}
		if (p<0) {
			*this ^= -p;
			*this = Complex(1, 0) / *this;
			return *this;
		}
		if (p%2 != 0) {
			Complex q = *this;
			q ^= p-1;
			*this *= q;
			return *this;
		}
		Complex q = *this;
		q ^= p/2;
		*this = q*q;
		return *this;
	}
	

private:
	double im_;
	double re_;
};




int main() {
	Complex complex_num;
	std::cin>>complex_num;
	std::cout<<complex_num;
}