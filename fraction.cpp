#include <iostream>
#include <math.h>
#define ABS(x) ((x) >= 0) ? (x) : -(x)

class Fraction
{
private:
	long long	WholeNumber;		//   целое число
	long long	numerator;			//   числитель дроби
	long long	denominator;		//   знаменатель дроби

	void		GetMixedView(){
		WholeNumber = numerator / denominator;
		numerator %= denominator;
	}
	int	FindNOD(long long a, long long b) 
	{
		a = ABS(a);
		b = ABS(b);
		while (a && b) {
			if (a > b)
				a = a % b;
			else
				b = b % a;
		}
		return (a + b);
	}
	void		Cancellation(){			//сокращение дроби
		int		nod;

		nod = FindNOD(numerator, denominator);
		numerator /= nod;
		denominator /= nod; 
	}
	void		CheckSign()
	{
		if ((numerator < 0 && denominator < 0) || denominator < 0)
		{
			numerator *= -1;
			denominator *= -1;
		}
	}
public:
	Fraction();
	Fraction(long long num, long long denom);
	Fraction(double numeric);
	operator double(){
		return((double)this->numerator / this->denominator);
	}
	operator int(){
		return(this->numerator / this->denominator);
	}
	// метод сложения двух дробей
	Fraction operator + (Fraction);
	Fraction operator += (Fraction);
	// метод сложения дроби с целым числом
	Fraction operator + (int);
	Fraction operator + (double);
	Fraction operator += (int);
	Fraction operator += (double);
	// метод вычитания двух дробей
	Fraction operator - (Fraction);
	Fraction operator -= (Fraction);
	// метод вычитания из дроби целого числа
	Fraction operator - (int);
	Fraction operator - (double);
	Fraction operator -= (int);
	Fraction operator -= (double);
	// метод умножения двух дробей
	Fraction operator * (Fraction);
	Fraction operator *= (Fraction);
	// метод умножения дроби на целыое число
	Fraction operator * (int);
	Fraction operator * (double);
	Fraction operator *= (int);
	Fraction operator *= (double);
	// метод деления двух дробей
	Fraction operator / (Fraction);
	Fraction operator /= (Fraction);
	// метод деления дроби на целое число
	Fraction operator / (int);
	Fraction operator / (long long);
	Fraction operator / (double);
	Fraction operator /= (int);
	Fraction operator /= (long long);
	Fraction operator /= (double);
	// метод умножения на (-1)
	Fraction operator - ();
	// дружественные функции
	// функция сложения целого числа и дроби
	friend Fraction operator + (int, Fraction);
	friend Fraction operator + (double, Fraction);
	// функция вычитания дроби из целого числа
	friend Fraction operator - (int, Fraction);
	friend double operator - (double, Fraction);
	// функция умножения целого числа и дроби
	friend Fraction operator * (int, Fraction);
	friend Fraction operator * (double, Fraction);
	// функция деления целого числа на дробь
	friend Fraction operator / (int, Fraction);
	friend Fraction operator / (double, Fraction);
	// метод преобразования в тип double
	// методы сравнения двух дробей
	bool operator > (Fraction);
	bool operator < (Fraction);
	bool operator >= (Fraction);
	bool operator <= (Fraction);
	bool operator != (Fraction);
	bool operator == (Fraction);
	bool operator > (int);
	bool operator < (int);
	bool operator >= (int);
	bool operator <= (int);
	bool operator != (int);
	bool operator == (int);
	//дружественные функции сравнения
	friend bool operator > (int, Fraction);
	friend bool operator < (int, Fraction);
	friend bool operator >= (int, Fraction);
	friend bool operator <= (int, Fraction);
	friend bool operator != (int, Fraction);
	friend bool operator == (int, Fraction);
};

Fraction::Fraction()
{
	this->numerator = 0;
	this->denominator = 1;
	this->WholeNumber = 0;
}

Fraction::Fraction(long long num, long long denom)
{
	if (denom == 0)
	{
		this->numerator = 0;
		this->denominator = 1;
	}
	else
	{
		this->numerator = num;
		this->denominator = denom;
	}
	this->WholeNumber = 0;
	this->CheckSign();
	this->Cancellation();
}

