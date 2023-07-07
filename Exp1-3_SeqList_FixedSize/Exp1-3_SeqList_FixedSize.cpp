#define _CRT_SECURE_NO_WARNINGS
// Exp1-3_SeqList_FixedSize
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STU_NUM_MAX 20
#define STU_ID_MAXLEN 16
#define STU_NAME_MAXLEN 20

typedef struct
{
    char stuId[STU_ID_MAXLEN];
    char name[STU_NAME_MAXLEN];
    char gender;
    float score;
} Stu;

// Define the sequence list type
typedef struct 
{
    Stu data[STU_NUM_MAX];    // Store student's information, array size MAX cannot be expanded
    int length;        // Number of elements in the current list
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
    printf("\n\t***Fixed-length Sequence List(Space cannot be expanded)***\n");
    printf("\t*       1 Insert a student                               *\n");
    printf("\t*       2 Delete a student                               *\n");
    printf("\t*       3 Modify student's information                   *\n");
    printf("\t*       4 Output the information of all students         *\n");
    printf("\t*       0 Save the data and exit the program             *\n");
    printf("\t**********************************************************\n");
}

/*  Check whether the file stu1-3.dat exist in the current directory.
    If it exists, the data will be read from it to construct a sequence list.
*/
SeqList *init()
{
    FILE *fp;
    Stu stmp;
    int i;

    /*  给顺序表开辟内存空间，并初始化为空表；

        此处做法很多，可以将开辟空间的代码放到主函数中，
        也可以在主函数中用定义局部变量 SeqList list; 的形式，
        这两种情况都需要用通过引用参数或指针变量将list双向传递给init()函数。

        但切记，千万不能在init()函数中用定义局部变量 SeqList list; 这种形式来开辟空间，
        因为局部变量是存放在栈内存区的，
        init()函数调用结束时，其局部变量list将会直接回收，
        该变量的空间（就是整个顺序表的空间）无法保留到主函数中，
        也就不能继续传递给其它函数对该表作进一步的增删元素处理了。
    */

    SeqList *p=(SeqList *)malloc(sizeof(SeqList));
    
    p->length = 0;    // Set the initial length of the sequence list to 0

    if((fp=fopen("stu1-3.dat", "rb"))==NULL)
    {
        return p;
    }

    i=0;
    fread(&stmp, sizeof(Stu), 1, fp);    // Try reading a student first

    while(!feof(fp))    // If the file is not finished, a student has been read
    {
        p->data[i] = stmp;    // Copy the student stmp to cell 1 of the data array in the sequence list
        
        fread(&stmp, sizeof(Stu), 1, fp);    // Read the next student from the file
        i++;
    }
    p->length = i;    // The number of students which be read from the file is the length of the sequence list

    fclose(fp);
    return p;
}

/* 获取一个学生的信息 */
Stu getAStudent()
{
    // Generate a random number, which is in [0, stunUM-1]
    int r = rand() % stuNum;
    return ps[r];
}

/* Insert a student into the sequence list */
void insert(SeqList *p)
{
    int poi, i;

    if(STU_NUM_MAX > p->length)
    {
        printf("There are %d elements in the current sequence list, and the current inserted position can only be in [1,%d]!\n", p->length, p->length+1);
        printf("Please enter the inserted location:\n");
        scanf("%d", &poi);

        // Determine whether the insert position is valid. 
        // If not, ask to re-input until the insert position is valid. 
         

        // Start from the p->length element
        // Move all elements back in the [p->length, poi] section
        // Insert the student into the sequence list, 
        // and the sequence list length increase 1.
         

        printf("%s inserted successfully!\n", p->data[poi-1].name);
    }
    else
        printf("The sequence list is full, no more elements can be inserted!\n");
}

