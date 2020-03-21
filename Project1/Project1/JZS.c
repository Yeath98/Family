#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
typedef struct TreeNode_1
{
	int Num;// 孩子数目
	char Name[20];           // 名字
	char Sex;                      // 性别 男M女F
	struct TreeNode_1 *NextNode[20];   //（配偶+孩子节点）
	struct TreeNode_1 *Parent;         // 祖先节点
}TreeNode;

//函数声明，避免（顺序）调用出错！！！！！！！！！！！！！！
void SubMenu_1(TreeNode *Node);
void Main_menutree(TreeNode *Tree);
void input_T(TreeNode *node);

void CreatTree(TreeNode *Node)//创建家族
{
	TreeNode *NewNode;
	NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	Node->NextNode[0] = NewNode;
	Node->NextNode[0] = NULL;
	printf("请输入%s的子女的数目:", Node->Name);
	scanf("%d", &(Node->Num));
	printf("请输入%s的配偶的姓名:", Node->Name);
	scanf("%s", NewNode->Name);
	if (strcmp(NewNode->Name, "0") == 0 && Node->Num == 0)
	{
		return;
	}
	if (Node->Sex == 'B')
	{
		NewNode->Sex = 'G';
	}
	else
	{
		NewNode->Sex = 'B';
	}
	NewNode->Num = 0;
	NewNode->NextNode[0] = NULL;
	Node->NextNode[0] = NewNode;
	Node->NextNode[0]->Parent = Node;
	for (int i = 1; i <= Node->Num; i++)
	{
		TreeNode *Child_Node;
		Child_Node = (TreeNode *)malloc(sizeof(TreeNode));
		printf("请输入%s的第%d个子女的名字:", Node->Name, i);
		scanf("%s", Child_Node->Name);
		printf("请输入%s的第%d个子女的性别(女G男B):", Node->Name, i);
		getchar();
		scanf("%c", &Child_Node->Sex);
		Child_Node->Num = 0;
		Child_Node->Parent = Node;
		Node->NextNode[i] = Child_Node;
		CreatTree(Node->NextNode[i]);
	}

}

void Outputall(TreeNode *Tnode)//显示全部
{
	printf("姓名：%s\t性别：", Tnode->Name);
	if (Tnode->Sex == 'G')
	{
		printf("女\n");
	}
	else
	{
		printf("男\n");
	}
	if (Tnode->NextNode[0] == NULL)
	{
		printf("没有配偶。");
		return;
	}
	if (Tnode->Sex == 'G')
	{
		printf("丈夫是:%s\n", Tnode->NextNode[0]->Name);
	}
	else
	{
		printf("妻子是:%s\n", Tnode->NextNode[0]->Name);
	}
	for (int i = 1; i <= Tnode->Num; i++)
	{
		printf("%s的第%d个子女的姓名:%s\n", Tnode->Name, i, Tnode->NextNode[i]->Name);
	}

	for (int i = 1; i <= Tnode->Num; i++)
	{
		Outputall(Tnode->NextNode[i]);
	}
}

void Outputm(TreeNode *Tnode)
{
	int Others = 0;//入赘或者嫁入
	if (Tnode == NULL)
	{
		printf("无信息。");
		return;
	}
	printf("你所寻找的信息如下:\n");
	printf("姓名:%s\n性别:", Tnode->Name);
	if (Tnode->Sex == 'G')
	{
		printf("女\n");
	}
	else
	{
		printf("男\n");
	}
	if (Others == 1)
	{
		if (Tnode->Sex == 'G')
		{
			printf("此人不在家谱内。\n");
			printf("其丈夫的姓名是:%s\n", Tnode->Parent->Name);
		}
		else
		{
			printf("此人不在家谱内。\n");
			printf("其妻子的姓名是:%s\n", Tnode->Parent->Name);
		}
		if (Tnode->Parent->Num != 0 && Tnode->Parent->Num > 0)
		{
			printf("其子女的信息如下:\n");
			for (int i = 1; i <= Tnode->Parent->Num; i++)
			{

				printf("姓名:%s\n性别:", Tnode->NextNode[i]->Name);
				if (Tnode->Sex == 'G')
				{
					printf("女\n");
				}
				else
				{
					printf("男\n");
				}
			}
		}
		system("pause");
	}
	if (Tnode->Parent != NULL)
	{
		if (Tnode->Parent->Sex = 'G')
		{
			printf("其父亲的姓名是:%s\n", Tnode->Parent->Name);
			printf("其母亲的姓名是:%s\n", Tnode->Parent->NextNode[0]->Name);
		}
		else
		{
			printf("其母亲的姓名是:%s\n", Tnode->Parent->Name);
			printf("其父亲的姓名是:%s\n", Tnode->Parent->NextNode[0]->Name);
		}
		system("pause");
	}
	else
	{
		printf("此人为祖先。\n");
		return;
	}

	if (Tnode->NextNode[0] != NULL)
	{
		if (Tnode->Sex == 'G')
		{
			printf("丈夫的姓名:%s\n", Tnode->NextNode[0]->Name);
		}
		else
		{
			printf("妻子的姓名:%s\n", Tnode->NextNode[0]->Name);
		}
		if (Tnode->Num != 0 && Tnode->Num > 0)
		{
			printf("其孩子的信息如下:\n");
			for (int i = 1; i <= Tnode->Num; i++)
			{
				printf("姓名:%s\n性别：", Tnode->NextNode[i]->Name);
				if (Tnode->Sex == 'G')
				{
					printf("女\n");
				}
				else
				{
					printf("男\n");
				}
			}
		}
		system("pause");
		Main_menutree(Tnode);

	}

}

