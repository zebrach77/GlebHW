#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

namespace my_std {
	struct _endl {
	};

	struct set_precision {
		set_precision(int x) : x(x) {}
		int x;
	};

	class IFStream {
	public:
		IFStream(FILE* in) : f_(in) {

		}

		friend IFStream& operator >> (IFStream& in, int& x) {
			fscanf(in.f_, "%d", std::addressof(x));
			return in;
		}

		friend IFStream& operator >> (IFStream& in, double & x) {
			fscanf(in.f_, "%lf", std::addressof(x));
			return in;
		}

	private:
		FILE* f_;
	};

	class OFStream {
	public:
		OFStream(FILE* out) : f_(out) {
		}

		friend OFStream& operator << (OFStream& out, const int& x) {
			fprintf(out.f_, "%d", x);
			return out;
		}

		friend OFStream& operator << (OFStream& out, const double & x) {
			if (out.precision != 0) {
				std::string format = "%." + std::to_string(out.precision) + "lf";
				fprintf(out.f_, format.c_str(), x);
				return out;
			}
			fprintf(out.f_, "%lf", x);
			return out;
		}

		friend OFStream& operator << (OFStream& out, const _endl & x) {
			fprintf(out.f_, "%s", "\n");
			return out;
		}

		friend OFStream& operator << (OFStream& out, const set_precision & p) {
			out.precision = p.x;
			return out;
		}

	private:
		FILE* f_;
		int precision{0};
	};

	static IFStream cin(stdin);
	static OFStream cout(stdout);
	static _endl endl;
}

class Complex {
public:
	Complex() : re_(0), im_(0) {}

	Complex& operator=(const Complex& other) = default;
	Complex(const Complex& other)=default;

	Complex(double re, double im) : re_(re), im_(im) {
	}

	Complex operator - () const {
		return {-re_, -im_};
	}

	Complex& operator += (const Complex& other) {
		re_ += other.re_;
		im_ += other.im_;
		return *this;
	}

	Complex& operator -= (const Complex& other) {
		return *this += -other;
	}

	int operator&() const {
		return ((int)re_) & ((int)im_);
	}
/*
    bool operator < (const Complex& other) const {
         if (re_ == other.re_) {
             return im_ < other.im_;
         }
        return re_ < other.re_;
    }

    bool operator > (const Complex& other) const {
        return other < *this;
    }

    bool operator >= (const Complex& other) const {
        return !(*this < other);
    }

    bool operator <= (const Complex& other) const {
        return !(*this > other);
    }

    bool operator == (const Complex& other) const {
        return !(*this > other) && !(*this < other);
    }

    bool operator != (const Complex& other) const {
        return !(*this == other);
    }
    */

	std::strong_ordering operator <=> (const Complex& other) const {
		if (re_ == other.re_) {
			if (im_ < other.im_) {
				return std::strong_ordering::less;
			} else if (im_ == other.im_) {
				return std::strong_ordering::equal;
			} else {
				return std::strong_ordering::greater;
			}
		}
		if (re_ < other.re_) {
			return std::strong_ordering::less;
		} else if (re_ == other.re_) {
			return std::strong_ordering::equal;
		} else {
			return std::strong_ordering::greater;
		}
	}

	friend std::istream& operator >> (std::istream& in, Complex& a);
	friend std::ostream& operator << (std::ostream& out, const Complex& a);

	friend my_std::IFStream& operator >> (my_std::IFStream& in, Complex& a);


private:
	double re_;
	double im_;
};

std::istream& operator >> (std::istream& in, Complex& a) {
	in >> a.re_ >> a.im_;
	return in;
}

my_std::IFStream& operator >> (my_std::IFStream& in, Complex& a) {
	in >> a.re_ >> a.im_;
	return in;
}

Complex operator+(const Complex& a, const Complex& b) {
	Complex c = a;
	c += b;
	return c;
}

Complex operator-(const Complex& a, const Complex& b) {
	Complex c = a;
	c -= b;
	return c;
}

std::ostream& operator << (std::ostream& out, const Complex& a) {
	out << a.re_ <<" " << a.im_;
	return out;
}


template <typename T>
class Wrapper {
public:
	Wrapper(T* x) : x(x) {}
	~Wrapper() {
		std::cout << "Bye" << std::endl;
		delete[] x;
	}
	T* operator -> () {
		return x;
	}

	T& operator [] (int i) {
		return x[i];
	}
private:
	T* x;
};

template <typename T>
void* address_of(T& x) {
	return &reinterpret_cast<int8_t&>(x);
}

// (a+ib) * (c + id) = ac + cbi + adi - bd
int main() {
	int u;
	// my_std::cin >> u;
	//my_std::cout << u;
	my_std::cout << my_std::set_precision(2) << 1.0/3 << my_std::endl;
	Complex x, y;
	std::vector<int> w;
	{
		Wrapper<int> t(new int[10]);
		t[1] = 10;
		std::cout << t[1] << std::endl;
	}

	std::cout << &x << std::endl;
	std::cout << address_of(x) << std::endl;
	my_std::cin >> x >> y;

	if (x >= y) {
		std::cout << "ok" << std::endl;
	}
}