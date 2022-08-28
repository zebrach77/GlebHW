#include <iostream>
#include <string>

class BigNum {
public:
	BigNum(): num_(""){}
	BigNum(std::string s): num_(s) {}
	friend std::istream& operator>>(std::istream& in, BigNum& c){
		in>>c.num_;
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const BigNum& c){
		out<<c.num_;
		return out;
	}
	BigNum& operator+=(const BigNum& c) {
		num_ = ADD(num_, c.num_, 0);
		return *this;
	}

	BigNum operator+(const BigNum& c) const {
		BigNum temp = *this;
		return temp +=c ;
	}
	BigNum& operator-=(const BigNum& c) {
		num_ = SUB(num_, c.num_, 0);
		return *this;
	}

	BigNum operator-(const BigNum& c) const {
		BigNum temp = *this;
		return temp -=c ;
	}
	BigNum& operator*=(const BigNum& c) {
		num_ = MUL(num_, c.num_);
		return *this;
	}

	BigNum operator*(const BigNum& c) const {
		BigNum temp = *this;
		return temp *=c ;
	}


private:
	std::string num_;
	std::string ADD(std::string s1, std::string s2, size_t added_num) {
		if (s1.empty() && s2.empty()) {
			return (added_num)?  std::to_string(added_num) : "";
		}
		if (s1.empty()) {
			size_t b = s2.back() - '0' + added_num;
			size_t a = b / 10;
			b = b % 10;
			s2.pop_back();
			std::string temp = ADD(s1, s2, a);
			return temp + std::to_string(b);
		}
		if (s2.empty()) {
			size_t b = s1.back() - '0' + added_num;
			size_t a = b / 10;
			b = b % 10;
			s1.pop_back();
			std::string temp = ADD(s1, s2, a);
			return temp + std::to_string(b);
		}
		size_t b = s1.back() - '0' + added_num + s2.back() - '0';
		size_t a = b / 10;
		b = b % 10;
		s2.pop_back();
		s1.pop_back();
		std::string temp = ADD(s1, s2, a);
		return temp + std::to_string(b);
	}
	std::string SUB(std::string s1, std::string s2, size_t added_num) {
		if (s1.empty() && s2.empty()) {
			return (added_num)?  "-" : "";
		}
		if (s1.empty()) {
			int b = s2.back() - '0' - added_num;
			size_t a = (b >= 0)? 0 : 1;
			b = (b >= 0)? b : (b+10)/10;
			s2.pop_back();
			std::string temp = SUB(s1, s2, a);
			return (temp == "0")? std::to_string(b): temp + std::to_string(b);
		}
		if (s2.empty()) {
			int b = s1.back() - '0' - added_num;
			size_t a = (b >= 0)? 0 : 1;
			b = (b >= 0)? b : (b+10)/10;
			s1.pop_back();
			std::string temp = SUB(s1, s2, a);
			return (temp == "0")? std::to_string(b): temp + std::to_string(b);
		}
		int b = s1.back() - '0' - added_num - (s2.back() - '0');
		size_t a = (b >= 0)? 0 : 1;
		b = (b>=0)? b : (b+10)/10;
		s2.pop_back();
		s1.pop_back();
		std::string temp = SUB(s1, s2, a);
		return (temp == "0")? std::to_string(b): temp + std::to_string(b);
	}

	std::string MUL(std::string s1, std::string s2) {
		if (s1.length() == 1 && s2.length() == 1) {
			return std::to_string(std::stoi(s1)*std::stoi(s2));
		}
		std::string s1_1;
		std::string s1_2;
		std::string s2_1;
		std::string s2_2;
		std::string t1;
		std::string t2;
		std::string t3;
		std::string t4;
		std::string t5;

		if (s1.length() % 2 == 0) {
			 s1_1 = s1.substr(0, s1.length()/2);
			 s1_2 = s1.substr(s1.length()/2, s1.length()/2);
		}
		else {
			s1_1 = s1.substr(0, s1.length()/2);
			s1_2 = s1.substr(s1.length()/2, s1.length()/2+1);
		}


		if (s2.length() % 2 == 0) {
			s2_1 = s2.substr(0, s2.length()/2);
			s2_2 = s2.substr(s2.length()/2, s2.length());
		}
		else {
			s2_1 = s2.substr(0, s2.length()/2);
			s2_2 = s2.substr(s2.length()/2, s2.length()+1);
		}
		if (s1.length() == 1) {
			t1 = MUL(s1, ADD(s2_1, s2_2, 0));
			t3 = MUL(s1, s2_2);
			t5 = SUB(t1, t3, 0);
			t5 += (t5=="0")? "" : "0";
			return ADD(t3, t5, 0);
		}
		if (s2.length() == 1) {
			t1 = MUL(ADD(s1_1, s1_2, 0), s2);
			t3 = MUL(s1_2, s2);
			t5 = SUB(t1, t3, 0);
			t5 += (t5=="0")? "" : "0";
			return ADD(t3, t5, 0);
		}
		t1 = MUL(ADD(s1_1, s1_2, 0), ADD(s2_1, s2_2, 0));
		t2 = MUL(s1_1, s2_1);
		t3 = MUL(s1_2, s2_2);
		t4 = (t2 == "0")? "0" : t2 + "00";
		t5 = SUB(SUB(t1, t2, 0), t3, 0);
		t5 += (t5=="0")? "" : "0";
		return ADD(ADD(t3, t5, 0), t4, 0);
	}
};

int main () {
	BigNum a;
	BigNum b;
	std::cin>>a>>b;
	std::cout<<a*b;
}