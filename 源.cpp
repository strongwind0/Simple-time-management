#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#define len sizeof(struct Memorandum)
//���õĺ�����

//�ṹ��
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

//����Ϊ���ò���
void free0(struct Memorandum* head)  //�ͷſռ�
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
struct Memorandum* chain()  //����������������
{
	FILE* fp;
	fp = fopen("��Ϣ.txt", "r+");
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
void chage(struct Memorandum* p1, struct Memorandum* p2)   //��������������
{
	struct Memorandum* p, a;
	a = *p1;
	*p1 = *p2;
	*p2 = a;
	p = p1->next;
	p1->next = p2->next;
	p2->next = p;
}
int save(struct Memorandum* head)  //����
{
	FILE* fp;
	struct Memorandum* p = NULL;
	p = head;
	if ((fp = fopen("��Ϣ.txt", "w")) == NULL)
	{
		printf("�ļ���ʧ��\n");
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
int print(struct Memorandum* head)  //��ӡ��������
{
	system("cls");
	struct Memorandum* p;
	p = head;
	while (p->next != NULL)
	{
		printf("�¼���%s\n", p->thing);
		printf("�ص㣺%s\n", p->place);
		printf("��ʼʱ�䣺%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day1, p->hour0, p->minute0);
		printf("����ʱ�䣺%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
		printf("ʱ����%d\n\n", p->lasttime);
		p = p->next;
	}
	return 1;
}
void wrongscanf()
{
	printf("�����������������");
	Sleep(3);
}

//����ΪĿ¼����
void mainmenu()
{
	printf("\n\n\n\n\n");
	printf("             plan\n");
	printf("          1.�����ճ�\n");
	printf("          2.�鿴�ճ�\n");
	printf("          3.�޸��ճ�\n");
	printf("          4.ɾ���ճ�\n");
	printf("          5.��ѯ�ճ�\n");
	printf("          6.��������\n");
	printf("          7.ì���Ų�\n");
	printf("          0.�˳�����\n");
	printf("          ���������ѡ��");
}
void menu2()
{
	printf("\n\n\n\n\n");
	printf("         �鿴��ʽ\n");
	printf("          1.ʱ��\n");
	printf("          2.�¼�\n");
	printf("          ���������ѡ��");
}
void menu3()
{
	printf("\n\n\n\n\n");
	printf("     ѡ����Ҫ�޸ĵ���Ŀ\n");
	printf("          1.�¼�\n");
	printf("          2.�ص�\n");
	printf("          3.ʱ��\n");
	printf("          ���������ѡ��");
}
void menu4()
{
	printf("\n\n\n\n\n");
	printf("     ѡ����Ҫɾ���ķ�ʽ\n");
	printf("          1.�¼�\n");
	printf("          2.ʱ��\n");
	printf("          ���������ѡ��");
}
void menu5()
{
	printf("\n\n\n\n\n");
	printf("      ��ѡ���ѯ��ʽ\n");
	printf("          1.�¼�\n");
	printf("          2.�ص�\n");
	printf("          3.ʱ��\n");
	printf("          ���������ѡ��");
}

//����Ϊ��¼����Ϣ����
int savenew(struct Memorandum* p)  //�ļ��洢
{
	FILE* fp;
	if ((fp = fopen("��Ϣ.txt", "a")) == NULL)
	{
		printf("�ļ���ʧ��\n");
		return -1;
	}
	fprintf(fp, "%s    %s    %d %d %d %d %d %d ", p->thing, p->place, p->year0, p->month0, p->day0, p->hour0, p->minute0, p->lasttime);
	fprintf(fp, "%d %d %d %d %d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
	fclose(fp);
	return 1;
}
void conversion(struct Memorandum* p)    //����ʱ�任��
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
struct Memorandum* creat()   //��������
{
	int choice1=1;
	struct Memorandum* head = NULL, * p1, * p2 = NULL;
	int i = 1;
	while (choice1 != 0)
	{
		system("cls");
		p1 = (struct Memorandum*)malloc(len);
		printf("ע�����\n");
		printf("1.����Ʋ��õ���24Сʱ��\n");
		printf("2.�¼����ص����������ó���50�֣��뾫��\n");
		printf("�������¼�����");
		scanf("%s", &p1->thing);
		printf("������ص㣺");
		scanf("%s", &p1->place);
		loop:
		printf("�����뿪ʼ������ʱ�֣��ո��������");
		scanf("%d %d %d %d %d", &p1->year0, &p1->month0, &p1->day0, &p1->hour0, &p1->minute0);
		if (starttimewrong(p1))
		{
			printf("��ʽ��������������\n");
			goto loop;
		}
		printf("������ʱ������λ�Ƿ֣���");
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
		printf("����¼���밴0��");
		scanf("%d", &choice1);
		if (choice1 == 0)
		{
			p1->next = NULL;
			return head;
		}
	}
}

//����Ϊ�鿴����
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
		printf("��0�ص���Ŀ¼���������ּ��ص��ϼ�Ŀ¼\n"); 
		scanf("%d", &choice2);
	}
	return 1;
}

//����Ϊ�޸Ĳ���
int thingmodify(struct Memorandum *p) //�¼��޸�
{
	printf("�������޸ĺ��¼���");
	scanf("%s", p->thing);
	return 1;
}
int placemodify(struct Memorandum* p) //�ص��޸�
{
	printf("�������޸ĺ�ص㣺");
	scanf("%s", p->place);
	return 1;
}
int timemodify(struct Memorandum* p) //ʱ���޸�
{
	loop:
	printf("�������޸ĺ���ʼʱ�䣨������ʱ�֣��ո��������");
	scanf("%d %d %d %d %d", &p->year0, &p->month0, &p->day0, &p->hour0, &p->minute0);
	if (starttimewrong(p))
	{
		printf("��ʽ��������������\n");
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
				printf("ʱ����%s�¼�ì�ܣ�����������\n", p2->thing);
				goto loop;
			}
		}
		p2 = p2->next;
	}
	printf("������ʱ����");
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
		printf("����Ϊ�գ�������������\n");
		Sleep(3000);
		return 0;
	}
	while (choice3 != 0)
	{
		print(head);
		printf("�������޸��¼�����");
		scanf("%s", thing, sizeof(thing));
		system("cls");
		p = head;
		while (p->next != NULL)
		{
			if (strcmp(p->thing, thing) == 0)
			{
				printf("�¼���%s\n", p->thing);
				printf("�ص㣺%s\n", p->place);
				printf("��ʼʱ�䣺%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
				printf("����ʱ�䣺%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
				printf("����ʱ�䣺%d\n\n", p->lasttime);
				num++;
				break;
			}
			p = p->next;
		}
		if (num == 1)//���¼�������ŵ����õĺ����У����������¼����ַ����ȽϺ��ӡ������(����)
		{
			menu3();
			scanf("%d", &choi3);
			switch (choi3)   //switch���ѡ��
			{
			case 1:thingmodify(p); break;
			case 2:placemodify(p); break;
			case 3:timemodify(p); break;
			default:wrongscanf(); break;
			}
			save(head);    //�޸ĺ���ú�������
		}
		else    //û���ҵ� else ��������޴��¡�
		{
			printf("���޴���\n");
		}
		printf("�Ƿ񷵻���һ����0�Ż���Ŀ¼���������ּ�������һ������");	//�ж��Ƿ񷵻�
		scanf("%d", &choice3);
	}
	return 1;
}

//������ɾ������
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
	printf("������ʱ���(������ʱ�֣��ո����)��");
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
							printf("��ɾ��\n");
							return 1;
						}
					}
				}
			}
		}
		p2 = p1;
		p1 = p1->next;
	}
	printf("���޴���\n");
	return 0;
}
int dellthing(struct Memorandum* head)
{
	struct Memorandum* p1, * p2;
	p1 = head;
	p2 = head;
	char thing[100];
	printf("������ɾ���¼�����");
	scanf("%s", &thing);
	while (p1->next != NULL)
	{
		if (strcmp(p1->thing, thing) == 0)
		{
			dell(head, p1, p2);
			printf("��ɾ��\n");
			return 1;
		}
		else
		{
			p2 = p1;
			p1 = p1->next;
		}
	}
	printf("���޴���\n");
	return 0;
}
int del(struct Memorandum* head)
{
	int choice4 = 1, choi4 = 1;
	if (head->next == NULL)
	{
		printf("����Ϊ�գ�������������\n");
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
		printf("�Ƿ������0������Ŀ¼���������ּ���������");
		scanf("%d", &choice4);
	}
	return 1;
}

