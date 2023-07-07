#define _CRT_SECURE_NO_WARNINGS
// Exp1-1_LinkedList_WithHead
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STU_ID_MAXLEN 16
#define STU_NAME_MAXLEN 20

// 学生结构体
typedef struct
{
    char stuId[STU_ID_MAXLEN];
    char name[STU_NAME_MAXLEN];
    char gender;
    float score;
} Stu;

// 单链表结点的结构体
typedef struct LNode
{
    Stu data;    
    struct LNode *next;    
} LinkedNode;

Stu *ps;    // 指向备用同学数组
int stuNum;    // 备用同学的数量

// 获得备用同学的数据
void loadAllStudent()
{
    FILE *fp;
    int i = 0;

    if ((fp = fopen("allStu.dat", "rb")) == NULL)
    {
        printf("Cannot open the data file, failed to save the student information!");
        return;
    }

    // 开始读文件，先读人数，根据人数开辟空间的大小 
    fread(&stuNum, sizeof(int), 1, fp);
    ps = (Stu *)malloc(sizeof(Stu)*stuNum);

    while (i < stuNum)
    {
        fread(&(ps[i]), sizeof(Stu), 1, fp);
        i++;
    }
    // fread(ps, sizeof(Stu), stuNum, fp);

    fclose(fp);
}

void menu()                               
{
    printf("\n\t***The one-way linked list with head***\n");
    printf("\t*     1 Choose a student & insert     *\n");    
    printf("\t*     2 Delete a student              *\n");
    printf("\t*     3 Modify a student              *\n");
    printf("\t*     4 Show all the students         *\n");
    printf("\t*     0 Save & Exit                   *\n");
    printf("\t***************************************\n");
    printf("\tPlease select a menu item:\n");
}

/*    检测当前目录下是否存在文件stu1-1.dat，
    如果存在，则从其中读取数据构造线性表。  */
LinkedNode *init()
{
    FILE *fp;
    Stu stmp;
    LinkedNode *head=NULL, *p, *rear=NULL;

    // 给头结点开辟空间，并初始化为空表 
    head = (LinkedNode *)malloc(sizeof(LinkedNode));
    head->next = NULL;
    
    if((fp=fopen("stu1-1.dat","rb"))==NULL)
        return head; 
    
    // 打开成功，则开始读文件
     fread(&stmp, sizeof(Stu), 1, fp);
     
     while(!feof(fp))
     {
        // 开辟一个结点空间
        p = (LinkedNode *)malloc(sizeof(LinkedNode));

        // 构造结点
        p->data = stmp;
        p->next=NULL;

        // 将构造好的结点从尾部插入单向链表
        if(NULL == head->next)    // 如果插入的是第一个结点
        {
            rear = p;
            head->next = p;
        }
        else                    // 如果插入的不是第一个结点
        {
            rear->next = p;
            rear = p;
        }

        // 再读一个学生的数据
        fread(&stmp, sizeof(Stu), 1, fp);
     }
         
    fclose(fp);

    return head;
}

/* 获取一个学生的信息 */
Stu getAStudent()
{
    // 生成一个[0, stuNum-1]的随机数
    int r = rand() % stuNum;
    return ps[r];
}

/* 插入一个随机选中的学生，到带头结点的单链表中 */
void insert(LinkedNode *head)
{
    int poi, count = 0;
    LinkedNode *pre, *pNew;    // pre指向插入位置的直接前驱结点，pNew用于开辟新结点空间
    pre = head;

    printf("Please enter the location of the student to be inserted:\n");
    scanf("%d", &poi);

    // 当未到链表尾部，并且未到第poi-1个学生结点（即插入点的直接前驱）时
     

    // 如果找到了正确的插入位置
    if (count == poi - 1 && pre != NULL)
    {
        // 开辟空间
        // 构造结点（随机选中一个结点存入刚开辟的新结点空间） 
        // 插入新结点到单向链表中pre所指结点之后
         
        printf("%s has been inserted successfully!\n", pNew->data.name);
    }
    else     // 如果插入位置不合法
        printf("The inserted position is invalid!\n");
}

/* 从带头结点的单链表中删除一个指定学生 */
void del(LinkedNode *head)
{
    char c;

    if(NULL!=head && NULL!=head->next)
    {
        char stuId[STU_ID_MAXLEN];
        int flag=0;
        LinkedNode *pre, *q;

        // pre始终要指向待删除结点的直接前驱，因为有可能删除第一个数据结点，
        // 所以先让其指向整个链表的头结点
        pre = head;
        
        // fflush(stdin);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Please enter the id of the student to be deleted:\n");
        scanf("%s", stuId);
        
        while(NULL != pre->next)
        {
            // 如果找到了待删除结点的直接前驱    
            // q指向待删除结点
            // 先让q所指结点从链表中断开
            // 先提示，后释放q所指结点
             
        }

        if(0 == flag)
            printf("The student you want to delete was not found!\n");
    }
    else
        printf("The one-way linked list does not exist or is empty, no student data to delete!\n");
}