Fraction::Fraction(double num)
{
	int a[11] = {0};
	int	p[12] = {0}, q[12] = {0};
	int	i = 0;
	Fraction sub((int)(num * 10000000), 10000000);
	
	for (i = 0; i < 10 && sub.numerator != 0;i++)
	{
		sub.GetMixedView();
		a[i] = sub.WholeNumber;
		sub = 1 / sub;
	}
	p[1] = a[0];
	p[0] = 1;
	q[1] = 1;
	q[0] = 0;
	for (i = 2;i < 10; i++)
	{
		p[i] = a[i - 1] * p[i - 1] + p[i - 2];
		q[i] = a[i - 1] * q[i - 1] + q[i - 2];
		if (a[i + 1] == 0)
			break;
	}
	*this = Fraction(p[i], q[i]);
}

Fraction Fraction::operator+(Fraction p){
	Fraction sub(this->numerator * p.numerator + p.numerator * this->denominator,
													this->numerator * p.denominator);
	return(sub);
}

Fraction Fraction::operator+(int i){
	Fraction sub(this->numerator + i * this->denominator,this->denominator);
	return(sub);
}

Fraction Fraction::operator+(double d){
	Fraction sub(d);
	return(*this + sub);
}

Fraction	operator +(int i, Fraction p)
{
	Fraction sub(p.numerator + i * p.denominator, p.denominator);
	return(sub);
}

Fraction Fraction::operator+=(Fraction p)
{
	Fraction sub(this->numerator * p.denominator + p.numerator * this->denominator,
												this->denominator * p.denominator);
	*this = sub;
	return(*this);
}

Fraction Fraction::operator+=(int i)
{
	Fraction sub(this->numerator + i * this->denominator,this->denominator);
	*this = sub;
	return(*this);
}


Fraction Fraction::operator+=(double d)
{
	Fraction sub(d);
	*this = *this + sub;
	return(*this);
}

Fraction Fraction::operator - (Fraction p)
{
	Fraction sub(this->numerator * p.denominator - p.numerator * this->denominator,
													this->denominator * p.denominator);
	return(sub);
}
Fraction Fraction::operator -= (Fraction p)
{
	Fraction sub(this->numerator * p.denominator - p.numerator * this->denominator,
													this->denominator * p.denominator);
	*this = sub;
	return(*this);
}
	// метод вычитания из дроби целого числа
Fraction Fraction::operator - (int i)
{
	Fraction sub(this->numerator - i * this->denominator, this->denominator);
	return(sub);
}

Fraction Fraction::operator - (double d)
{
	Fraction sub(d);
	return(*this - sub);
}

Fraction Fraction::operator -= (int i)
{
	Fraction sub(this->numerator - i * this->denominator, this->denominator);
	*this = sub;
	return(*this);
}
Fraction Fraction::operator -= (double d)
{
	Fraction sub(d);
	*this = *this - sub;
	return(*this);
}
// метод умножения двух дробей
Fraction Fraction::operator * (Fraction p)
{
	Fraction sub(this->numerator * p.numerator, this->denominator * p.denominator);
	return(sub);
}
Fraction Fraction::operator *= (Fraction p)
{
	Fraction sub(this->numerator * p.numerator, this->denominator * p.denominator);
	*this = sub;
	return(*this);
}
// метод умножения дроби на целыое число
Fraction Fraction::operator * (int  i)
{
	Fraction sub(this->numerator * i, this->denominator);
	return(sub);
}

Fraction Fraction::operator * (double d)
{
	Fraction sub(d);
	return(*this + sub);
}

Fraction Fraction::operator *= (int i)
{
	Fraction sub(this->numerator * i, this->denominator);
	*this = sub;
	return(*this);
}

Fraction Fraction::operator *= (double d)
{
	Fraction sub(d);
	*this = *this * sub;
	return(*this);
}

// метод деления двух дробей
Fraction Fraction::operator / (Fraction p)
{
	if (p.numerator == 0 && p.denominator == 0)
		return(*this);
	else
	{
		Fraction sub(this->numerator * p.denominator, this->denominator * p.numerator);
		return(sub);
	}
}

Fraction Fraction::operator /= (Fraction p)
{
	if (p.numerator != 0)
	{
		Fraction sub(this->numerator * p.denominator, this->denominator * p.numerator);
		*this = sub;
	}
	return(*this);
}

// метод деления дроби на число
Fraction Fraction::operator / (int i)
{
	if (i != 0)
	{
		Fraction sub(this->numerator, this->denominator * i);
		return(sub);
	}
	else
		return(*this);
}

Fraction Fraction::operator / (long long i)
{
	if (i != 0)
	{
		Fraction sub(this->numerator, this->denominator * i);
		return(sub);
	}
	else
		return(*this);
}
Fraction Fraction::operator / (double d)
{
	Fraction sub(d);
	return(*this / sub);
}