//����Ϊ��ѯ����
void thinglook(struct Memorandum* head)  //�¼����Ҳ���ӡ
{
	int num = 0;
	system("cls");
	struct Memorandum* p;
	char thing[100];
	printf("�������¼�����");
	scanf("%s", thing, sizeof(thing));
	printf("\n");
	p = head;
	while (p->next != NULL)
	{
		if (strcmp(p->thing, thing) == 0)
		{
			printf("�¼���%s\n", p->thing);
			printf("�ص㣺%s\n", p->place);
			printf("��ʼʱ�䣺%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
			printf("����ʱ�䣺%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
			printf("����ʱ�䣺%d\n\n", p->lasttime);
			num++;
		}
		p = p->next;
	}
	if (num == 0)
	{
		printf("���޴���\n");
	}
}
void placelook(struct Memorandum* head)  //�ص���Ҳ���ӡ
{
	int num = 0;
	struct Memorandum* p;
	char place[100];
	printf("�������¼�����");
	scanf("%s", &place);
	p = head;
	while (p->next != NULL)
	{
		if (strcmp(p->thing, place) == 0)
		{
			printf("�¼���%s\n", p->thing);
			printf("�ص㣺%s\n", p->place);
			printf("��ʼʱ�䣺%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
			printf("����ʱ�䣺%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
			printf("����ʱ�䣺%d\n\n", p->lasttime);
			num++;
		}
		p = p->next;
	}
	if (num == 0)
	{
		printf("���޴���\n");
	}
}
void timelook(struct Memorandum* head)  //ʱ����Ҳ���ӡ
{
	int num = 0;
	system("cls");
	int year, month, day, hour, minute;
	struct Memorandum* p;
	p = head;
	printf("���������ʱ��㣺");
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
							printf("�¼���%s\n", p->thing);
							printf("�ص㣺%s\n", p->place);
							printf("��ʼʱ�䣺%4d %2d %2d %2d %2d\n", p->year0, p->month0, p->day0, p->hour0, p->minute0);
							printf("����ʱ�䣺%4d %2d %2d %2d %2d\n", p->year1, p->month1, p->day1, p->hour1, p->minute1);
							printf("����ʱ�䣺%d\n\n", p->lasttime);
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
		printf("���޴���\n");
	}
}
int lookup(struct Memorandum* head)
{
	int choice5 = 1, choi5 = 1;
	if (head->next == NULL)
	{
		printf("����Ϊ�գ�������������\n");
		Sleep(3000);
		return 0;
	}
	while (choice5 != 0)
	{
		system("cls");
		menu5();
		scanf("%d", &choi5);
		switch (choi5)  //switch���ѡ���֧
		{
		case 1:thinglook(head); break;
		case 2:placelook(head); break;
		case 3:timelook(head); break;
		default:wrongscanf(); break;
		}
		printf("�Ƿ��������(0���أ��������ּ�����)��");
		scanf("%d",&choice5);
	}
	return 1;
}

//����
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
	struct tm t;              //tm�ṹָ��
	time_t now;              //����time_t���ͱ���
	struct Memorandum* p;
	while (1)
	{
		time(&now);            //��ȡϵͳ���ں�ʱ��
		localtime_s(&t, &now); //��ȡ�������ں�ʱ��
		p = head;
		system("cls");
		printf("\n\n\n\n\n       ����ʱ�䣺%4d %2d %2d   %2d:%2d %2d\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
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
								printf("������Ӧ������\n");
								printf("�¼���%s\n", p->thing);
								printf("ʱ�䣺%s\n", p->place);
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

//�¼�ʱ��ì���Ų�(��Ҫ�޸�)
int troubleshooting(struct Memorandum* head)
{
	system("cls");
	struct Memorandum* p1, * p2;
	long int ymdhm1, ymdhm2, ymdhm0;
	int i=0;
	seebytime(head);  //�����Ų�
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
				printf("\n\n\n\n\n     %s��%s����ʱ��ì�ܣ��뾡���޸�\n",p1->thing,p2->thing);
				i++;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	if (i == 0)
	{
		printf("\n\n\n\n\n         δ����ì��");
		Sleep(3000);
		return 0;
	}
	else
	{
		Sleep(5000);
	}
	
}

//������
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