void Change(TreeNode *Tnode, char Name[20])//修改函数
{
	if (Tnode != NULL)
	{
		if (strcmp(Name, Tnode->Name) == 0)
		{
			SubMenu_1(Tnode);
		}
		else
		{
			for (int i = 0; i <= Tnode->Num; i++)
			{
				Change(Tnode->NextNode[i], Name);
			}
		}
	}
}

TreeNode *Search(TreeNode *Tnode, char Name[20])//查找函数
{
	if (Tnode != NULL)
	{
		if (strcmp(Tnode->Name, Name) == 0)
		{
			Outputm(Tnode);
		}
		else
		{
			for (int i = 0; i <= Tnode->Num; i++)
			{
				Search(Tnode->NextNode[i], Name);
			}
		}
	}return NULL;
}

TreeNode *Search_c(TreeNode *Tnode, char Name[20])//查找函数
{
	if (Tnode != NULL)
	{
		if (strcmp(Tnode->Name, Name) == 0)
		{
			input_T(Tnode);
		}
		else
		{
			for (int i = 0; i <= Tnode->Num; i++)
			{
				Search(Tnode->NextNode[i], Name);
			}
		}
	}return NULL;
}

void input_T(TreeNode *node) {
	int i, j, k;
	if (node == NULL) { printf("未找到该人\n"); printf("按键返回主菜单\n"); system("pause"); Main_menutree(node); }
	else {
		while (1) {
			printf("\t\t\t1、添加孩子\n");
			printf("\t\t\t2、添加配偶\n");
			printf("\t\t\t3、返回主菜单\n");
			printf("\t\t\t选择要添加内容:");
			scanf("%d", &j);
			if (j == 1)
			{
				TreeNode *p;
				p = (TreeNode *)malloc(sizeof(TreeNode));
				p->Parent = node;
				printf("\t\t\t孩子姓名：");
				scanf("%s", p->Name);
				p->NextNode[0] = NULL;
				node->Num += 1;
				node->NextNode[node->Num] = p;
				Main_menutree(node);
			}
			if (j == 2) {
				TreeNode *p;
				p = (TreeNode *)malloc(sizeof(TreeNode));
				p->Parent = 0;
				printf("\t\t\t输入名字:");
				scanf("%s", p->Name);
				getchar();
				p->Num = node->Num;
				node->NextNode[0] = p;
				Main_menutree(node);
			}
			if (j == 3) { Main_menutree(node); }
		}
	}
}

void Main_menutree(TreeNode *Tree)//主菜单选项
{
	char Name[20];
	TreeNode *NewNode;
	NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	while (1)
	{
		system("cls");
		printf("\t\t\t-------# 操作选项-------\n");
		printf("\t\t\t-------1 输入信息-------\n");
		printf("\t\t\t-------2 查找成员-------\n");
		printf("\t\t\t-------3 添加成员-------\n");
		printf("\t\t\t-------4 家谱信息-------\n");
		printf("\t\t\t-------5 修改信息-------\n");
		printf("\t\t\t-------6 退出程序-------\n");
		printf("\t\t\t请选择要执行的操作: ");
		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("请输入姓名:");
			scanf("%s", Tree->Name);
			printf("请输入性别(女G,男B):");
			getchar();
			scanf("%c", &(Tree->Sex));
			Tree->Parent = NewNode;
			Tree->Parent = NULL;
			CreatTree(Tree);
			getchar();
			system("pause");
			break;


		case 2:
			if (strcmp(Tree->Name, "0") == 0)
			{
				printf("家谱图未建立请先建立。\n");
				getchar();
				system("pause");
				system("cls");
				break;
			}
			printf("请输入你所要查找的姓名：\n");
			scanf("%s", &Name);
			Outputm(Search(Tree, Name));
			getchar();
			system("pause");
			break;

		case 3:
			if (strcmp(Tree->Name, "0") == 0)
			{
				printf("家谱图未建立请先建立。\n");
				getchar();
				system("pause");
				break;
			}
			printf("请输入你所要添加的姓名：\n");
			scanf("%s", &Name);
			input_T(Search_c(Tree, Name));
			system("pause");
			break;



		case 4:
			if (strcmp(Tree->Name, "0") == 0)
			{
				printf("家谱图未建立请先建立。\n");
				getchar();
				system("pause");
				break;
			}
			Outputall(Tree);
			getchar();
			system("pause");
			break;


		case 5:
			if (strcmp(Tree->Name, "0") == 0)
			{
				printf("家谱图未建立请先建立。\n");
				getchar();
				system("pause");
				break;
			}
			SubMenu_1(Tree);
			getchar();
			system("pause");
			break;

		case 6:
			exit(0);
			break;
		}

	}
}

