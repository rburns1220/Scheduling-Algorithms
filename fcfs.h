#include <stdio.h>
#define size 100
struct process{
int pid;
int waitingtime;
int bursttime;
int arrivaltime;
int turnaroundtime;
int completiontime;
};
int main()
{
struct process p[size];
int n,i,j,temp,temp1,temp2;
int sumwaiting=0;
int sumturnaround=0;

printf("Enter the total no of processes:");
scanf("%d",&n);
printf("Enter the burst time and arrivaltime for each process:\n");
for(i=0;i<n;i++)
{
p[i].pid=i+1;
printf("p[%d] : ",i+1);
scanf("%d",&p[i].bursttime);
scanf("%d",&p[i].arrivaltime);
p[i].waitingtime=0;
p[i].turnaroundtime=0;
p[i].completiontime=0;
}
for(i=0;i<n-1;i++)

{
for(j=0;j<n-1-i;j++)
{
if(p[j].arrivaltime>p[j+1].arrivaltime)
{
temp1=p[j].bursttime;
p[j].bursttime=p[j+1].bursttime;
p[j+1].bursttime=temp1;
temp=p[j].arrivaltime;
p[j].arrivaltime=p[j+1].arrivaltime;
p[j+1].arrivaltime=temp;
temp2=p[j].pid;
p[j].pid=p[j+1].pid;
p[j+1].pid=temp2;

}
}
}
p[0].turnaroundtime=p[0].bursttime;
p[0].completiontime=p[0].bursttime+p[0].arrivaltime;
for(i=1;i<n;i++)
{
if(p[i-1].completiontime<p[i].arrivaltime)
{
p[i-1].completiontime=p[i].arrivaltime;
p[i].completiontime=p[i-1].completiontime+p[i].bursttime;
}
else
{
p[i].completiontime=p[i-1].completiontime+p[i].bursttime;

}
p[i].turnaroundtime = p[i].completiontime - p[i].arrivaltime;
p[i].waitingtime = p[i].turnaroundtime - p[i].bursttime;
}

printf(" \nPROCESS\tB.T\tA.T\tT.T\tW.T\tC.T\n");
for(i=0;i<n;i++)
{
printf("%d\t""%d\t""%d\t""%d\t""%d\t""%d\t",p[i].pid,p[i].bursttime,p[i].arrivaltime,p[i].turnaroundtime,p[i].waitingtime,p[i].completiontime);
printf("\n");
sumwaiting=sumwaiting+p[i].waitingtime;
sumturnaround=sumturnaround+p[i].turnaroundtime;
}

printf("TOTAL WAITING TIME : %d\n",sumwaiting);
printf("AVERAGE WAITING TIME : %d\n",sumwaiting/n);
printf("TOTAL TURNAROUND TIME : %d\n",sumturnaround);
printf("AVERAGE TURNAROUND TIME : %d\n",sumturnaround/n);
puts("");
puts(" GANTT CHART ");
print_gantt_chart(p, n);
return 0;
}

void print_gantt_chart(struct process p[],int n)
{
int i,j;
printf(" ");
for(i=0; i<n; i++) {

for(j=0; j<p[i].bursttime; j++) printf("--");
printf(" ");
}
printf("\n|");
for(i=0; i<n; i++) {
for(j=0; j<p[i].bursttime - 1; j++) printf(" ");
printf("P%d", p[i].pid);
for(j=0; j<p[i].bursttime - 1; j++) printf(" ");
printf("|");
}
printf("\n ");

for(i=0; i<n; i++) {
for(j=0; j<p[i].bursttime; j++) printf("--");
printf(" ");
}
printf("\n");

printf("0");

for(i=0; i<n; i++) {
for(j=0; j<2*p[i].bursttime; j++) printf(" ");
if(p[i].turnaroundtime > 9) printf("\b");
printf("%d",p[i].completiontime);

}
printf("\n");
}
#include <stdio.h>
#define size 100
struct process{
int pid;
int waitingtime;
int bursttime;
int arrivaltime;
int turnaroundtime;
int completiontime;
};
int main()
{
struct process p[size];
int n,i,j,temp,temp1,temp2;
int sumwaiting=0;
int sumturnaround=0;

printf("Enter the total no of processes:");
scanf("%d",&n);
printf("Enter the burst time and arrivaltime for each process:\n");
for(i=0;i<n;i++)
{
p[i].pid=i+1;
printf("p %d : ",i+1);
scanf("%d",&p[i].bursttime);
scanf("%d",&p[i].arrivaltime);
p[i].waitingtime=0;
p[i].turnaroundtime=0;
p[i].completiontime=0;
}
for(i=0;i<n-1;i++)

{
for(j=0;j<n-1-i;j++)
{
if(p[j].arrivaltime>p[j+1].arrivaltime)
{
temp1=p[j].bursttime;
p[j].bursttime=p[j+1].bursttime;
p[j+1].bursttime=temp1;
temp=p[j].arrivaltime;
p[j].arrivaltime=p[j+1].arrivaltime;
p[j+1].arrivaltime=temp;
temp2=p[j].pid;
p[j].pid=p[j+1].pid;
p[j+1].pid=temp2;

}
}
}
p[0].turnaroundtime=p[0].bursttime;
p[0].completiontime=p[0].bursttime+p[0].arrivaltime;
for(i=1;i<n;i++)
{
if(p[i-1].completiontime<p[i].arrivaltime)
{
p[i-1].completiontime=p[i].arrivaltime;
p[i].completiontime=p[i-1].completiontime+p[i].bursttime;
}
else
{
p[i].completiontime=p[i-1].completiontime+p[i].bursttime;

}
p[i].turnaroundtime = p[i].completiontime - p[i].arrivaltime;
p[i].waitingtime = p[i].turnaroundtime - p[i].bursttime;
}

printf(" \nPROC\tB.T\tA.T\tT.T\tW.T\tC.T\n");
for(i=0;i<n;i++)
{
printf("%d\t""%d\t""%d\t""%d\t""%d\t""%d\t",p[i].pid,p[i].bursttime,p[i].arrivaltime,p[i].turnaroundtime,p[i].waitingtime,p[i].completiontime);
printf("\n");
sumwaiting=sumwaiting+p[i].waitingtime;
sumturnaround=sumturnaround+p[i].turnaroundtime;
}

printf("TOTAL WAITING TIME : %d\n",sumwaiting);
printf("AVERAGE WAITING TIME : %d\n",sumwaiting/n);
printf("TOTAL TURNAROUND TIME : %d\n",sumturnaround);
printf("AVERAGE TURNAROUND TIME : %d\n",sumturnaround/n);
puts("");
puts(" GANTT CHART ");
print_gantt_chart(p, n);
return 0;
}

void print_gantt_chart(struct process p[],int n)
{
int i,j;
printf(" ");
for(i=0; i<n; i++) {

for(j=0; j<p[i].bursttime; j++);
printf(" ");
}
printf("\n|");
for(i=0; i<n; i++) {
for(j=0; j<p[i].bursttime - 1; j++) printf(" ");
printf("P%d", p[i].pid);
for(j=0; j<p[i].bursttime - 1; j++) printf(" ");
printf("|");
}
printf("\n ");

for(i=0; i<n; i++) {
for(j=0; j<p[i].bursttime; j++);
printf(" ");
}
printf("\n");

printf("0");

for(i=0; i<n; i++) {
for(j=0; j<2*p[i].bursttime; j++) printf(" ");
if(p[i].turnaroundtime > 9) printf("\b");
printf("%d",p[i].completiontime);

}
printf("\n");
}

