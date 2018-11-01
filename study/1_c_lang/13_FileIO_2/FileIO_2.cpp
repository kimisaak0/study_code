#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//�ڱ� ���� ����ü (���Ḯ��Ʈ), ����ü
typedef struct TNodeData
{
	char		m_strName[20];
	int			m_iAge;
	char		m_strAddress[50];
	TNodeData*	pNext;
}TNode;

char*	GetName(TNode* pNode, int iIndex) { return pNode[iIndex].m_strName; }
int		GetAge(TNode* pNode, int iIndex) { return pNode[iIndex].m_iAge; }
char*	GetAddress(TNode* pNode, int iIndex) { return pNode[iIndex].m_strAddress; }

//��ϴ��� �����
int main()
{
	FILE*	fp_src;
	FILE*	fp_dest;
	char	buff[4096];
	size_t	n_size;

	fopen_s(&fp_src, "FileIO_2.cpp", "r");
	fopen_s(&fp_dest, "FileIO_2.bak", "w");

	while (0 < (n_size = fread(buff, 1, 4096, fp_src))) {
		fwrite(buff, 1, n_size, fp_dest);
	}

	fclose(fp_src);
	fclose(fp_dest);

	//�ؽ�Ʈ ���� ��ϴ��� ���
	TNode List[3] = {
		{ "ȫ�浿", 24, "����" },
		{ "������", 44, "����" },
		{ "���׳�", 54, "�λ�" }
	};

	fopen_s(&fp_dest, "BolckRead.dat", "w");
	fwrite(List, 1, sizeof(TNode) * 3, fp_dest);
	fclose(fp_dest);

	//�ؽ�Ʈ ���� ��ϴ��� �Է�
	TNode Load[3];
	fopen_s(&fp_src, "BolckRead.dat", "r");
	fread(Load, 1, sizeof(TNode) * 3, fp_src);
	fclose(fp_src);

	//�ؽ�Ʈ ���� ���� ���
	fopen_s(&fp_dest, "LineWrite.txt", "wt");
	for (int iCnt = 0; iCnt < 3; iCnt++) {
		fprintf(fp_dest, "\n%s %d %s",
			GetName(List, iCnt),
			GetAge(List, iCnt),
			GetAddress(List, iCnt));
	}
	fclose(fp_dest);

	//�ؽ�Ʈ ���� ���� �Է�
	TNode	LineBuffer[3];
	char	pBuffer[256];
	int		iCount = 0;

	fopen_s(&fp_src, "LineWrite.txt", "rt");
	fgets(pBuffer, 256, fp_src);
	while (!feof(fp_src)) {
		fgets(pBuffer, 256, fp_src);
		sscanf_s(pBuffer, "%s %d %s", 
			LineBuffer[iCount].m_strName, 20,
			&LineBuffer[iCount].m_iAge,
			LineBuffer[iCount].m_strAddress, 50);
		iCount++;
	}
	fclose(fp_src);

	return 0;
}