#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const double eps = 0.0001;
const double eps1 = 0.000001;
const int N = 1000;
int iterroot = 0;
int iterintegral = 0;
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double derf1(double x);
extern double derf2(double x);
extern double derf3(double x);

double root(double(*f1)(double), double(*f2)(double), double(*derf1)(double), double(*derf2)(double), double a, double b, double eps)
{
    double m, c1, c2, Fa, Fb;
    while (b - a > eps)
    {
        m = (b + a) / 2.0;
        Fa = f2(a) - f1(a);
        Fb = f2(b) - f1(b);
        c1 = (a * Fb - b* Fa) / (Fb - Fa);
        if (((Fb - Fa)* (((Fb + Fa) / 2) - (f2(m) - f1(m)))) > 0)
        {
            c2 = b - Fb / (derf2(b) - derf1(b));
            b = c2;
            a = c1;
        }
        else
        {
            c2 = a - Fa / (derf2(a) - derf1(a));
            a = c2;
            b = c1;
        }
        ++iterroot;
    }
    return m;
}

double integral(double (*f)(double), double a, double b, double eps)
{
    int n = N;
    double summ0 = 0;
    double delta = (b - a) / n;
    double now = a + delta / 2;
    double summ1 = f(now);
    for (int i = 0; i < n; i++)
    {
        summ1 += f(now += delta);
    }
    while (fabs((summ0 * 2 - summ1)*delta) >= eps)
    {
        summ0 = summ1;
        n *= 2;
        delta /= 2;
        now = a + delta / 2;
        //printf("%.10lf\n", (summ1*delta));
        for (int i = 0; i < n; i++)
        {
            summ1 += f(now += delta);
        }
        iterintegral++;
    }
    return (summ1*delta / 2);
}



double root1(double x)
{
    return (-x*x - x + 6);
}

double root2(double x)
{
    return (x*x - 4);
}

double f0(double x)
{
    return (0.0);
}


double derroot1(double x)
{
    return ((-2) * x - 1);
}

double derroot2(double x)
{
    return (2 * x);
}

double derf0(double x)
{
    return (0.0);
}

void testroot()
{
    int s1, rot;
    printf ("enter number of function:\n");
    printf("1) -x^2 -x +6\n");
    printf("2) x^2 - 4\n");
    scanf("%d", &s1);
    printf("enter number of root:\n");
    scanf("%d", &rot);
    if (s1 == 1 && rot == 1)
    {
        printf("%lf\n", root(root1, f0, derroot1, derf0, -4.0, -1.0, eps1));
    }
    if (s1 == 1 && rot == 2)
    {
        printf("%lf\n", root(root1, f0, derroot1, derf0, 1.0, 3.0, eps1));
    }
    if ((s1 == 2) && (rot == 1))
    {
        printf("%lf\n", root(root2, f0, derroot2, derf0, -4.0, -1.0, eps1));
    }
    if ((s1 == 2) && (rot == 2))
    {
        printf("%lf\n", root(root2, f0, derroot2, derf0, 1.0, 10.0, eps1));
    }
    printf("iteration %d\n", iterroot);
    return;
}

double int1(double x)
{
    return ((-2)*x + 2);
}

double int2(double x)
{
    return (3*(x*x) - 12);
}


void testintegral()
{
    double a = 0, b = 0;

    int s1, s2;
    printf("enter number of function:\n");
    printf("1) -2x + 2\n");
    printf("2) 3x^2 - 12\n");
    scanf("%d", &s1);
    printf("%s", "enter first point: \n");
    scanf("%lf", &a);
    printf("%s", "enter second point: \n");
    scanf("%lf", &b);
    if (s1 == 1)
    {
        printf("%lf\n", integral(int1, a, b, eps));
    }
    if (s1 == 2)
    {
        printf("%lf\n", integral(int2, a, b, eps));
    }
    printf("iteration %d\n", iterintegral);
    return;
}

void help()
{
    printf("%s\n", "-h (help)");
    printf("%s\n", "-tr (test root)");
    printf("%s\n", "-ti (test integral)");
    printf("%s\n", "-r (result)");
}

int main(int argc, char **argv)
{
    if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "-h"))
    {
        help();
    }
    else if (!strcmp(argv[1], "-r"))
    {
        double r12, r23, r31;
        r12 = root(f1, f2, derf1, derf2, 0.0, 5.0, eps1);
	printf("first root %lf\n", r12);
        r23 = root(f2, f3, derf2, derf3, 1.0, 2.0, eps1);
	printf("second root %lf\n", r23);
        r31 = root(f3, f1, derf3, derf1, 0.25, 0.28, eps1);
	printf("third root %lf\n", r31);
        double integ, i1, i2, i3;
        i1 = integral(f1, r31, r12, eps);
        i2 = integral(f2, r23, r12, eps);
        i3 = integral(f3, r31, r23, eps);
        integ = i1 - i2 - i3;
        printf("%lf\n", integ);
	printf("iteration of root %d\n", iterroot);
	printf("iteration of integral %d\n", iterintegral);
    }
    else if (!strcmp(argv[1], "-tr"))
    {
        testroot();
    }
    else if (!strcmp(argv[1], "-ti"))
    {
        testintegral();
    }
    else
    {
        printf("%s\n", "key didn't found");
    }
    return 0;
}