/* 查找指定学生，并修改其信息（修改后的姓名字符串中，不能含有中文字符） */
void modify(LinkedNode *head)
{
    char c;

    if(NULL!=head && NULL!=head->next)
    {
        char stuId[STU_ID_MAXLEN];
        int choice, flag=0;
        LinkedNode *p;

        // p最终要指向待修改的学生结点，所以先让其指向第一个学生结点
        p = head->next;
        
        printf("Please enter the student ID of the student to be modified:\n");
        scanf("%s", stuId);

        while(p!=NULL)
        {
            if(!strcmp(p->data.stuId, stuId))    // 如果找到待修改的学生
            {
                while(1)
                {
                    printf("Current student information is as follows:\n");
                    printf("1--StuID:%s\n", p->data.stuId);
                    printf("2--Name:%s\n", p->data.name);
                    printf("3--Gender:%c\n", p->data.gender);
                    printf("4--Score:%.1f\n", p->data.score);
                    printf("Please select a menu item to be modified (enter 0 to complete the modification):\n");
                    scanf("%d", &choice);

                    switch(choice)
                    {
                    case 1:
                        // fflush(stdin);
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("Please enter the revised student ID:");
                        scanf("%s", p->data.stuId); 
                        break;
                    case 2:
                        // fflush(stdin);
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("Please enter the revised student name:");
                        // scanf("%s", p->data.name); 
                        fgets(p->data.name, STU_NAME_MAXLEN, stdin);
                        if ('\n' == p->data.name[strlen(p->data.name)-1])
                        {
                            p->data.name[strlen(p->data.name) - 1] = '\0';
                        }
                        break;
                    case 3:
                        // fflush(stdin);
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("Please enter the revised student gender:");
                        scanf("%c", &p->data.gender);
                        break;
                    case 4:
                        printf("Please enter the revised student score:");
                        scanf("%f", &p->data.score);
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default:
                        printf("This option does not exist, please re-enter the menu item!\n");
                    }
                    choice = -1;            // 输入错误的信息项编号 或者 未输入信息项编号
 
                    if(1 == flag)
                        break;
                }
                return;
            }
            else 
                p=p->next;
        }

        printf("There are no students with student id %s in the current one-way linked list!\n", stuId);
    }
    else
        printf("The one-way linked list does not exist or is empty, no student data to be modified!\n");
}

/* 显示所有学生的信息 */
void showList(LinkedNode *head)
{
    LinkedNode *p;
    int i;

    if(head->next)
    {
        printf("The information of all students in the linked list is as follows!\n");
        printf("%5s%15s%19s%12s%10s\n", "S/N", "StuID    ", "Name", "Gender", "Score");
        i=1;
        // 先让p指向第一个学生结点
        p = head->next;
        while(NULL != p)
        {
            int nameLen = strlen(p->data.name);
            // 每输出1个汉字，会占2个英文字符的位置，但是UTF8编码为3Bytes
            // 因此每多输出一个汉字，前面会少输出一个空格，应补足才能对齐。
            // 先统计字符串中汉字的个数chineseCount
            int chineseCount = 0, j;
            for (j=0; j<nameLen; j++)
            {
                if ((unsigned int)(p->data.name[j]) > 128)
                {
                    chineseCount++;
                }
            }
            chineseCount /= 3;

            printf("%5d%15s", i, p->data.stuId);

            for (j=0; j<chineseCount; j++)
            {
                printf(" ");
            }

            printf("%19s%9c%13.1f\n", p->data.name, p->data.gender, p->data.score);

            p = p->next;
            i++;
        }
    }
    else
        printf("The one-way linked list is empty!\n");
}

/* 保存所有学生的信息到文件 */
void save(LinkedNode *head)
{
    FILE *fp;
    LinkedNode *p;

    if((fp=fopen("stu1-1.dat", "wb"))==NULL)
    {
        printf("Failed to open the data file, so failed to save the student information!");
        return;
    }

    // 开始写文件
    p = head->next;

    while(p)    // while(p!=NULL)
    {
        fwrite(&(p->data), sizeof(Stu), 1, fp);
        p=p->next;
    }

    // 关闭文件
    fclose(fp);

    printf("All data in the one-way linked list has been written to the file successfully!\n");
}

int main()
{
    int choice=-1, seed;
    LinkedNode *head;

    // 设置window控制台（CMD或命令行窗口）为UTF-8格式
    system("chcp 65001");  
    
    // 获取备选的学生数据（在ps所指空间中，stuNum为空间单元数，即人数） 
    loadAllStudent();

    // 输入随机种子（插入时，需随机选取学生数据）
    printf("Please enter a random seed:");
    scanf("%d", &seed);
    srand(seed);
    
    // 初始化单链表 
    head = init();
    
    while(1)
    {
        menu();
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:    insert(head);
                    break;
            case 2:    del(head);
                    break;
            case 3:    modify(head);
                    break;
            case 4:    showList(head);
                    break;    
            case 0:    save(head);
                    exit(0);
                    break;    
            default:
                printf("\tThe menu item you entered does not exist, please select it again!\n");
        }
        choice = -1;
    }
    return 0;
}