/* Remove a student from the sequence list */
void del(SeqList *pList)
{
    int i, j;
    char stuId[STU_ID_MAXLEN], choice, c;

    // There are any elements can be deleted only when the number of elements in the sequence list is greater than 0
    if(pList->length > 0)            
    {
        // fflush(stdin);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Please enter the student ID of the student to be deleted:\n");
        scanf("%s", stuId);
        
        // First find the location or index where you want to delete the student
         

        // If the previous for loop was executed by break statement to exit,
        // then the student to delete is found (in cell 1 of the array data).
        if(i <= pList->length-1)                    
        {
            printf("The student's information you want to delete is as follows:\n");
            printf("%s\t%s\t%c\t%.1f\t\n", pList->data[i].stuId, pList->data[i].name, pList->data[i].gender, pList->data[i].score);
            // fflush(stdin);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Are you sure to delete the student? Press y or Y to delete, or any key to cancel deletion!\n");
            choice = getchar();

            if('Y'==choice || 'y'==choice)
            {
                printf("The student whose id is %s has been deleted successfully!\n", pList->data[i].stuId);

                // Start to delete, the deletion method is as follows:
                // Start from the cell i+1, 
                // move all elements in the [i+1, p->length-1] section forward one cell.
                // The length of the sequence list is reduced by one
                 
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
void modify(SeqList *p)
{
    int i, flag=0, choice;
    char stuId[STU_ID_MAXLEN], c;
    
    if(p->length > 0)
    {
        // fflush(stdin);    
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Please enter the student id of the student to be modified:\n");
        scanf("%s", stuId);

        // First find the location or index of the student to be modified
        for(i=0; i<=p->length-1; i++)
        {
            if(!strcmp(stuId, p->data[i].stuId))    
                break;
        }

        // Find the student to modify (in unit i of the data array)
        if(i <= p->length-1)
        {
            while(1)
            {
                printf("Current student's information is as follows:\n");
                printf("1--StuID:%s\n", p->data[i].stuId);
                printf("2--Name:%s\n", p->data[i].name);
                printf("3--gender:%c\n", p->data[i].gender);
                printf("4--Score:%.1f\n", p->data[i].score);
                printf("Please select the number of the modify menu item(Enter 0 to complete the modification):\n");
                scanf("%d", &choice);

                switch(choice)
                {
                case 1:
                    // fflush(stdin);
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Please enter the revised student's ID:\n");
                    scanf("%s", p->data[i].stuId); 
                    break;

                case 2:
                    // fflush(stdin);
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Please enter the revised student's name:\n");
                    fgets(p->data[i].name, STU_NAME_MAXLEN, stdin);
                    // The last character of the string name is '\n'
                    if (p->data[i].name[strlen(p->data[i].name) - 1] == '\n')
                    {
                        p->data[i].name[strlen(p->data[i].name) - 1] = '\0'; 
                    }
                    break;

                case 3:
                    // fflush(stdin);
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Please enter the revised student's gender:\n");
                    scanf("%c", &p->data[i].gender);
                    break;

                case 4:
                    printf("Please enter the revised student's score:\n");
                    scanf("%f", &p->data[i].score);
                    break;

                case 0:
                    flag = 1;
                    break;

                default:
                    printf("This option does not exist, please re-enter the menu item!\n");
                }

                if(1 == flag)
                    break;
            }
        }
        else
            printf("The student you want to modify is not found in the current sequence list!\n");
    }
    else
        printf("Current sequence list is empty, no students to modify!\n");
}

/* Display the information of all students in the sequence list */
void showList(SeqList *p)
{
    int i;

    if(p->length > 0)
    {
        printf("The number of cells in the sequence list is %d, and the number of elements in the current sequence list is %d.\n", STU_NUM_MAX, p->length);
        printf("The information of all students in the sequence list is as follows!\n");
        printf("%5s%15s%19s%12s%10s\n", "S/N", "StuID    ", "Name", "Gender", "Score");
        for(i=0; i<=p->length-1; i++)
        {
            int nameLen = strlen(p->data[i].name);
            // 每输出1个汉字，会占2个英文字符的位置，但是UTF8编码为3Bytes
            // 因此每多输出一个汉字，前面会少输出一个空格，应补足才能对齐。
            // 先统计字符串中汉字的个数chineseCount
            int chineseCount = 0, j;
            for (j = 0; j < nameLen; j++)
            {
                if ((unsigned int)(p->data[i].name[j]) > 128)
                {
                    chineseCount++;
                }
            }
            chineseCount /= 3;

            printf("%5d%15s", i+1, p->data[i].stuId);

            for (j = 0; j < chineseCount; j++)
            {
                printf(" ");
            }

            printf("%19s%9c%13.1f\n", p->data[i].name, p->data[i].gender, p->data[i].score);
        }
    }
    else
        printf("The current sequence list is empty!\n");
}

/* Save the information of all students to a file stu.dat */
void save(SeqList *p)
{
    FILE *fp;
    int i;

    if((fp=fopen("stu1-3.dat", "wb"))==NULL)
    {
        printf("Cannot open the data file, failed to save the student's information, program exit abnormally!\n");
        exit(-1);
    }

    for(i=0; i<=p->length-1; i++)
    {
        // fwrite(&(p->data[i]), sizeof(Stu), 1, fp);
        fwrite(p->data+i, sizeof(Stu), 1, fp);
    }
    // fwrite(p->data, sizeof(Stu), p->length, fp);

    fclose(fp);

    printf("All data in the sequence list has been written to the file successfully!\n");
}

int main()
{
    int choice = -1, seed;
    char c;
    SeqList *pList;

    // Set the window console (cmd or command line window) to UTF-8 format
    system("chcp 65001");  

    pList = init();

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
            insert(pList);
            break;
        case 2:
            del(pList);
            break;
        case 3:
            modify(pList);
            break;
        case 4:
            showList(pList);
            break;    
        case 0:
            save(pList);
            exit(0);
            break;    
        default:
            // If the user enters an alphabetic menu item instead of an integer, 
            // the buffer needs to be emptied
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\tThe menu item you entered does not exist, please select it again!\n");
        }

        // Indicates that the menu item is not selected or the menu item is incorrectly selected
        choice = -1;    
    }
    return 0;
}