void SubMenu_1(TreeNode *Tnode)//修改子菜单
{
	while (1)
	{
		printf("-------# 操作选项-------\n");
		printf("-------1 修改个人信息-------\n");
		printf("-------2 修改父母信息-------\n");
		printf("-------3 修改兄妹信息-------\n");
		printf("-------4 修改子女信息-------\n");
		printf("-------5 修改配偶信息-------\n");
		printf("-------6 返回主菜单-------\n");
		printf("-------7 退出程序-------\n");
		printf("请选择要执行的操作: ");
		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			printf("当前个人信息如下：\n");
			printf("姓名：%s\t性别：", Tnode->Name);
			if (Tnode->Sex == 'G')
			{
				printf("女\n");
			}
			else
			{
				printf("男\n");
			}
			printf("请输入想要修改的姓名：");
			scanf("%s", Tnode->Name);
			getchar();
			printf("请输入想要修改的性别(男B女G)：");
			scanf("%c", &(Tnode->Sex));
			break;
		}
		case 2:
		{
			if (Tnode->Parent == NULL)
			{
				printf("无信息。\n");
				return;
			}
			else

				printf("当前父母信息如下:\n");
			printf("父亲姓名：%s\n", Tnode->Parent->Name);
			printf("母亲姓名：%s\n", Tnode->Parent->NextNode[0]->Name);
			printf("请输入修改信息:\n");
			printf("修改的父亲姓名：");
			scanf("%s", Tnode->Parent->Name);
			getchar();
			printf("修改的母亲姓名：");
			scanf("%s", Tnode->Parent->NextNode[0]->Name);
			getchar();
			break;
		}
		case 3:
		{
			if (Tnode->Parent == NULL)
			{
				printf("无信息。\n");
				return;
			}
			if (Tnode->Parent->Num == 1)
			{
				printf("无信息。\n");
				return;
			}
			printf("当前兄弟姐妹信息如下:\n");
			for (int i = 1; i <= Tnode->Parent->Num; i++)
			{
				if (strcmp(Tnode->Name, Tnode->Parent->NextNode[i]->Name) != 0)
				{
					printf("兄弟姐妹第%d个的姓名：%s\n性别：", i, Tnode->Parent->NextNode[i]->Name);
					if (Tnode->Parent->NextNode[i]->Sex == 'G')
					{
						printf("女\n");
					}
					else
					{
						printf("男\n");
					}
				}
			}

			printf("请输入修改信息：\n");
			for (int i = 1; i <= Tnode->Parent->Num; i++)
			{
				if (strcmp(Tnode->Name, Tnode->Parent->NextNode[i]->Name) != 0)
				{
					printf("兄弟姐妹第%d个的姓名：", i);
					scanf("%s", Tnode->Parent->NextNode[i]->Name);
					getchar();
					printf("性别：");
					scanf("%c", &(Tnode->Parent->NextNode[i]->Sex));
					getchar();
				}
			}
			break;
		}
		case 4:
		{
			if (Tnode->Num == 0)
			{
				printf("无信息。");
				getchar();
				return;
			}
			printf("当前子女的信息如下：\n");
			for (int i = 1; i <= Tnode->Num; i++)
			{
				printf("第%d个子女的姓名：%s\t性别：", i, Tnode->NextNode[i]->Name);
				if (Tnode->NextNode[i]->Sex == 'G')
				{
					printf("女\n");
				}
				else
				{
					printf("男\n");
				}
			}
			printf("请输入修改信息：\n");
			for (int i = 1; i <= Tnode->Num; i++)
			{
				printf("第%d个子女的姓名：", i);
				scanf("%s", Tnode->NextNode[i]->Name);
				getchar();
				printf("性别：");
				scanf("%c", &(Tnode->NextNode[i]->Sex));
				getchar();
			}
			break;
		}
		case 5:
		{
			system("cls");
			if (strcmp(Tnode->NextNode[0]->Name, "0") == 0)
			{
				printf("该成员暂无配偶和子女。\n");
				return;
			}
			if (Tnode->NextNode[0]->Sex == 'G')
			{
				printf("妻子是：%s\n", Tnode->NextNode[0]->Name);
			}
			else
			{
				printf("丈夫是：%s\n", Tnode->NextNode[0]->Name);
			}
			fflush(stdin);
			printf("请输入修改信息：\n");
			printf("姓名：");
			scanf("%s", Tnode->NextNode[0]->Name);

			break;
		}
		case 6:
			Main_menutree(Tnode);
			break;
		case 7:
			exit(0);
			break;
		}
	}
}

int main()
{
	TreeNode *Tree;
	Tree = (TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent = NULL;
	strcpy(Tree->Name, "0");
	Main_menutree(Tree);
	return 0;
}