Fraction Fraction::operator /= (int i)
{
	if (i != 0)
	{
		Fraction sub(this->numerator, this->denominator * i);
		*this = sub;
		return(*this);
	}
	else
		return(*this);
}

Fraction Fraction::operator /= (long long i)
{
	if (i != 0)
	{
		Fraction sub(this->numerator, this->denominator * i);
		*this = sub;
		return(*this);
	}
	else
		return(*this);
}

Fraction Fraction::operator /= (double d)
{
	Fraction sub(d);
	*this = *this / sub;
	return(*this);
}

// // метод умножения на (-1)
// Fraction operator - ();
// // дружественные функции
// // функция сложения целого числа и дроби

Fraction operator + (double d, Fraction p)
{
	Fraction sub(d);
	return(sub + p);
}

// функция вычитания дроби из целого числа
Fraction operator - (int i, Fraction p)
{
	Fraction sub(i * p.denominator - p.numerator, p.denominator);
	return(sub);
}

// // функция умножения целого числа и дроби
Fraction operator * (int i, Fraction p)
{
	Fraction sub(i * p.numerator, p.denominator);
	return(sub);
}

Fraction operator * (double d, Fraction p)
{
	Fraction sub(d);
	return(sub * p);
}

// // функция деления целого числа на дробь
Fraction operator / (int i, Fraction p)
{
	Fraction sub(i * p.denominator, p.numerator);
	return(sub);
}

Fraction operator / (double d, Fraction p)
{
	Fraction sub(d);
	return(sub / p);
}

// метод преобразования в тип double
// методы сравнения двух дробей
bool Fraction::operator > (Fraction p){
	return (((double)*this > (double)p) ? true : false);
}

bool Fraction::operator >= (Fraction p){
	return (((double)*this >= (double)p) ? true : false);
}
bool Fraction::operator < (Fraction p){
	return (((double)*this < (double)p) ? true : false);
}
bool Fraction::operator <= (Fraction p){
	return (((double)*this < (double)p) ? true : false);
}
bool Fraction::operator != (Fraction p){
	return (((double)*this != (double)p) ? true : false);
}
bool Fraction::operator == (Fraction p){
	return (((double)*this == (double)p) ? true : false);
}

bool Fraction::operator > (int i){
	return (((double)*this > (double)i) ? true : false);
}
bool Fraction::operator < (int i){
	return (((double)*this < (double)i) ? true : false);
}
bool Fraction::operator >= (int i){
	return (((double)*this >= (double)i) ? true : false);
}
bool Fraction::operator <= (int i){
	return (((double)*this <= (double)i) ? true : false);
}
bool Fraction::operator == (int i){
	return (((double)*this == (double)i) ? true : false);
}
bool Fraction::operator != (int i){
	return (((double)*this != (double)i) ? true : false);
}
// //дружественные функции сравнения
bool operator > (int i , Fraction p)
{
	return(((double)i > (double)p) ? true : false);
}
bool operator >= (int i , Fraction p)
{
	return(((double)i >= (double)p) ? true : false);
}
bool operator < (int i , Fraction p)
{
	return(((double)i < (double)p) ? true : false);
}
bool operator <= (int i , Fraction p)
{
	return(((double)i <= (double)p) ? true : false);
}
bool operator == (int i , Fraction p)
{
	return(((double)i == (double)p) ? true : false);
}
bool operator != (int i , Fraction p)
{
	return(((double)i != (double)p) ? true : false);
}

long long	fact(int factorial)
{
	long long	ll = 1;
	for (;factorial;factorial--)
		ll *= factorial;
	return(ll);
}

Fraction pow(Fraction p, int pow)
{
	Fraction sub = p;
	for(; pow - 1; pow--)
		sub *= p;
	return (sub);
}
double	sin(Fraction p)
{
	Fraction sub = p;
	double d = 0;
	for (int i = 1; i < 6;i++)
	{
		long long factor = fact(i * 2 + 1);
		if (factor < 0)
			break;
		if (i % 2 != 0)
			sub -= (pow(p, i * 2 + 1) / factor);
		else
			sub += (pow(p, i * 2 + 1) / factor);
	}	
	return((double)sub);
}

int main(void)
{
	Fraction test1, test2, test3,test4;
	test1 = Fraction(10,-3);
	int i = test1;
	double d = test1;
	test2 = test1 / -23;
	test1 = Fraction(1,-2);
	d = sin(test1);
	test3 = Fraction(-sqrt(2));
	test4 = Fraction(2.0 / 3);
	test4 = pow(test4, 2);
	(void)i;

	return 0;
}
