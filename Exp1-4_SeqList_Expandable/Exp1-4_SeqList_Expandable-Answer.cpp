#define _CRT_SECURE_NO_WARNINGS
// Exp1-4_SeqList_Expandable
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_INIT_LENGTH 4    // 动态数组的初始长度
#define LIST_INCREMENT 3    // 动态数组长度不够时，每次增加的长度
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

// 动态顺序表结构体
typedef struct 
{
    Stu *base;        // 存放学生的动态数组的起始地址，数组大小可以扩充
    int listSize;    // 当前顺序表中数组单元的个数
    int length;        // 当前表中元素的个数（肯定小于数组单元的个数）
} SeqList;

Stu *ps;
int stuNum;

// Get alternative all students' data
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
    printf("\n\t***Expandable Sequence List(Space can be expanded dynamically)***\n");
    printf("\t*       1 Insert a student                                      *\n");
    printf("\t*       2 Delete a student                                      *\n");
    printf("\t*       3 Modify student's information                          *\n");
    printf("\t*       4 Output the information of all students                *\n");
    printf("\t*       0 Save the data and exit the program                    *\n");
    printf("\t*****************************************************************\n");
}

/*  Check whether the file stu1-4.dat exist in the current directory.
    If it exists, the data will be read from it to construct a sequence list.
*/
void init(SeqList &seqList)
{
    FILE *fp;
    Stu stmp;
    int i;

    /* Give the array initial memory space */
    seqList.base = (Stu *)malloc(sizeof(Stu)*LIST_INIT_LENGTH); 
    
    // 设置顺序表中动态数组的初始长度为LIST_INIT_LENGTH
    seqList.listSize = LIST_INIT_LENGTH;
    
    // 设置顺序表的初始长度为0
    seqList.length = 0;

    // 打开文件
    if((fp=fopen("stu1-4.dat", "rb"))==NULL)
        return;

    // 开始读文件
    i=0;
    fread(&stmp, sizeof(Stu), 1, fp);        // 先尝试着读第一个学生

    while(!feof(fp))                        // 检测文件尚未结束，则说明读到了一个学生
    {
        if(i < seqList.listSize)
        {
            seqList.base[i] = stmp;                    // 将读到的学生stmp复制到顺序表中pData数组的i号单元
            
            fread(&stmp, sizeof(Stu), 1, fp);    // 从文件读下一个学生的同时，执行i++
            i++;
        }
        else
        {
            // 必须先扩充顺序表中动态数组s的空间，然后再继续;
            // 给顺序表中的动态数组增加LIST_INCREMENT个单元的空间
            seqList.base = (Stu *)realloc(seqList.base, (seqList.listSize+LIST_INCREMENT)*sizeof(Stu));
            seqList.listSize = seqList.listSize+LIST_INCREMENT;
        }
    }

    seqList.length = i;    // 读到的学生个数即为顺序表长度

    // 关闭文件
    fclose(fp);
}

/* 获取一个学生的信息 */
Stu getAStudent()
{
    // Generate a random number, which is in [0, stunUM-1]
    int r = rand() % stuNum;
    return ps[r];
}

