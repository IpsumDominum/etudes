#include "Rational.h"

namespace cosc326 {

	Rational::Rational() {

	}

	Rational::Rational(const std::string& str) {

	}

	Rational::Rational(const Rational& r) {

	}

	Rational::Rational(const Integer& a) {

	}

	Rational::Rational(const Integer& a, const Integer& b) {

	}

	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {

	}

	Rational::~Rational() {

	}

	Rational& Rational::operator=(const Rational& r) {
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
