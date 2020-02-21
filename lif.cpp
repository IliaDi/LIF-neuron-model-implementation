# include <stdio .h> /* printf , scanf , puts , NULL*/
# include <stdlib .h> /* srand , rand */
# include <iostream >
# include <fstream >
# include <iomanip >
using namespace std;
double myrand ( double fMin , double fMax) //
{
double f = ( double )rand () / RAND_MAX ;
return fMin + f * ( fMax - fMin);
}
int main(int argc , char *argv []) {
double pi =3.14159;
int n =1000;
int r= atoi (argv [1]) ;
double m=atof (argv [2]) ;
double uth= atof( argv [3]);
double couplingStrength = atof( argv [4]);
double u[n], unext [n];
double sum;
double dt =0.001;
double simTime =5000.0;
double time =0.0;
int iterations = (int) ( simTime /dt);
// double refTime; // refIter=refTime/dt
//int refIter =3;
int refractoryPeriod [n];
int minIter =2000;
int cycles [n];
double omega [n];
int it =0;
int i,j,k;
int seed= 436875663;
srand (436875663) ;
ofstream outfile (argv [5]) ;
21
/* initializations */
for(i=0; i<n; i++){
u[i]= myrand (0.0 , uth);
unext [i ]=0.0;
refractoryPeriod [i ]=0;
cycles [i ]=0;
omega [i ]=0.0;
}
for(it =0; it <= iterations ; it ++){
/*for each element */
time += dt;
for(i=0; i<n; i++){
// calculate sum
sum =0.0;
for(j=1; j <=r; j++){
int n1=i-j;
if (n1 <0){n1 +=n;}
int n2=i+j;
if (n2 >=n){n2 -=n;}
sum=sum +(u[n1]-u[i]);
sum=sum +(u[n2]-u[i]);
}
unext [i]=u[i]+ dt *(m-u[i]-( couplingStrength *sum)
/(2*r));
}
/*new initial u*/
for(i=0;i<n;i++ ){
u[i]= unext [i];
/*if threshold is exceeded */
if(u[i]>uth){
u[i ]=0.0;
/*mean phase velocity calculation */
if(it >= minIter ){
cycles [i ]++;
}}
}
//save unext.
//save omega
if(it %1000==0) {
for(i=0;i<n;i++){
22
omega [i ]=2.0* pi* cycles [i]/( time -dt* minIter );
outfile <<fixed << setprecision (5) <<time <<"\t" <<i<<
"\t"<<u[i]<<"\t"<<omega [i]<<"\n";
}
}
}
return 0;
}