void insert(SeqList &seqList)
{
    int poi, i;
    char choice, c;

    if(seqList.listSize > seqList.length)        // 如果动态数组中尚有空闲空间，则可以插入
    {
        printf("There are %d elements in the current sequence list, and the current inserted position can only be in [1,%d]!\n", seqList.length, seqList.length+1);
        printf("Please enter the inserted location:\n");
        scanf("%d", &poi);

        // 判断插入位置是否合法，若不合法，则要求再次输入
        while(poi<=0 || poi>=(seqList.length+2))
        {
            printf("This position is not valid, inserted position can only be in [1,%d]!\n", seqList.length + 1);
            printf("Please re-enter the inserted location:\n");
            scanf("%d", &poi);
        }

        // Start from the p->length element
        // Move all elements back in the [p->length, poi] section
        // Insert a student into the sequence list, 
        // and the sequence list length increase 1.
        
for (i = seqList.length - 1; i >= poi - 1; i--)
{
	seqList.base[i + 1] = seqList.base[i];
}

// Insert a student into the sequence list, 
// and the sequence list length increase 1.
seqList.base[poi - 1] = getAStudent();
seqList.length++;


        printf("%s inserted successfully!\n", seqList.base[poi-1].name);
    }
    else    // 如果数组中已没有空闲空间，则可以必须先扩充空间，然后才能插入
    {
        // fflush(stdin);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("The array space of the current sequence list is full. Do you need to expand the space?(Press Y or y to expand, press any key to cancel the expansion)\n");
        choice = getchar();

        if('Y'==choice || 'y'==choice)
        {
            // 给顺序表中的动态数组增加LIST_INCREMENT个单元的空间
            // 此时空间已经足够，因此再次调用insert()函数，完成插入过程（此处为递归）
            
seqList.base = (Stu *)realloc(seqList.base, (seqList.listSize+LIST_INCREMENT)*sizeof(Stu));
seqList.listSize = seqList.listSize + LIST_INCREMENT;
			
printf("The array space of the current sequence list has been expanded to %d, it is ready to continue insertion!\n", seqList.listSize);
insert(seqList);

        }
    }
}

/* Remove a student from the sequence list */
void del(SeqList &seqList)
{
    int i, j;
    char stuId[16], choice, c;

    if(seqList.length > 0)    // 顺序表中元素个数大于0，才有元素可以删除
    {
        // fflush(stdin);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Please enter the student ID of the student to be deleted:\n");
        scanf("%s", stuId);

        // 先查找要删除学生的位置（下标）
        
for(i=0; i<=seqList.length-1; i++)
{
	if(!strcmp(stuId, seqList.base[i].stuId))	// 找到要删除的学生
		break;
}


        // 如果前面的for循环是通过执行break;语句退出的，
        // 则说明找到了要删除的学生（在pData数组的i号单元）
        if(i<=seqList.length-1)                    
        {
            printf("The student's information you want to delete is as follows:\n");
            printf("%s\t%s\t%c\t%.1f\t\n", seqList.base[i].stuId, seqList.base[i].name, seqList.base[i].gender, seqList.base[i].score);
            // fflush(stdin);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Do you want to delete the student?(press Y or Y to delete, any key to cancel deletion)\n");
            choice = getchar();

            if('Y'==choice || 'y'==choice)
            {
                printf("The student whose id is %s has been deleted successfully!\n", seqList.base[i].stuId);
                // 开始删除，删除方法为：从第i+1号单元开始，将顺序表pData数组中
                // 第i+1号单元至第SL.length-1号单元之间的所有元素，依次前移一个单元。
                // 数组长度减一
                
for(j=i+1; j<=seqList.length-1; j++)
{
	seqList.base[j-1] = seqList.base[j];
}
seqList.length--;

            }
            else
                printf("Deletion has been canceled!\n");        
        }
        else
            printf("The student you want to delete is not found in the current sequence list!\n");
    }
    else
        printf("Current sequence list is empty, no students to delete!\n");
}

/* Find and modify a student's information */
void modify(SeqList &seqList)
{
    int i, flag=0, choice;
    char stuId[16], c;
    
    if(seqList.length > 0)
    {
        // fflush(stdin);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Please enter the student id of the student to be modified:\n");
        scanf("%s", stuId);

        // 先查找要修改学生的位置（下标）
        for(i=0; i<=seqList.length-1; i++)
        {
            if(!strcmp(stuId, seqList.base[i].stuId))    
                break;
        }

        // 找到要修改的学生（在pData数组的i号单元）
        if(i <= seqList.length-1)
        {
            while(1)
            {
                printf("Current student's information is as follows:\n");
                printf("1--StuID:%s\n", seqList.base[i].stuId);
                printf("2--Name:%s\n", seqList.base[i].name);
                printf("3--Gender:%c\n", seqList.base[i].gender);
                printf("4--Score:%.1f\n", seqList.base[i].score);
                printf("Please select the number of the modify menu item(Enter 0 to complete the modification):\n");
                scanf("%d", &choice);

                switch(choice)
                {
                case 1:
                    // fflush(stdin);
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Please enter the revised student's ID:\n");
                    scanf("%s", seqList.base[i].stuId); 
                    break;
                case 2:
                    // fflush(stdin);
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Please enter the revised student's name:\n");
                    fgets(seqList.base[i].name, STU_NAME_MAXLEN, stdin);
                    // The last character of the string name is '\n'
                    if (seqList.base[i].name[strlen(seqList.base[i].name) - 1] == '\n')
                    {
                        seqList.base[i].name[strlen(seqList.base[i].name) - 1] = '\0';
                    }
                    break;
                case 3:
                    // fflush(stdin);
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Please enter the revised student's gender:\n");
                    scanf("%c", &seqList.base[i].gender);
                    break;
                case 4:
                    printf("Please enter the revised student's score:\n");
                    scanf("%f", &seqList.base[i].score);
                    break;
                case 0:
                    flag=1;
                    break;
                default:
                    printf("This option does not exist, please re-enter the menu item!\n");
                }

                if(1==flag)
                    break;
            }
        }
        else
            printf("The student you want to modify is not found in the current sequence list!\n");
    }
    else
        printf("Current sequence list is empty, no students to modify!\n");
}

