#include <stdio.h>
#include <stdlib.h>
float d[99999];
float l[99999];
float m[99999];
double f[99999];
float s[99999],mu[99999];
int main()
{
	int n;
	float c, a,b, shag;
	float h;
	
	setbuf(stdout, NULL);
	printf("Vvedite shag h:= ");
	setbuf(stdin, NULL);
	scanf("%f ", &h);
	printf("Vvedite kolichestvo znachenii n:= ");
	scanf("%d ", &n);
	shag=h/2;
	c=h/6;
	a=2*h/3;
	b=h/6;
	printf("c = %f a = %f b = %f", c, a, b);
	int i;
	float x[99999],y[99999];
	for(i=1;i<n+1;i++)
		x[i]=(float)i;
	for(i=1;i<n+1;i++)
	{
		printf("Vvedite Y[%lf]= ", h*i);
		printf("%lf", y[i]);
	}
	mu[0] = m[0] =m[n] = l[0]=0;
	for(i=2;i<n+1;i++)
		d[i]=((y[1+i]-y[i])/h)-(y[i]-y[i-1])/h;
	for(i=1;i<n+1;i++)
	{
		l[i]=-b/(a+c*l[i-1]);
		mu[i]=(d[i]-c*mu[i-1])/(a+c*l[i-1]);
	}
	for(i=n-1;i>1;i--)
		m[i]=l[i]*m[i+1]+mu[i];
	double po;
	for(i=2;i<n;i++)
	{
		f[i]=x[i]-shag;
		s[i]=(((x[i]-f[i])*y[i-1])/h)+(((f[i]-x[i-1])*y[i])/h)+(((x[i]-f[i])*(x[i]-f[i])*(x[i]-f[i]))-((h)*(h)*(x[i]-f[i]))*(m[i-1]))/(6*h)+((((f[i]-x[i-1])*(f[i]-x[i-1])*(f[i]-x[i-1]))-(h)*(h)*(f[i]-x[i-1]))*m[i])/(6*h);
		po=(float)(h*i);
		po=po-shag;
		printf("S[%lf] = \n", s[i]);
		po=(float)(h*i);
		printf("S[%lf] = \n", po);
	}
	
	return 0;
}