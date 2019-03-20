#include <stdio. h>
#include <windows. h>
#include <iostream. h>
#include <stdlib. h>
float d[99999];
float l[99999];
float m[99999];
double f[99999];
float s[99999],mu[99999];
void main()
{
system("cls");
int n;
float c, a,b, shag;
float h;
printf("Vvedite shag h:= ");
scanf("%f ", &h);
printf("Vvedite kolichestvo znachenii n:=");
scanf("%d ", &h);
shag=h/2;
c=h/6;
a=2*h/3;
b=h/6;
printf("c = %f a = %f b = %f", c, a, b);
int i;
float x[99999],y[99999];
for(i=1;i<n+1;i++)
{
x[i]=(float)i;
}
for(i=1;i<n+1;i++)
{
	printf("");
cout<<"Vvedite Y["<<h*i<<"]:=";
cin>>y[i];
}
mu[0]=m[0]=m[n]=l[0]=0;
for(i=2;i<n+1;i++)
{ 
d[i]=((y[1+i]-y[i])/h)-(y[i]-y[i-1])/h;
}
for(i=1;i<n+1;i++)
{
l[i]=-b/(a+c*l[i-1]);
mu[i]=(d[i]-c*mu[i-1])/(a+c*l[i-1]);
}
for(i=n-1;i>1;i--)
{
m[i]=l[i]*m[i+1]+mu[i];
}
double po;
for(i=2;i<n;i++)
{
f[i]=x[i]-shag;
s[i]=(((x[i]-f[i])*y[i-1])/h)+(((f[i]-x[i-1])*y[i])/h)+(((x[i]-f[i])*(x[i]-f[i])*(x[i]-f[i]))-((h)*(h)*(x[i]-f[i]))*(m[i-1]))/(6*h)+((((f[i]-x[i-1])*(f[i]-x[i-1])*(f[i]-x[i-1]))-(h)*(h)*(f[i]-x[i-1]))*m[i])/(6*h);
po=(float)(h*i);
po=po-shag;
cout<<"S["<<po<<"]="<<s[i]<<endl;
po=(float)(h*i); 
cout<<"S["<<po<<"]= "<<y[i]<<endl;
} 
system("PAUSE");
}