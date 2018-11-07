//操作系统进程调度实验2018.11.4
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define getpch(type) (type *)malloc(sizeof(type))  //用getpch(type)给type类型的变量申请一个空间
struct pcb{                //定义进程模块PCB
    char name[10];          //进程名                                
    char state;             //进程状态
    int super;              //进程优先级
    int ntime;              //进程需要运行的时间
    int rtime;              //进程已经运行的时间
    struct pcb *link;       //定义了一个指向pcb结构类型的指针link作为自己的成员函数

}*ready=NULL,*p;             //定义了两个指向pcb结构类型的指针ready和p,ready的初值为空

typedef struct pcb PCB;
//--------------------------------------------------------------------------------------
void inunization();
void menu();
void youxian();
void sort(); 
void input();
int space();
void destroy();
void check();
void disp(PCB * pr);  
void running();
void FIFO();
void running2();
void sort2();
void input2();
main()
{
    inunization();
    menu();

}
//--------------------------------------------------------------------------------------
void inunization()          //初始化界面函数
{
    printf("\n\n\t\t****************************************\t\t\n");
    printf("\t\t\t\t实验一进程调度\n");
    printf("\t\t******************************************\t\t\n");
    printf("\n\n\n\t\t\t计算机系计算机班\n");
    printf("\t\t\t姓名:司炜辰\n");
    printf("\t\t\t学号:16031029\n");
    printf("\t\t\t完成时间:2018年11月4日\n\n\n\n");
    printf("\t\t\t\t请按任意键进入演示过程\n");
    getchar();
}
//--------------------------------------------------------------------------------------
void menu()     //菜单
{
    int m;
    system("cls");
    printf("\n\n\t\t**************************************\t\t\n");
    printf("\t\t\t\t进程调度演示\n");
    printf("\t\t**************************************\t\t\n");
    printf("\n\n\n\t\t\t1.演示最高优先级优先算法:");
    printf("\n\t\t\t2.演示先来先运行算法:");
    printf("\n\t\t\t0.退出程序.");
    printf("\n\n\t\t\t\t选择进程调度方法:");
    scanf("%d",&m);
    switch(m)
    {
        case 1:
            youxian();   //高优先级优先算法的程序入口
            system("cls");
            menu();
            break;
        case 2:
            FIFO();     //轮转算法演示进程的程序入口
            system("cls");
            menu();
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            menu();

    }
}
//--------------------------------------------------------------------------------------
void FIFO()     //先来先服务算法
{
    int len,h=0;        //len用来存放进程的个数
    char ch;
    system("cls");
    input2();
    len=space();      //进程个数赋给len
     while((len!=0)&&(ready!=NULL))
    {
        ch=getchar();
        h++;            //h用于记录运行的次数
        printf("\n The execute number:%d \n",h);
        p=ready;      //将队首指针赋给p
        ready=p->link;      //ready指向p的下一个进程
        p->link=NULL;       //p的link赋空
        p->state='R';       //将p的状态设置成运行
        check();
        running2();
        printf("\n按任意键继续......");
    }
    printf("\n\n进程已经完成.\n");
    ch=getchar();
}

//--------------------------------------------------------------------------------------
void input2()
{
    int i;
    system("cls");
    printf("\n请输入四个进程信息:\n");

    for(i=0;i<4;i++)
    {
        printf("\n进程号N0.%d:\n",i+1);
        p=getpch(PCB);              //给进程申请一个空间，并用指针p指向这个空间
        printf("\n输入进程名：");
        scanf("%s",p->name);        //输入进程的名字
        printf("\n输入进程优先数:");
        scanf("%d",&p->super);      //输入进程的优先数
        printf("\n输入进程运行的时间:");
        scanf("%d",&p->ntime);      //输入进程运行的时间
        printf("\n");
        p->rtime=0;                 //程序已运行的时间的初值为0
        p->state='w';               //将新建的进程的状态置为“等待”
        p->link=NULL;               //新建进程的指针域为空
        sort2();                     //调用sort函数
    }
}
//--------------------------------------------------------------------------------------
void sort2()

{
    PCB *first,*second;
    if(ready==NULL){
        p->link=ready;      //将新建的进程块指向队首进程,它自己成为队首
        ready=p;            //将ready指向队首的进程
    }
   
    if(ready!=NULL){
        first=ready;        //first指针指向队首进程
        first=p->link;     //second指针指向第二个进程
        second=p;
    }
    else{
        while(second!=NULL)
		{
			first=first->link;
			second=second->link;
            first->link=p;
            p->link=second;
            //             //将新建进程在队列中的前一个进程指向这个新进程
            second=NULL;  
		    }
        } 
    
    
}
//--------------------------------------------------------------------------------------

