#include<iostream>
#include<string>
#include<math.h>
#include<stdlib.h>

class Fraction{
    private:
        int numerator; 
        int donominator;
        static int gcd(int a, int b);
    public:
        Fraction();
        Fraction(int nt, int dt);
        Fraction(const Fraction &f);

        int getNumerator();
        void setNumerator(int nt);
        int getDonominator();
        void setDonominator(int dt);
        void reduction();

        double toDouble();
        std::string toString();
        static Fraction decstr2Fraction(std::string str);

        Fraction operator+(const Fraction &target);
        Fraction operator-(const Fraction &target);
        Fraction operator*(const Fraction &target);
        Fraction operator/(const Fraction &target);
        bool operator<(const Fraction &target);
        bool operator<=(const Fraction &target);
        bool operator>(const Fraction &target);
        bool operator>=(const Fraction &target);
        bool operator==(const Fraction &target);
        bool operator!=(const Fraction &target);
        friend std::istream &operator>>(std::istream &is, Fraction &f);
        friend std::ostream &operator<<(std::ostream &os, Fraction &f);
};

//找出最大公约数
int Fraction::gcd(int a, int b)
{
    unsigned int p = abs(a), q = abs(b), r;
    while(q>0){
        r = p % q;
        p = q;
        q = r;
    }
    return p;
}

//分子分母进行约分到最简
void Fraction::reduction()
{
    int r = Fraction::gcd(numerator, donominator);
    if(donominator < 0) r = -r;
    numerator /= r;
    donominator /= r;
}

//初始化分数
Fraction::Fraction()
{
    numerator = 0;
    donominator = 1;
}
Fraction::Fraction(int nt, int dt)
{
    numerator = nt;
    if(dt != 0) {
        donominator = dt;
        reduction();
    } else {
        std::cout << "donominator cannot be 0" << std::endl; //分母不能为0
        system("pause");
        exit(-1);
    }
}
Fraction::Fraction(const Fraction &f)
{
    this->numerator = f.numerator;
    this->donominator = f.donominator;
}

//分子分母分别赋值
int Fraction::getNumerator()
{
    return numerator;
}
void Fraction::setNumerator(int nt)
{
    numerator = nt;
}
int Fraction::getDonominator()
{
    return donominator;
}
void Fraction::setDonominator(int dt)
{
    if(dt > 0) donominator = dt;
}

//转化为double型
double Fraction::toDouble()
{
    return (double)numerator/donominator;
}

//转化为string型
std::string Fraction::toString()
{
    std::string str = std::to_string(numerator);
    str.append("/");
    str.append(std::to_string(donominator));
    return str;
}

//有限十进制字符串转换
Fraction Fraction::decstr2Fraction(const std::string str)
{
    std::size_t pos_digit;
    int n, d = 1;
    for(int i = str.size() - 1; i >= 0; i--){
        if(str[i] == '.') {
            pos_digit = i;
            break;
        }
        d *= 10;
    }
    std::string strnt = str.substr(0, pos_digit);
    if(pos_digit < str.size() - 1) {
        strnt.append(str.substr(pos_digit + 1, str.size() - pos_digit - 1));
    } else {
        d = 1;
    }
    n = atoi(strnt.data());
    return Fraction(n, d);
}

//处理+-*/四种运算情况
Fraction Fraction::operator+(const Fraction &target)
{
    int d = donominator * target.donominator;
    int n = numerator * target.donominator + donominator * target.numerator;
    return Fraction(n, d);
}
Fraction Fraction::operator-(const Fraction &target)
{
    int d = donominator * target.donominator;
    int n = numerator * target.donominator - donominator * target.numerator;
    return Fraction(n, d);
}
Fraction Fraction::operator*(const Fraction &target)
{
    int d = donominator * target.donominator;
    int n = numerator * target.numerator;
    return Fraction(n, d);
}
//在除0时原本对象值不变
Fraction Fraction::operator/(const Fraction &target)
{
    int d = donominator * target.numerator;
    int n = numerator * target.donominator;
    if(n==0){
        std::cout << "division by 0" << std::endl;
        system("pause");
        exit(-1);
    }
    return Fraction(n, d);
}

//判断六种不同符号情况
bool Fraction::operator<(const Fraction &target)
{
    return (numerator * target.donominator - donominator * target.numerator<0);
}
bool Fraction::operator<=(const Fraction &target)
{
    return (numerator * target.donominator - donominator * target.numerator<=0);
}
bool Fraction::operator>(const Fraction &target)
{
    return (numerator * target.donominator - donominator * target.numerator>0);
}
bool Fraction::operator>=(const Fraction &target)
{
    return (numerator * target.donominator - donominator * target.numerator>=0);
}
bool Fraction::operator==(const Fraction &target)
{
    return (numerator * target.donominator - donominator * target.numerator==0);
}
bool Fraction::operator!=(const Fraction &target)
{
    return (numerator * target.donominator - donominator * target.numerator!=0);
}

//输入输出流
std::istream &operator>>(std::istream &is, Fraction &f)
{
    int n, d;
    char ch;
    is >> n ;
    if(n == 0) {
        f.setNumerator(0);
        f.setDonominator(1);
    } else {
        is >> ch;
        if(ch != '/'){
            f.setNumerator(n);
            f.setDonominator(1);
            return is;
        } else{
            is >> d;
            if(d == 0) {
                std::cout << "donominator cannot be 0" << std::endl;
                system("pause");
                exit(-1);
            } else {
                f.setNumerator(n);
                f.setDonominator(d);
                f.reduction();
            }
        }
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, Fraction &f)
{
    if(f.getDonominator() == 1) {
        os << f.getNumerator();
    } else {
        os << f.getNumerator() << "/" << f.getDonominator();
    }
    return os;
}

int main()
{
    Fraction f1, f2, f3, f4, f5;
    f1 = Fraction();
    f2 = Fraction(-12, 30);
    std::cin >> f3;
    f4 = Fraction(f3);
    Fraction res1 = f2 + f4;
    Fraction res2 = f4 - f1;
    Fraction res3 = f2 * f3;
    Fraction res4 = f4 / f3;
    std::cout << "f2 + f4 = " << res1 << std::endl 
            << "f4 - f1 = " << res2 << std::endl 
            << "f2 * f3 = " << res3 << std::endl 
            << "f4 / f3 = " << res4 << std::endl;
    std::string str = f4.toString();
    std::cout << "(double)f2: " << f2.toDouble() << std::endl
            << "(string)f4: " << str << std::endl;
    f5 = Fraction::decstr2Fraction("0.625");
    std::cout << f5 << std::endl;
    std::cout << "f3 < f5: " << (f3 < f5) << std::endl
            << "f4 > f5: " << (f4 > f5) << std::endl
            << "f2 <= f5: " << (f2 <= f5) << std::endl
            << "f4 >= f5: " << (f4 >= f5) << std::endl
            << "f2 == f3: " << (f2 < f3) << std::endl
            << "f4 != f5: " << (f4 < f5) << std::endl;
    return 0;
}