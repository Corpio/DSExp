#define _CRT_SECURE_NO_WARNINGS
// Exp1-2_LinkedList_NoHead
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
    Stu data;            // 当前结点中存储的学生数据
    struct LNode *next;    // 下一个结点的地址
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
        printf("Failed to open the data file, failed to save the student information!");
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
    printf("\n\t***The one-way linked list without head***\n");
    printf("\t*     1 Choose a student & insert        *\n");
    printf("\t*     2 Delete a student                 *\n");
    printf("\t*     3 Modify a student                 *\n");
    printf("\t*     4 Show all the students            *\n");
    printf("\t*     0 Save & Exit                      *\n");
    printf("\t******************************************\n");
    printf("\tPlease select a menu item:\n");
}

/*  Check whether the file stu1-2.dat exist in the current directory.
    If it exists, the data will be read from it to construct a linked list.
*/
LinkedNode *init()
{
    FILE *fp;
    Stu stmp;
    LinkedNode *head, *p, *rear = NULL;

    // 将头指针设置为NULL，初始化为空表 
    head = NULL;

    if ((fp = fopen("stu1-2.dat", "rb")) == NULL)
        return head;

    // 打开成功，则开始读文件
    fread(&stmp, sizeof(Stu), 1, fp);

    while (!feof(fp))
    {
        // 开辟一个结点空间
        p = (LinkedNode *)malloc(sizeof(LinkedNode));

        // 构造结点
        p->data = stmp;
        p->next = NULL;

        // 将构造好的结点从尾部插入单向链表
        if (NULL == head)    // 如果插入的是第一个结点
        {
            rear = p;
            head = p;
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

/* 插入一个学生到不带头结点的单链表中，形参用C++的引用参数 */
void insertV1(LinkedNode *&head)
{
    int poi, count = 0;
    LinkedNode *pre, *pNew;        // pre指向插入位置的直接前驱结点，pNew用于开辟新结点空间
    pre = head;

    printf("Please enter the location of the student to be inserted:\n");
    scanf("%d", &poi);

    // 如果插入到表头（第1个数据元素之前），特殊情况，先处理掉或直接排除
    if (1 == poi)
    {
        // 开辟空间
        // 构造结点（随机选中一个结点存入） 
        // 插入新结点到单向链表中表头
        
		pNew = (LinkedNode *)malloc(sizeof(LinkedNode));

		// 构造结点（随机选中一个结点存入） 
		pNew->data = getAStudent();
		pNew->next = NULL;

		// 插入新结点到单向链表中pre所指结点之后
		pNew->next = head;
		head = pNew;

        printf("%s has been inserted successfully!\n", pNew->data.name);
        return;
    }

    // 当未到链表尾部，并且未到第poi-2个学生结点（即插入点的直接前驱）时
    
	while (pre != NULL && count < poi - 2)
	{
		pre = pre->next;
		count++;
	}


    // 如果找到了正确的插入位置
    if (count == poi - 2 && pre != NULL)
    {
        // 开辟空间
        // 构造结点（随机选中一个结点存入） 
        // 插入新结点到单向链表中pre所指结点之后
        
		// 开辟空间
		pNew = (LinkedNode *)malloc(sizeof(LinkedNode));

		// 构造结点（随机选中一个结点存入） 
		// 生成一个[0, stuNum-1]的随机数
		int r = rand() % stuNum;
		pNew->data = ps[r];
		pNew->next = NULL;

		// 插入新结点到单向链表中pre所指结点之后
		pNew->next = pre->next;
		pre->next = pNew;

        printf("%s has been inserted successfully!\n", pNew->data.name);
    }
    else                 // 如果插入位置不合法
        printf("The inserted position is invalid!\n");
}

/* 插入一个学生到不带头结点的单链表中，形参用二级指针 */
void insertV2(LinkedNode **ph)
{
    int poi, count = 0;
    LinkedNode *pre, *pNew;        // pre指向插入位置的直接前驱结点，pNew用于开辟新结点空间
    pre = *ph;

    printf("Please enter the location of the student to be inserted:\n");
    scanf("%d", &poi);

    // 如果插入到表头（第1个数据元素之前），特殊情况，先处理掉或直接排除
    if (1 == poi)
    {
        // 开辟空间
        // 构造结点（随机选中一个结点存入） 
        // 插入新结点到单向链表的表头
        
		// 开辟空间
		pNew = (LinkedNode *)malloc(sizeof(LinkedNode));

		// 构造结点（随机选中一个结点存入） 
		// 生成一个[0, stuNum-1]的随机数
		int r = rand() % stuNum;
		pNew->data = ps[r];
		pNew->next = NULL;

		// 插入新结点到单向链表中pre所指结点之后
		pNew->next = *ph;
		*ph = pNew;

        printf("%s has been inserted successfully!\n", pNew->data.name);
        return;
    }

    // 当未到链表尾部，并且未到第poi-2个学生结点（即插入点的直接前驱）时
    
	while (pre != NULL && count < poi - 2)
	{
		pre = pre->next;
		count++;
	}


    // 如果找到了正确的插入位置
    if (count == poi - 2 && pre != NULL)
    {
        // 开辟空间
        // 构造结点（随机选中一个结点存入） 
        // 插入新结点到单向链表中pre所指结点之后
        
		pNew = (LinkedNode *)malloc(sizeof(LinkedNode));

		// 构造结点（随机选中一个结点存入） 
		// 生成一个[0, stuNum-1]的随机数
		int r = rand() % stuNum;
		pNew->data = ps[r];
		pNew->next = NULL;

		// 插入新结点到单向链表中pre所指结点之后
		pNew->next = pre->next;
		pre->next = pNew;

        printf("%s has been inserted successfully!\n", pNew->data.name);
    }
    else                 // 如果插入位置不合法
        printf("The inserted position is invalid!\n");
}

/* 从不带头结点的单链表中删除一个指定学生 */
void del(LinkedNode *&head)
{
    char stuId[STU_ID_MAXLEN], c;
    int flag = 0;
    LinkedNode *pre, *q;

    if (NULL == head)  // 先排除链表为空的情况
    {
        printf("The one-way linked list is empty, no student data to delete!\n");
        return;
    }

    // fflush(stdin);
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Please enter the id of the student to be deleted:\n");
    scanf("%s", stuId);

    // 如果待删除的是链表中的第一个数据结点
    
	if (!strcmp(head->data.stuId, stuId)) 
	{
		q = head;			// q指向待删除结点
		head = q->next;		// 头指针head指向链表中的新的第一个结点（有可能赋值为空）

		printf("The student of id %s has been deleted successfully!\n", q->data.stuId);
		free(q);			// 先提示，后释放

		return;
	}


    pre = head;  // 如果待删除的不是链表中的第一个数据结点
    while (NULL != pre->next)
    {
        // 如果找到了待删除结点的直接前驱    
        // q指向待删除结点
        // 先让q所指结点从链表中断开
        // 先提示，后释放
        
		if (!strcmp(pre->next->data.stuId, stuId)) 	// 如果找到了待删除结点的直接前驱	
		{
			q = pre->next;	// q指向待删除结点
			pre->next = q->next;	// 先让q所指结点从链表中断开

			printf("The student of id %s has been deleted successfully!\n", q->data.stuId);
			free(q);		// 先提示，后释放

			flag = 1;
			break;
		}
		else
			pre = pre->next;

    }

    if (0 == flag)
        printf("The student you want to delete was not found!\n");
}

/* 查找指定学生，并修改其信息（修改后的姓名字符串中，不能含有中文字符） */
void modify(LinkedNode *head)
{
    char c;

    if (NULL != head)
    {
        char stuId[STU_ID_MAXLEN];
        int choice, flag = 0;
        LinkedNode *p;

        // p最终要指向待修改的学生结点，所以先让其指向第一个学生结点
        p = head;

        printf("Please enter the student ID of the student to be modified:\n");
        scanf("%s", stuId);

        while (p != NULL)
        {
            if (!strcmp(p->data.stuId, stuId))    // 如果找到待修改的学生
            {
                while (1)
                {
                    printf("Current student information is as follows:\n");
                    printf("1--StuID:%s\n", p->data.stuId);
                    printf("2--Name:%s\n", p->data.name);
                    printf("3--Gender:%c\n", p->data.gender);
                    printf("4--Score:%.1f\n", p->data.score);
                    printf("Please select a menu item to be modified (enter 0 to complete the modification):\n");
                    scanf("%d", &choice);

                    switch (choice)
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
                        if ('\n' == p->data.name[strlen(p->data.name) - 1])
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

                    if (1 == flag)
                        break;
                }
                return;
            }
            else
                p = p->next;
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

    if (head)
    {
        printf("The information of all students in the linked list is as follows!\n");
        printf("%5s%15s%19s%12s%10s\n", "S/N", "StuID    ", "Name", "Gender", "Score");
        i = 1;
        // 先让p指向第一个学生结点
        p = head;
        while (NULL != p)
        {
            int nameLen = strlen(p->data.name);
            // 每输出1个汉字，会占2个英文字符的位置，但是UTF8编码为3Bytes
            // 因此每多输出一个汉字，前面会少输出一个空格，应补足才能对齐。
            // 先统计字符串中汉字的个数chineseCount
            int chineseCount = 0, j;
            for (j = 0; j < nameLen; j++)
            {
                if ((unsigned int)(p->data.name[j]) > 128)
                {
                    chineseCount++;
                }
            }
            chineseCount /= 3;

            printf("%5d%15s", i, p->data.stuId);

            for (j = 0; j < chineseCount; j++)
                printf(" ");

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
    int count;

    if ((fp = fopen("stu1-2.dat", "wb")) == NULL)
    {
        printf("Cannot open the data file, failed to save the student information!");
        return;
    }

    // 开始写文件
    p = head;

    count = 0;
    while (p)    // while(p!=NULL)
    {
        fwrite(&(p->data), sizeof(Stu), 1, fp);
        count++;
        p = p->next;
    }
    // 最后将count写入文件
    // fwrite(&count, sizeof(int), 1, fp);

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

    while (1)
    {
        menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:    insertV1(head);
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

    system("pause");
    return 0;
}