void youxian()      //高优先级优先算法的程序入口
{
    int len,h=0;        //len用来存放进程的个数
    char ch;
    system("cls");
    input();
    len=space();      //进程个数赋给len
    while((len!=0)&&(ready!=NULL))
    {
        ch=getchar();
        h++;            //h用于记录运行的次数
        printf("\n The execute number:%d \n",h);
        p=ready;      //将队首指针赋给p
        ready=p->link;      //ready指向p的下一个进程
        p->link=NULL;       //p的link赋空
        p->state='R';       //将p的状态设置成运行
        check();
        running();
        printf("\n按任意键继续......");
    }
    printf("\n\n进程已经完成.\n");
    ch=getchar();
}
//--------------------------------------------------------------------------------------

void input()        //建立进程控制块函数
{
    int i;
    system("cls");
    printf("\n请输入四个进程信息:\n");

    for(i=0;i<4;i++)
    {
        printf("\n进程号N0.%d:\n",i+1);
        p=getpch(PCB);              //给进程申请一个空间，并用指针p指向这个空间
        printf("\n输入进程名：");
        scanf("%s",p->name);        //输入进程的名字
        printf("\n输入进程优先数:");
        scanf("%d",&p->super);      //输入进程的优先数
        printf("\n输入进程运行的时间:");
        scanf("%d",&p->ntime);      //输入进程运行的时间
        printf("\n");
        p->rtime=0;                 //程序已运行的时间的初值为0
        p->state='w';               //将新建的进程的状态置为“等待”
        p->link=NULL;               //新建进程的指针域为空
        sort();                     //调用sort函数
    }
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void sort()         //对进程进行优先级排序的函数
{
    PCB *first,*second;
    int insert=0;           //判断是否将新建进程插入在队列中,如果是,则置1
    if(ready==NULL||((p->super)>(ready->super)))  //优先级最大者,插入队首
    {
        p->link=ready;      //将新建的进程块指向队首进程,它自己成为队首
        ready=p;            //将ready指向队首的进程
    }
    else
    {
        first=ready;        //first指针指向队首进程
        second=first->link;     //second指针指向第二个进程
        while(second!=NULL)     //判断是否已到队尾
        {
            if((p->super)>(second->super))    //若插入进程比当前进程优先数大,
            {                                  //插入到当前进程前面
                p->link=second;               //将新建进程的link指针指向它的下一个进程
                first->link=p;              //将新建进程在队列中的前一个进程指向这个新进程
                second=NULL;                //second不指向任何进程
                insert=1;
            }  
            else{               //插入进程的优先数最低,则插入到队尾
                first=first->link;      //新建进程的优先数小于second指向进程的优先级
                second=second->link;   //将first和second下移一个进程
                }
        }   
        if(insert==0)
            first->link=p;          //p指向进程的优先级最小,将p指向的进程插入队尾                                   

    }
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
int space()            //计算进程控制块个数的函数
{
    int l=0;PCB * pr=ready;   //pr指向队首进程
    while(pr!=NULL)            //pr为空,则说明计数完成
    {
        l++;
        pr=pr->link;        //pr向下移一个进程
    }
    return(l);
}
//--------------------------------------------------------------------------------------
void check()        //进程查看函数
{
    PCB *pr;
    printf("\n **** 当前正在运行的进程是: %s",p->name); //显示正在运行进程
    disp(p);
    pr=ready;       //pr指向等待队列的队首进程
    printf("\n **** 当前就绪队列状态为:\n");  //显示就绪队列状态
    while(pr!=NULL)
    {
        disp(pr);
        pr=pr->link;
    }
}
//--------------------------------------------------------------------------------------
void disp(PCB * pr)         //建立进程显示函数，用于显示当前进程
{
    printf("\n qname \t state \t super \t ndtime  runtime \n");
    printf("|%s\t",pr->name);
    printf("|%c\t",pr->state);
    printf("|%d\t",pr->super);
    printf("|%d\t",pr->ntime);
    printf("|%d\t",pr->rtime);
    printf("\n");
}
//--------------------------------------------------------------------------------------
void running()      //建立进程就绪函数（进程运行时间到，置就绪状态）
{
    (p->rtime)++;        //进程的运行时间加1
    if(p->rtime==p->ntime)      //如果已运行时间等于进程运行所需要的时间,则将进程释放
        destroy();
    else{
        (p->super)--;       //将优先级减1
        p->state='w';        //将状态置为"等待
        sort();             //调用sort函数
    }
}
//--------------------------------------------------------------------------------------
void running2()      //建立进程就绪函数（进程运行时间到，置就绪状态）
{
    (p->rtime)++;        //进程的运行时间加1
    if(p->rtime==p->ntime)      //如果已运行时间等于进程运行所需要的时间,则将进程释放
        destroy();
    else{
        p->state='w';        //将状态置为"等待
        sort2();             //调用sort函数
    }
}
//--------------------------------------------------------------------------------------
void destroy()      //建立进程撤销函数（进程运行结束,撤销进程）
{
    printf("\n 进程 [%s]已完成 .\n",p->name);
    free(p);
}
