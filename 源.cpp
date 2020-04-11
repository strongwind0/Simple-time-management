#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#define len sizeof(struct Memorandum)
//调用的函数库

//结构体
struct Memorandum
{
	char thing[101];
	char place[101];
	int  year0;
	int  month0;
	int  day0;
	int  hour0;
	int  minute0;
	long lasttime;
	int  year1;
	int  month1;
	int  day1;
	int  hour1;
	int  minute1;
	struct Memorandum* next;
};

//以下为公用部分
void free0(struct Memorandum* head)  //释放空间
{
	struct Memorandum* p1, * p2;
	p1 = head;
	while (p1->next != NULL)
	{
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	free(p1);
}
struct Memorandum* chain()  //生成所有任务链表
{
	FILE* fp;
	fp = fopen("信息.txt", "r+");
	struct Memorandum* head = NULL, * p1 = NULL, * p2 = NULL;
	int i = 1;
	while (!feof(fp))
	{
		p1 = (struct Memorandum*)malloc(len);
		fscanf(fp, "%s", p1->thing);
		fscanf(fp, "%s", p1->place);
		fscanf(fp, "%d", &p1->year0);
		fscanf(fp, "%d", &p1->month0);
		fscanf(fp, "%d", &p1->day0);
		fscanf(fp, "%d", &p1->hour0);
		fscanf(fp, "%d", &p1->minute0);
		fscanf(fp, "%d", &p1->lasttime);
		fscanf(fp, "%d", &p1->year1);
		fscanf(fp, "%d", &p1->month1);
		fscanf(fp, "%d", &p1->day1);
		fscanf(fp, "%d", &p1->hour1);
		fscanf(fp, "%d", &p1->minute1);
		if (i == 1)
		{
			head = p1;
		}
		else
		{
			p2->next = p1;
		}
		p2 = p1;
		i++;
	}
	p1->next = NULL;
	return head;
}
void chage(struct Memorandum* p1, struct Memorandum* p2)   //交换（用于排序）
{
	struct Memorandum* p, a;
	a = *p1;
	*p1 = *p2;
	*p2 = a;
	p = p1->next;
	p1->next = p2->next;
	p2->next = p;
}
int save(struct Memorandum* head)  //保存
{
	FILE* fp;
	struct Memorandum* p = NULL;
	p = head;
	if ((fp = fopen("信息.txt", "w")) == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	while (p->next != NULL)
	{
		fprintf(fp, "%s    %s    %d %d %d %d %d %d ", p->thing, p->place, p->year0, p->month0, p->day0, p->hour0, p->minute0, p->lasttime);
		fprintf(fp, "%d %d %d %d %d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
		p = p->next;
	}
	fclose(fp);
	return 1;
}
int print(struct Memorandum* head)  //打印所有任务
{
	system("cls");
	struct Memorandum* p;
	p = head;
	while (p->next != NULL)
	{
		printf("事件：%s\n", p->thing);
		printf("地点：%s\n", p->place);
		printf("起始时间：%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day1, p->hour0, p->minute0);
		printf("结束时间：%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
		printf("时长：%d\n\n", p->lasttime);
		p = p->next;
	}
	return 1;
}
void wrongscanf()
{
	printf("输入错误，请重新输入");
	Sleep(3);
}

//以下为目录函数
void mainmenu()
{
	printf("\n\n\n\n\n");
	printf("             plan\n");
	printf("          1.输入日程\n");
	printf("          2.查看日程\n");
	printf("          3.修改日程\n");
	printf("          4.删除日程\n");
	printf("          5.查询日程\n");
	printf("          6.闹铃提醒\n");
	printf("          7.矛盾排查\n");
	printf("          0.退出程序\n");
	printf("          请输入你的选择：");
}
void menu2()
{
	printf("\n\n\n\n\n");
	printf("         查看方式\n");
	printf("          1.时间\n");
	printf("          2.事件\n");
	printf("          请输入你的选择：");
}
void menu3()
{
	printf("\n\n\n\n\n");
	printf("     选择你要修改的项目\n");
	printf("          1.事件\n");
	printf("          2.地点\n");
	printf("          3.时间\n");
	printf("          请输入你的选择：");
}
void menu4()
{
	printf("\n\n\n\n\n");
	printf("     选择你要删除的方式\n");
	printf("          1.事件\n");
	printf("          2.时间\n");
	printf("          请输入你的选择：");
}
void menu5()
{
	printf("\n\n\n\n\n");
	printf("      请选择查询方式\n");
	printf("          1.事件\n");
	printf("          2.地点\n");
	printf("          3.时间\n");
	printf("          请输入你的选择：");
}

//以下为新录入信息部分
int savenew(struct Memorandum* p)  //文件存储
{
	FILE* fp;
	if ((fp = fopen("信息.txt", "a")) == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	fprintf(fp, "%s    %s    %d %d %d %d %d %d ", p->thing, p->place, p->year0, p->month0, p->day0, p->hour0, p->minute0, p->lasttime);
	fprintf(fp, "%d %d %d %d %d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
	fclose(fp);
	return 1;
}
void conversion(struct Memorandum* p)    //结束时间换算
{
	p->minute1 = p->minute0 + p->lasttime;
	p->hour1 = p->hour0 + (p->minute1) / 60;
	p->minute1 = p->minute1 % 60;
	p->day1 = p->day0 + (p->hour1 / 24);
	p->hour1 = p->hour1 % 24;
	if (p->month0 == 1 || p->month0 == 3 || p->month0 == 5 || p->month0 == 7 || p->month0 == 8 || p->month0 == 10 || p->month0==12)
	{
		if (p->day1 > 31)
		{
			p->month1 = p->month0 + 1;
			p->day1 -= 31;
			if (p->month0 > 12)
			{
				p->year1 = p->year0 + 1;
				p->month1 -= 12;
			}
			else
			{
				p->year1 = p->year0;
			}
		}
		else
		{
			p->month1 = p->month0;
			p->year1 = p->year0;
		}
	}
	else if (p->month0 == 2)
	{
		if ((p->year0 % 4 == 0 && p->year0 % 100 != 0) || (p->year0 % 400 == 0))
		{
			if (p->day1 > 29)
			{
				p->month1 = p->month0 + 1;
				p->day1 -= 29;
			}
			else
			{
				p->month1 = p->month0;
				p->year1 = p->year0;
			}
		}
		else
		{
			if (p->day1 > 28)
			{
				p->month1 = p->month0 + 1;
				p->day1 -= 28;
			}
			else
			{
				p->month1 = p->month0;
				p->year1 = p->year0;
			}
		}
	}
	else
	{
		if (p->day1 > 30)
		{
			p->month1 = p->month0 + 1;
			p->day1 -= 30;
		}
		else
		{
			p->month1 = p->month0;
			p->year1 = p->year0;
		}
	}
}
int starttimewrong(struct Memorandum* p)
{
	switch (p->month0)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: if (p->day0 > 31) return 1; else break;
	case 4:
	case 6:
	case 9:
	case 11:if (p->day0 > 30) return 1; else break;
	case 2:{
		if ((p->year0 % 4 == 0 && p->year0 % 100 != 0) || (p->year0 % 400 == 0))
		{
			if (p->day0 > 29)
			{
				return 1;
			}
			else break;
		}
		else
		{
			if (p->day0 > 28)
			{
				return 1;
			}
			else break;
		}
	        }
	default:return 1;
	}
	if (p->hour0 > 23 || p->minute0 > 59)
	{
		return 1;
	}
	return 0;
}
struct Memorandum* creat()   //链表生成
{
	int choice1=1;
	struct Memorandum* head = NULL, * p1, * p2 = NULL;
	int i = 1;
	while (choice1 != 0)
	{
		system("cls");
		p1 = (struct Memorandum*)malloc(len);
		printf("注意事项：\n");
		printf("1.本设计采用的是24小时制\n");
		printf("2.事件、地点描述均不得超过50字，请精简\n");
		printf("请输入事件名：");
		scanf("%s", &p1->thing);
		printf("请输入地点：");
		scanf("%s", &p1->place);
		loop:
		printf("请输入开始年月日时分（空格隔开）：");
		scanf("%d %d %d %d %d", &p1->year0, &p1->month0, &p1->day0, &p1->hour0, &p1->minute0);
		if (starttimewrong(p1))
		{
			printf("格式错误，请重新输入\n");
			goto loop;
		}
		printf("请输入时长（单位是分）：");
		scanf("%d", &p1->lasttime);
		conversion(p1);
		savenew(p1);
		if (i == 1)
		{
			head = p1;
		}
		else
		{
			p2->next = p1;
		}
		p2 = p1;
		i++;
		printf("结束录入请按0：");
		scanf("%d", &choice1);
		if (choice1 == 0)
		{
			p1->next = NULL;
			return head;
		}
	}
}

//以下为查看部分
void seebytime(struct Memorandum* head)
{
	struct Memorandum* p1, * p2, * p;
	p1 = head;
	while (p1->next != NULL)
	{
		
		p2 = p1->next;
		p = p1;
		while (p2->next != NULL)
		{
			if ((p->year0 * 10000 + p->month0 * 100 + p->day0) > (p2->year0 * 10000 + p2->month0 * 100 + p2->day0))
			{
				p = p2;
			}
			if ((p->year0 * 10000 + p->month0 * 100 + p->day0) == (p2->year0 * 10000 + p2->month0 * 100 + p2->day0))
			{
				if ((p->hour0 * 60 + p->minute0) > (p2->hour0 * 60 + p2->minute0))
				{
					p = p2;
				}
				
			}
			p2 = p2->next;
		}
		chage(p1, p);
		p1 = p1->next;
	}
}
void seebyname(struct Memorandum* head)
{
	struct Memorandum* p1, * p2, * p;
	p1 = head;
	while (p1->next != NULL)
	{
		p2 = p1->next;
		p = p1;
		while (p2->next != NULL)
		{
			if (strcmp(p->thing, p2->thing) > 0)
			{
				p = p2;
			}
			p2 = p2->next;
		}
		chage(p1, p);
		p1 = p1->next;
	}
}
int see(struct Memorandum* head)
{
	int choice2=1;
	while (choice2 != 0)
	{
		system("cls");
		menu2();
		scanf("%d", &choice2);
		switch (choice2)
		{
		case 1:seebytime(head); print(head); break;
		case 2:seebyname(head); print(head); break;
		default:wrongscanf(); break;
		}
		printf("按0回到主目录，其他数字键回到上级目录\n"); 
		scanf("%d", &choice2);
	}
	return 1;
}

//以下为修改部分
int thingmodify(struct Memorandum *p) //事件修改
{
	printf("请输入修改后事件：");
	scanf("%s", p->thing);
	return 1;
}
int placemodify(struct Memorandum* p) //地点修改
{
	printf("请输入修改后地点：");
	scanf("%s", p->place);
	return 1;
}
int timemodify(struct Memorandum* p) //时间修改
{
	loop:
	printf("请输入修改后起始时间（年月日时分，空格隔开）：");
	scanf("%d %d %d %d %d", &p->year0, &p->month0, &p->day0, &p->hour0, &p->minute0);
	if (starttimewrong(p))
	{
		printf("格式错误，请重新输入\n");
		goto loop;
	}
	struct Memorandum* head, * p2;
	head = chain();
	p2 = head;
	int year, month, day, hour, minute;
	long int num1, num2, num3;
	while (p2->next != NULL)
	{
		if (strcmp(p2->place, p->place) != 0)
		{
			minute = p2->minute1 + 10;
			hour = p2->minute1 + minute / 60;
			minute = minute % 60;
			day = p2->day1 + hour / 24;
			hour = hour % 24;
			month = p2->month1;
			year = p2->year1;
			switch (month)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12: {
				month = month + day / 31;
				day = day % 31;
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11: {
				month = month + day / 30;
				day = day % 30;
				break;
			}
			case 2: {
				if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				{
					month = month + day / 29;
					day = day % 29;
				}
				else
				{
					month = month + day / 28;
					day = day % 28;
				}
				break;
			}
			}
			if (month > 12)
			{
				year = year + month / 12;
				month = month % 12;
			}
			num1 = p->year0 * 100000000 + p->month0 * 1000000 + p->day0 * 10000 + p->hour0 * 100 + p->minute0;
			num2 = year * 100000000 + month * 1000000 + day * 10000 + hour * 100 + minute;
			num3 = p2->year1 * 100000000 + p2->month1 * 1000000 + p2->day1 * 10000 + p2->hour1 * 100 + p2->minute0;
			if (num1 > num3&& num1 < num2)
			{
				printf("时间与%s事件矛盾，请重新输入\n", p2->thing);
				goto loop;
			}
		}
		p2 = p2->next;
	}
	printf("请输入时长：");
	scanf("%d", &p->lasttime);
	conversion(p);
	return 1;
}
int modify(struct Memorandum* head)
{
	int num = 0;
	int choice3 = 1, choi3 = 0;
	char thing[100];
	struct Memorandum* p = NULL;
	if (head->next == NULL)
	{
		printf("数据为空，请先输入数据\n");
		Sleep(3000);
		return 0;
	}
	while (choice3 != 0)
	{
		print(head);
		printf("请输入修改事件名：");
		scanf("%s", thing, sizeof(thing));
		system("cls");
		p = head;
		while (p->next != NULL)
		{
			if (strcmp(p->thing, thing) == 0)
			{
				printf("事件：%s\n", p->thing);
				printf("地点：%s\n", p->place);
				printf("起始时间：%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
				printf("结束时间：%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
				printf("持续时间：%d\n\n", p->lasttime);
				num++;
				break;
			}
			p = p->next;
		}
		if (num == 1)//把事件名输入放到调用的函数中，遍历所有事件，字符串比较后打印，返回(函数)
		{
			menu3();
			scanf("%d", &choi3);
			switch (choi3)   //switch语句选择
			{
			case 1:thingmodify(p); break;
			case 2:placemodify(p); break;
			case 3:timemodify(p); break;
			default:wrongscanf(); break;
			}
			save(head);    //修改后调用函数存下
		}
		else    //没有找到 else 输出“查无此事”
		{
			printf("查无此事\n");
		}
		printf("是否返回上一级（0放回主目录，其余数字键返回上一级）：");	//判断是否返回
		scanf("%d", &choice3);
	}
	return 1;
}

//以下是删除部分
int dell(struct Memorandum* head, struct Memorandum* p1, struct Memorandum* p2)
{
	if (p1 == head)
	{
		head = p1->next;
	}
	else
	{
		p2->next = p1->next;
	}
	free(p1);
	save(head);
	return 1;
}
int delltime(struct Memorandum* head)
{
	struct Memorandum* p1, * p2;
	p1 = head;
	p2 = head;
	int year, month, day, hour, minute;
	printf("请输入时间点(年月日时分，空格隔开)：");
	scanf("%d %d %d %d %d", &year, &month, &day, &hour, &minute);
	while (p1->next != NULL)
	{
		if (p1->year0 <= year && p1->year1 >= year)
		{
			if (p1->month0 <= month && p1->month1 >= month)
			{
				if (p1->day0 <= day && day >= p1->day1)
				{
					if (p1->hour0 <= hour && p1->hour1 >= hour)
					{
						if (p1->minute0 >= minute && p1->minute1 >= minute)
						{
							dell(head, p1, p2);
							printf("已删除\n");
							return 1;
						}
					}
				}
			}
		}
		p2 = p1;
		p1 = p1->next;
	}
	printf("查无此事\n");
	return 0;
}
int dellthing(struct Memorandum* head)
{
	struct Memorandum* p1, * p2;
	p1 = head;
	p2 = head;
	char thing[100];
	printf("请输入删除事件名：");
	scanf("%s", &thing);
	while (p1->next != NULL)
	{
		if (strcmp(p1->thing, thing) == 0)
		{
			dell(head, p1, p2);
			printf("已删除\n");
			return 1;
		}
		else
		{
			p2 = p1;
			p1 = p1->next;
		}
	}
	printf("查无此事\n");
	return 0;
}
int del(struct Memorandum* head)
{
	int choice4 = 1, choi4 = 1;
	if (head->next == NULL)
	{
		printf("数据为空，请先输入数据\n");
		Sleep(3000);
		return 0;
	}
	while (choice4 != 0)
	{
		print(head);
		menu4();
		scanf("%d", &choi4);
		switch (choi4)
		{
		case 1:dellthing(head); break;
		case 2:delltime(head); break;
		default:wrongscanf();break;
		}
		printf("是否继续（0返回主目录，其余数字键继续）：");
		scanf("%d", &choice4);
	}
	return 1;
}

//以下为查询部分
void thinglook(struct Memorandum* head)  //事件查找并打印
{
	int num = 0;
	system("cls");
	struct Memorandum* p;
	char thing[100];
	printf("请输入事件名：");
	scanf("%s", thing, sizeof(thing));
	printf("\n");
	p = head;
	while (p->next != NULL)
	{
		if (strcmp(p->thing, thing) == 0)
		{
			printf("事件：%s\n", p->thing);
			printf("地点：%s\n", p->place);
			printf("起始时间：%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
			printf("结束时间：%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
			printf("持续时间：%d\n\n", p->lasttime);
			num++;
		}
		p = p->next;
	}
	if (num == 0)
	{
		printf("查无此事\n");
	}
}
void placelook(struct Memorandum* head)  //地点查找并打印
{
	int num = 0;
	struct Memorandum* p;
	char place[100];
	printf("请输入事件名：");
	scanf("%s", &place);
	p = head;
	while (p->next != NULL)
	{
		if (strcmp(p->thing, place) == 0)
		{
			printf("事件：%s\n", p->thing);
			printf("地点：%s\n", p->place);
			printf("起始时间：%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
			printf("结束时间：%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
			printf("持续时间：%d\n\n", p->lasttime);
			num++;
		}
		p = p->next;
	}
	if (num == 0)
	{
		printf("查无此事\n");
	}
}
void timelook(struct Memorandum* head)  //时间查找并打印
{
	int num = 0;
	system("cls");
	int year, month, day, hour, minute;
	struct Memorandum* p;
	p = head;
	printf("请输入查找时间点：");
	scanf("%d %d %d %d %d", &year, &month, &day, &hour, &minute);
	printf("\n");
	while (p->next != NULL)
	{
		if (year >= p->year0 && year <= p->year1)
		{
			if (month >= p->month0 && month <= p->month1)
			{
				if (day >= p->day0 && day <= p->day1)
				{
					if (hour >= p->hour0 && hour <= p->hour1)
					{
						if (minute >= p->minute0 && minute <= p->minute1)
						{
							printf("事件：%s\n", p->thing);
							printf("地点：%s\n", p->place);
							printf("起始时间：%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
							printf("结束时间：%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
							printf("持续时间：%d\n\n", p->lasttime);
							num++;
						}
					}
				}
			}
		}
		p = p->next;
	}
	if (num == 0)
	{
		printf("查无此事\n");
	}
}
int lookup(struct Memorandum* head)
{
	int choice5 = 1, choi5 = 1;
	if (head->next == NULL)
	{
		printf("数据为空，请先输入数据\n");
		Sleep(3000);
		return 0;
	}
	while (choice5 != 0)
	{
		system("cls");
		menu5();
		scanf("%d", &choi5);
		switch (choi5)  //switch语句选择分支
		{
		case 1:thinglook(head); break;
		case 2:placelook(head); break;
		case 3:timelook(head); break;
		default:wrongscanf(); break;
		}
		printf("是否继续查找(0返回，其余数字键继续)：");
		scanf("%d",&choice5);
	}
	return 1;
}

//闹铃
void beep()
{
	int switch_ = 1;
	while (switch_ < 4)
	{
		Beep(500, 2000);
		Beep(400, 2000);
		Beep(450, 2000);
		Beep(300, 2000);
		Beep(300, 2000);
		Beep(450, 2000);
		Beep(500, 2000);
		Beep(400, 2000);
		switch_++;
	}
}
void beil(struct Memorandum* head)
{
	struct tm t;              //tm结构指针
	time_t now;              //声明time_t类型变量
	struct Memorandum* p;
	while (1)
	{
		time(&now);            //获取系统日期和时间
		localtime_s(&t, &now); //获取当地日期和时间
		p = head;
		system("cls");
		printf("\n\n\n\n\n       现在时间：%4d %2d %2d   %2d:%2d %2d\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
		Sleep(500);
		while (p->next != NULL)
		{
			if (p->year0 == (t.tm_year + 1900))
			{
				if (p->month0 == (t.tm_mon + 1))
				{
					if (p->day0 == t.tm_mday)
					{
						if (p->hour0 == t.tm_hour)
						{
							if (p->minute0 == t.tm_min)
							{
								printf("你现在应办事项\n");
								printf("事件：%s\n", p->thing);
								printf("时间：%s\n", p->place);
								beep();
							}
						}
					}
				}
			}
			p = p->next;
		}
	}

}

//事件时间矛盾排查(需要修改)
int troubleshooting(struct Memorandum* head)
{
	system("cls");
	struct Memorandum* p1, * p2;
	long int ymdhm1, ymdhm2, ymdhm0;
	int i=0;
	seebytime(head);  //便于排查
	p1 = head;
	p2 = head;
	while (p1->next != NULL)
	{
		p2 = p1->next;
		ymdhm1 = p1->year0 * 100000000 + p1->month0 * 1000000 + p1->day0 * 10000 + p1->hour0 * 100 + p1->minute0;
		ymdhm2 = p1->year1 * 100000000 + p1->month1 * 1000000 + p1->day1 * 10000 + p1->hour1 * 100 + p1->minute1;
		while (p2->next != NULL)
		{
			ymdhm0 = p2->year0 * 100000000 + p2->month0 * 1000000 + p2->day0 * 10000 + p2->hour0 * 100 + p2->minute0;
			if (ymdhm0 <= ymdhm2 && ymdhm0 >= ymdhm1)
			{
				printf("\n\n\n\n\n     %s和%s存在时间矛盾，请尽快修改\n",p1->thing,p2->thing);
				i++;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	if (i == 0)
	{
		printf("\n\n\n\n\n         未发现矛盾");
		Sleep(3000);
		return 0;
	}
	else
	{
		Sleep(5000);
	}
	
}

//主函数
int main()
{
	struct Memorandum* head = NULL;
	int choice0 = 1;
	while (choice0 != 0)
	{
		system("cls");
		mainmenu();
		scanf("%d", &choice0);
		switch (choice0)
		{
		case 0:return 0;
		case 1:head = creat(); free0(head); break;
		case 2:head = chain(); see(head); free0(head); break;
		case 3:head = chain(); modify(head); free0(head); break;
		case 4:head = chain(); del(head);  break;
		case 5:head = chain(); lookup(head); free0(head); break;
		case 6:head = chain(); beil(head); free0(head); break;
		case 7:head = chain(); troubleshooting(head); free0(head); break;
		default:wrongscanf(); Sleep(3000); break;
		}
	}
}
