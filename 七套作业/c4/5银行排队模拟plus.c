/*银行排队模拟plus
关键是每个人有不同的服务时间，使得这题要增加一个模拟窗口的数组
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define MIN 3 // 最大和最小窗口数

struct CUS
{
    int no;
    int wait_time; // 等待时间
    int cost_time;
} customer[100];
struct CUSWIN
{
    int no;
    int cost_time; // 花费时间
    int wait_time;
    int flag;
} cuswin[100];
struct ANS
{
    int no;

    int wait_time;

} ans[100];
int front = 100; // 方便构造循环队列, 同时处理开始和循环
int rear = 100;
int q = 0;
void Push(struct CUS);
struct CUS Pop();
struct CUSWIN Pop1();
int cus_num = 0, id = 0, number = 0; // 排队客人数  序号  总人数
int now_time, total_time;
int win_num = MIN; // 窗口数
int num[100];
void WinAdd();
void WinSub();
void Service();
void CusIn(int new);//进入排队队列
void update();//更新等待时间 以及服务时间
void WinCusIn();//进入窗口
void sort();//整理窗口客户  若服务结束 将其pop出去
int cmp1(const void *p1, const void *p2)
{
    if (((struct ANS *)p1)->no == ((struct ANS *)p2)->no)
        return 0;
    else if (((struct ANS *)p1)->no > ((struct ANS *)p2)->no)
        return 1;
    else
        return -1;
}
int main()
{
    for (int i = 0; i < 100; i++)
    {
        cuswin[i].flag = 0;
    }
    int new_cus;
    scanf("%d", &total_time);
    for (int i = 0; i < total_time; i++)
    {
        scanf("%d", &num[i]);
        number += num[i];
    }
    int k = 0;
    for (now_time = 1; now_time <= total_time || cus_num != 0||q<number; now_time++)
    {

        if (now_time > total_time)
            new_cus = 0;
        else
            new_cus = num[k++];

        CusIn(new_cus); // in queue
        if (new_cus > 0)
            WinAdd();
        
        Service();
        if(cuswin[win_num-1].flag==0)//只有当有空闲的时候才能减少！！！
        WinSub();
    }
    qsort(ans, number, sizeof(struct ANS), cmp1);
    for (int i = 0; i < number; i++)
    {
        printf("%d : %d\n", ans[i].no, ans[i].wait_time);
    }
    return 0;
}

void WinAdd()
{
    int ave;
    ave = cus_num / win_num;
    while (ave >= 7)
    {
        if (win_num == MAX)
            break;
        win_num++;
        ave = cus_num / win_num;
    }
}

void CusIn(int new)
{
    struct CUS person;
    cus_num += new;
    while (new --)
    {
        id++;
        person.wait_time = 0;
        person.no = id;
        int cost;
        scanf("%d", &cost);
        person.cost_time = cost;
        Push(person);
    }
}
void WinCusIn()
{
    struct CUS person;
    for (int i = 0; i < win_num && cus_num > 0; i++)
    {
        if (cuswin[i].flag == 0)
        {
            person = Pop();
            cuswin[i].no = person.no;
            cuswin[i].wait_time = person.wait_time;
            cuswin[i].cost_time = person.cost_time;
            cuswin[i].flag = 1;
            
        }
    }
}
void WinSub()
{
    int ave;
    ave = cus_num / win_num;
    while (ave < 7)
    {
        if (win_num == MIN)
            break;
        win_num--;
        ave = cus_num / win_num;
    }
}

void Service()
{
    WinCusIn();
    sort();//如果此时已经有人结束了，就要再判断是否能wincusin
    WinCusIn();
    update();
    sort();
    /*此时不能再判断能不能wincusin了，如果这时候再进入窗口一个，
    但是后面排队人数减少导致窗口关闭将发生重大错误
    也就是我还在接受服务呢你就把我强制驱离了
    */
}

void Push(struct CUS person)
{
    
    if (rear == 100)
    {
        rear = 0; // 回到开头
        // 注意同时处理了起始的情况
    }
    else
        rear++;
    customer[rear].wait_time = person.wait_time;
    customer[rear].no = person.no;
    customer[rear].cost_time = person.cost_time;
}

struct CUS Pop()
{
    if (front == 100)
        front = 0; // 这是处理上次的旧账,这次就应该在0
    cus_num--;
    return customer[front++];

}
void update()
{
    for (int i = 0; i < win_num; i++)//是否可以定义一个窗口处客户数量？
    {
        cuswin[i].cost_time--;
    }

    for (int i = front; i < cus_num+front; i++)
    {

        customer[i % 100].wait_time++;
    }
}
struct CUSWIN Pop1(int no)
{

    return cuswin[no];
}
void sort()
{
    int flag1;
    struct CUSWIN person;
    for (int j = 0; j < win_num; j++)
    {
        if (cuswin[j].cost_time == 0&&cuswin[j].no!=0&&cuswin[j].flag==1)
        {
            person = Pop1(j);
            for(int i=win_num-1;i>j;i--)
            {
                if(cuswin[i].flag==1)
                {
                    flag1=i;
                    break;
                }
            }
            cuswin[j] = cuswin[flag1];//应该等于最后一个flag为1的
            cuswin[flag1].flag = 0;
            
            ans[q].no = person.no;
            ans[q++].wait_time = person.wait_time;
        }
    }
}
