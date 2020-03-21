#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
typedef struct TreeNode_1
{
	int Num;// ������Ŀ
	char Name[20];           // ����
	char Sex;                      // �Ա� ��MŮF
	struct TreeNode_1 *NextNode[20];   //����ż+���ӽڵ㣩
	struct TreeNode_1 *Parent;         // ���Ƚڵ�
}TreeNode;

//�������������⣨˳�򣩵��ó�������������������������������
void SubMenu_1(TreeNode *Node);
void Main_menutree(TreeNode *Tree);

void CreatTree(TreeNode *Node)//��������
{
	TreeNode *NewNode;
	NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	Node->NextNode[0] = NewNode;
	Node->NextNode[0] = NULL;
	printf("������%s����Ů����Ŀ:", Node->Name);
	scanf("%d", &(Node->Num));
	printf("������%s����ż������:", Node->Name);
	scanf("%s", NewNode->Name);
	if (strcmp(NewNode->Name, "0") == 0 && Node->Num == 0)
	{
		return;
	}
	if (Node->Sex == 'B' )
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
		printf("������%s�ĵ�%d����Ů������:", Node->Name, i);
		scanf("%s", Child_Node->Name);
		printf("������%s�ĵ�%d����Ů���Ա�(ŮG��B):", Node->Name, i);
		getchar();
		scanf("%c", &Child_Node->Sex);
		Child_Node->Num = 0;
		Child_Node->Parent = Node;
		Node->NextNode[i] = Child_Node;
		CreatTree(Node->NextNode[i]);
	}

}

void Outputall(TreeNode *Tnode)//��ʾȫ��
{
	printf("������%s\t�Ա�", Tnode->Name);
	if (Tnode->Sex == 'G')
	{
		printf("Ů\n");
	}
	else
	{
		printf("��\n");
	}
	if (Tnode->NextNode[0] == NULL)
	{
		printf("û����ż��");
		return;
	}
	if (Tnode->Sex == 'G')
	{
		printf("�ɷ���:%s\n", Tnode->NextNode[0]->Name);
	}
	else
	{
		printf("������:%s\n", Tnode->NextNode[0]->Name);
	}
	for (int i = 1; i <= Tnode->Num; i++)
	{
		printf("%s�ĵ�%d����Ů������:%s\n", Tnode->Name, i, Tnode->NextNode[i]->Name);
	}

	for (int i = 1; i <= Tnode->Num; i++)
	{
		Outputall(Tnode->NextNode[i]);
	}
}

void Outputm(TreeNode *Tnode)
{
	int Others = 0;//��׸���߼���
	if (Tnode == NULL)
	{
		printf("����Ϣ��");
		return;
	}
	printf("����Ѱ�ҵ���Ϣ����:\n");
	printf("����:%s\n�Ա�:", Tnode->Name);
	if (Tnode->Sex == 'G')
	{
		printf("Ů\n");
	}
	else
	{
		printf("��\n");
	}
	if (Others == 1)
	{
		if (Tnode->Sex == 'G')
		{
			printf("���˲��ڼ����ڡ�\n");
			printf("���ɷ��������:%s\n", Tnode->Parent->Name);
		}
		else
		{
			printf("���˲��ڼ����ڡ�\n");
			printf("�����ӵ�������:%s\n", Tnode->Parent->Name);
		}
		if (Tnode->Parent->Num != 0 && Tnode->Parent->Num > 0)
		{
			printf("����Ů����Ϣ����:\n");
			for (int i = 1; i <= Tnode->Parent->Num; i++)
			{

				printf("����:%s\n�Ա�:", Tnode->NextNode[i]->Name);
				if (Tnode->Sex == 'G')
				{
					printf("Ů\n");
				}
				else
				{
					printf("��\n");
				}
			}
		}
		system("pause");
	}
	if (Tnode->Parent != NULL)
	{
		if (Tnode->Parent->Sex = 'G')
		{
			printf("��ĸ�׵�������:%s\n", Tnode->Parent->Name);
			printf("�丸�׵�������:%s\n", Tnode->Parent->NextNode[0]->Name);
		}
		else
		{
			printf("�丸�׵�������:%s\n", Tnode->Parent->Name);
			printf("��ĸ�׵�������:%s\n", Tnode->Parent->NextNode[0]->Name);
		}
		system("pause");
	}
	else
	{
		printf("����Ϊ���ȡ�\n");
	}

	if (Tnode->NextNode[0] != NULL)
	{
		if (Tnode->Sex == 'G')
		{
			printf("�ɷ������:%s\n", Tnode->NextNode[0]->Name);
		}
		else
		{
			printf("���ӵ�����:%s\n", Tnode->NextNode[0]->Name);
		}
		if (Tnode->Num != 0 && Tnode->Num > 0)
		{
			printf("�亢�ӵ���Ϣ����:\n");
			for (int i = 1; i <= Tnode->Num; i++)
			{
				printf("����:%s\n�Ա�", Tnode->NextNode[i]->Name);
				if (Tnode->Sex == 'G')
				{
					printf("Ů\n");
				}
				else
				{
					printf("��\n");
				}
			}
		}
		system("pause");
		Main_menutree(Tnode);

	}

}