/* 显示所有学生的信息 */
void showList(SeqList seqList)
{
    int i;

    if(seqList.length > 0)
    {
        printf("The number of cells in the sequence list is %d, and the number of elements in the current sequence list is %d.\n", seqList.listSize, seqList.length);
        printf("The information of all students in the sequence list is as follows!\n");
        printf("%5s%15s%19s%12s%10s\n", "S/N", "StuID    ", "Name", "Gender", "Score");
        for(i=0; i<=seqList.length-1; i++)
        {
            int nameLen = strlen(seqList.base[i].name);
            // 每输出1个汉字，会占2个英文字符的位置，但是UTF8编码为3Bytes
            // 因此每多输出一个汉字，前面会少输出一个空格，应补足才能对齐。
            // 先统计字符串中汉字的个数chineseCount
            int chineseCount = 0, j;
            for (j = 0; j < nameLen; j++)
            {
                if ((unsigned int)(seqList.base[i].name[j]) > 128)
                {
                    chineseCount++;
                }
            }
            chineseCount /= 3;

            printf("%5d%15s", i + 1, seqList.base[i].stuId);

            for (j = 0; j < chineseCount; j++)
            {
                printf(" ");
            }

            printf("%19s%9c%13.1f\n", seqList.base[i].name, seqList.base[i].gender, seqList.base[i].score);
        }
    }
    else
        printf("The current sequence list is empty!\n");
}

/* 保存所有学生的信息到文件 */
void save(SeqList seqList)
{
    FILE *fp;
    int i;

    // 打开文件
    if((fp=fopen("stu1-4.dat", "wb"))==NULL)
    {
        printf("Cannot open the data file, failed to save the student's information, program exit abnormally!\n");
        exit(-1);
    }

    // 开始写文件
    for(i=0; i<=seqList.length-1; i++)
    {
        fwrite(&(seqList.base[i]), sizeof(Stu), 1, fp);
    }

    // 关闭文件
    fclose(fp);

    printf("All data in the sequence list has been written to the file successfully!\n");
}

int main()
{
    int choice = -1, seed;
    char c;
    SeqList list;        // 定义顺序表list

    // Set the window console (cmd or command line window) to UTF-8 format
    system("chcp 65001");

    init(list);            // 在init()函数中为其成员s开辟空间，并设置数组元素个数为0

    // Get alternative all students' data（In the space of ps point to, stuNum is the number of spatial cells or students） 
    loadAllStudent();

    // Input the random seed
    printf("Please enter a random seed:\n");
    scanf("%d", &seed);

    // Set the random seed
    srand(seed);

    while(1)
    {
        menu();
        printf("\tPlease select a menu item: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
        case 1:
            insert(list);
            break;
        case 2:
            del(list);
            break;
        case 3:
            modify(list);
            break;
        case 4:
            showList(list);
            break;    
        case 0:
            save(list);
            exit(0);
            break;    
        default:
            // If the user enters an alphabetic menu item instead of an integer, 
            // the buffer needs to be emptied
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\tThe menu item you entered does not exist, please select it again!\n");
        }
        choice = -1;
    }
    return 0;
}