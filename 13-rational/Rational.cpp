#include "Rational.h"
#include "Integer.h"
namespace cosc326 {

	Rational::Rational() {
            num = Integer();
            denom = Integer();
	}
        Rational::Rational(const std::string& str) {
            /* Three cases :
               a
               a/b
               w.a/b
            */
	}
	Rational::Rational(const Rational& r) {
            num = r.num;
            denom = r.denom;
	}
	Rational::Rational(const Integer& a) {
            num = Integer(a);
            denom = Integer("1");
	}
	Rational::Rational(const Integer& a, const Integer& b) {
            num = Integer(a);
            denom = Integer(b);
	}
    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        num = Integer(a) + Integer(b);
        denom = Integer(c);
    }
    Rational::~Rational() {
        delete num;
        delete denom;
	}
    Rational& Rational::operator=(const Rational& r) {
        num = r.num;
        denom = r.denom;
		return *this;
	}
	Rational Rational::operator-() const {
		return Rational(*this);
	}
	Rational Rational::operator+() const {
		return Rational(*this);
	}
	Rational& Rational::operator+=(const Rational& r) {
		return *this;
	}
	Rational& Rational::operator-=(const Rational& r) {
		return *this;
	}
	Rational& Rational::operator*=(const Rational& r) {
		return *this;
	}
	Rational& Rational::operator/=(const Rational& r) {
		return *this;
	}
	Rational operator+(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}
	Rational operator-(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}
	Rational operator*(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}
	Rational operator/(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}
	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		return os;
	}
	std::istream& operator>>(std::istream& is, Rational& i) {
		return is;
	}
	bool operator<(const Rational& lhs, const Rational& rhs) {
		return true;
	}
	bool operator> (const Rational& lhs, const Rational& rhs) {
		return true;
	}
	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return true;
	}
	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return true;
	}
}
