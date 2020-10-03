#include<stdio.h>
main()
{
int n,a[10],b[10],p[10],t[10],c[10],w[10],i,j,temp,temp1,temp2,k;
float atat,awt,sum1=0.0,sum=0.0;
int length = sizeof(a)/sizeof(a[0]);
for(i=0;i<10;i++)
 {
a[i]=0; b[i]=0; p[i]=0; t[i]=0,c[i]=0,w[i]=0;
 }
printf("Enter the number of process=");
scanf("%d",&n);
printf("Enter the process");
for(i=0;i<n;i++)
scanf("%d",&p[i]);
printf("Enter the burst times=");
for(i=0;i<n;i++)
scanf("%d",&b[i]);
printf("\nEnter the arrival times=");
for(i=0;i<n;i++)
scanf("%d",&a[i]);
for (int i = 0; i < n; i++) {
 for (int j = i+1; j < n; j++) {
 if(a[i] > a[j]) {
 temp = a[i];
 a[i] = a[j];
 a[j] = temp;
 temp1=b[i];
 b[i]=b[j];
 b[j]=temp1;
 temp2=p[i];
 p[i]=p[j];
 p[j]=temp2;
 }
 }
 }
 for(i=0;i<10;i++){
 c[i+1]=c[i]+b[i];
 }
 printf("\n");
 printf("\n");
 printf("--------------------------------------------------------------------");
 printf("\n");
 for(i=0;i<n;i++){
 printf("p%d\t|\t",p[i]);
 }
 printf("\n");
 printf("--------------------------------------------------------------------");
 printf("\n");
 for(i=1;i<n+1;i++){
 printf("%d\t|\t",c[i]);
 }
 printf("\n");
 for(i=0;i<10;i++){
 t[i]=c[i+1]-a[i];
 }
 for(i=0;i<10;i++){
 w[i]=t[i]-b[i];
 }
 printf("turn around time\n\n");
 printf("process\t\tTAT\n\n");
 for(i=0;i<n;i++){
 printf("p%d\t\t",p[i]);
 printf("%d\t\t",t[i]);
 printf("\n");
 }
 printf("AVERAGE TURN AROUND TIME\n\n");
 for(i=0;i<n;i++)
 sum=sum+t[i];
 atat=sum/n;
 printf("%.2f\t\n\n",atat);
 printf("waiting time\n\n");
 printf("process\t\tWT\n");
 for(i=0;i<n;i++){
 printf("p%d\t\t",p[i]);
 printf("%d\t\t",w[i]);
 printf("\n");
 }
 printf("AVERAGE WAITING TIME\n\n");
 for(i=0;i<n;i++)
 sum1=sum1+w[i];
 awt=sum1/n;
 printf("%f\n\n",awt);
}