void Change(TreeNode *Tnode, char Name[20])//�޸ĺ���
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

TreeNode *Search(TreeNode *Tnode, char Name[20])//���Һ���
{
	if (Tnode != NULL)
	{
		if (strcmp(Tnode->Name,Name) == 0)
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
void input_T(TreeNode *node);

TreeNode *Search_c(TreeNode *Tnode, char Name[20])//���Һ���
{
	if (Tnode != NULL)
	{
		if (strcmp(Tnode->Name,Name) == 0)
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
/*
int Num;// ������Ŀ
	char Name[20];           // ����
	char Sex;                      // �Ա� ��MŮF
	struct TreeNode_1 *NextNode[20];   //����ż+���ӽڵ㣩
	struct TreeNode_1 *Parent;
	*/

void input_T(TreeNode *node){
     int i,j,k;
     if(node==NULL){printf("δ�ҵ�����\n");printf("�����������˵�\n");system("pause");Main_menutree(node);}
     else{
          while(1){
          printf("\t\t\t1�����Ӻ���\n");
          printf("\t\t\t2��������ż\n");
          printf("\t\t\t3���������˵�\n");
          printf("\t\t\tѡ��Ҫ��������:");
          scanf("%d",&j);
          if(j==1)
               {TreeNode *p;
                p = (TreeNode *)malloc(sizeof(TreeNode));
                p->Parent = node;
                printf("\t\t\t����������");
                scanf("%s",p->Name);
                p->NextNode[0]=NULL;
                node->Num+=1;
                node->NextNode[node->Num] = p;
                Main_menutree(node);
               }
          if(j==2){TreeNode *p;
                    p = (TreeNode *)malloc(sizeof(TreeNode));
                    p->Parent = 0;
                    printf("\t\t\t��������:");
                    scanf("%s",p->Name);
                    getchar();
                    p->Num = node->Num;
                    node->NextNode[0]=p;
                    Main_menutree(node);
               }
          if(j==3){Main_menutree(node);}
          }
     }
}




void Main_menutree(TreeNode *Tree)//���˵�ѡ��
{
	char Name[20];
	TreeNode *NewNode;
	NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	while (1)
	{    system("cls");
		printf("\t\t\t-------# ����ѡ��-------\n");
		printf("\t\t\t-------1 ������Ϣ-------\n");
		printf("\t\t\t-------2 ���ҳ�Ա-------\n");
		printf("\t\t\t-------3 ���ӳ�Ա-------\n");
		printf("\t\t\t-------4 ������Ϣ-------\n");
		printf("\t\t\t-------5 �޸���Ϣ-------\n");
		printf("\t\t\t-------6 �˳�����-------\n");
		printf("\t\t\t��ѡ��Ҫִ�еĲ���: ");
		int choice ;
		scanf("%d",&choice);
		switch (choice)
		{
		case 1:
			printf("����������:");
			scanf("%s", Tree->Name);
			printf("�������Ա�(ŮG,��B):");
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
				printf("����ͼδ�������Ƚ�����\n");
				getchar();
				system("pause");
			system("cls");
				break;
			}
			printf("����������Ҫ���ҵ�������\n");
			scanf("%s", &Name);
			Outputm(Search(Tree,Name));
			getchar();
			system("pause");
			break;

		case 3:
			if (strcmp(Tree->Name, "0") == 0)
			{
				printf("����ͼδ�������Ƚ�����\n");
				getchar();
				system("pause");
				break;
			}
			printf("����������Ҫ���ӵ�������\n");
			scanf("%s", &Name);
			input_T(Search_c(Tree,Name));
			system("pause");
			break;
			//���Ӻ���



		case 4:
			if (strcmp(Tree->Name, "0") == 0)
			{
				printf("����ͼδ�������Ƚ�����\n");
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
				printf("����ͼδ�������Ƚ�����\n");
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

void SubMenu_1(TreeNode *Tnode)//�޸��Ӳ˵�
{
	while (1)
	{
		printf("-------# ����ѡ��-------\n");
		printf("-------1 �޸ĸ�����Ϣ-------\n");
		printf("-------2 �޸ĸ�ĸ��Ϣ-------\n");
		printf("-------3 �޸�������Ϣ-------\n");
		printf("-------4 �޸���Ů��Ϣ-------\n");
		printf("-------5 �޸���ż��Ϣ-------\n");
		printf("-------6 �������˵�-------\n");
		printf("-------7 �˳�����-------\n");
		printf("��ѡ��Ҫִ�еĲ���: ");
		int choice ;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			printf("��ǰ������Ϣ���£�\n");
			printf("������%s\t�Ա�", Tnode->Name);
			if (Tnode->Sex == 'G')
			{
				printf("Ů\n");
			}
			else
			{
				printf("��\n");
			}
			printf("��������Ҫ�޸ĵ�������");
			scanf("%s", Tnode->Name);
			getchar();
			printf("��������Ҫ�޸ĵ��Ա�(��BŮG)��");
			scanf("%c", &(Tnode->Sex));
			break;
		}
		case 2:
		{
			if (Tnode->Parent == NULL)
			{
				printf("����Ϣ��\n");
				return;
			}
			else

			printf("��ǰ��ĸ��Ϣ����:\n");
			printf("����������%s\n", Tnode->Parent->Name);
			printf("ĸ��������%s\n", Tnode->Parent->NextNode[0]->Name);
			printf("�������޸���Ϣ:\n");
			printf("�޸ĵĸ���������");
			scanf("%s", Tnode->Parent->Name);
			getchar();
			printf("�޸ĵ�ĸ��������");
			scanf("%s", Tnode->Parent->NextNode[0]->Name);
			getchar();
			break;
		}
		case 3:
		{
			if (Tnode->Parent == NULL)
			{
				printf("����Ϣ��\n");
				return;
			}
			if (Tnode->Parent->Num == 1)
			{
				printf("����Ϣ��\n");
				return;
			}
			printf("��ǰ�ֵܽ�����Ϣ����:\n");
			for (int i = 1; i <= Tnode->Parent->Num; i++)
			{
				if (strcmp(Tnode->Name, Tnode->Parent->NextNode[i]->Name) != 0)
				{
					printf("�ֵܽ��õ�%d����������%s\n�Ա�", i, Tnode->Parent->NextNode[i]->Name);
					if (Tnode->Parent->NextNode[i]->Sex == 'G')
					{
						printf("Ů\n");
					}
					else
					{
						printf("��\n");
					}
				}
			}

			printf("�������޸���Ϣ��\n");
			for (int i = 1; i <= Tnode->Parent->Num; i++)
			{
				if (strcmp(Tnode->Name, Tnode->Parent->NextNode[i]->Name) != 0)
				{
					printf("�ֵܽ��õ�%d����������", i);
					scanf("%s", Tnode->Parent->NextNode[i]->Name);
					getchar();
					printf("�Ա�");
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
				printf("����Ϣ��");
				getchar();
				return;
			}
			printf("��ǰ��Ů����Ϣ���£�\n");
			for (int i = 1; i <= Tnode->Num; i++)
			{
				printf("��%d����Ů��������%s\t�Ա�", i, Tnode->NextNode[i]->Name);
				if (Tnode->NextNode[i]->Sex == 'G')
				{
					printf("Ů\n");
				}
				else
				{
					printf("��\n");
				}
			}
			printf("�������޸���Ϣ��\n");
			for (int i = 1; i <= Tnode->Num; i++)
			{
				printf("��%d����Ů��������", i);
				scanf("%s", Tnode->NextNode[i]->Name);
				getchar();
				printf("�Ա�");
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
				printf("�ó�Ա������ż����Ů��\n");
				return;
			}
			if (Tnode->NextNode[0]->Sex == 'G')
			{
				printf("�����ǣ�%s\n", Tnode->NextNode[0]->Name);
			}
			else
			{
				printf("�ɷ��ǣ�%s\n", Tnode->NextNode[0]->Name);
			}
			fflush(stdin);
			printf("�������޸���Ϣ��\n");
			printf("������");
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



