#include <stdio.h>

union TData
{
	char a;
	int b;
	double c;
};

//��Ʈ�ʵ� ����ü
struct TBool
{
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char c : 1;
	unsigned char d : 1;
	unsigned char e : 1;
	unsigned char f : 1;
	unsigned char g : 1;
	unsigned char h : 1;
};

//��Ʈ�ʵ屸��ü�� ����ü
typedef struct {
	union {
		struct {
			unsigned long Zone : 28;
			unsigned long Level : 4;
		};
		unsigned long Value;
	};
} DATA, *PDATA;

typedef struct in_addr {
	union {
		struct { unsigned char s_b1, s_b2, s_b3, s_b4; } S_un_b;
		struct { unsigned short s_w1, s_w2; } S_un_w;
		unsigned long S_addr;
	} S_un;

#define s_addr	S_un.S_addr

#define s_inpno	S_un.S_un_b.s_b4
#define s_lh	S_un.S_un_b.s_b3
#define s_host	S_un.S_un_b.s_b2
#define s_net	S_un.S_un_b.s_b1

#define s_imp	S_un.S_un_w.s_w2

} IN_ADDR, *PIN_ADDR;

struct TData2
{
	int		f;
	short	d;
	short	c;

	char	a;
	char	u;
	short	s;
};



void main()
{
	TData2 data1;
	int iSize = sizeof(data1);

	TBool BData;
	iSize = sizeof(BData);
	BData.a = 0;
	BData.b = 1;
	BData.c = 2;
	BData.d = 3;
	printf("%d %d %d %d \n\n", 
		BData.a, BData.b, 
		BData.c, BData.d);
	//�޸𸮸� ���� ���鼭 �� ���

	TData data;
	iSize = sizeof(data);
	data.a = 65;
	printf("%c\n", data.a);
	data.b = 100;
	printf("%d\n", data.b);
	data.c = 3.14;
	printf("%f\n\n", data.c);

	
	//������̶� ����Ʈ�� ����Ǵ� ������ ���Ѵ�.

	//����, AMD cpu�� Little-Endian���� ����ȴ�.
	//�����ʺ��� �������� ����Ǵ� �������
	//�ֻ��� �����Ͱ� ���� ���� �ּҿ� ����Ǵ� ����̴�.

	//�ݴ�� Big-Endian�̶� �ϸ� (unix) ��Ʈ��ũ���� ���ȴ�.
	//���ʺ��� ���������� ����Ǵ� �������
	//�ֻ��� �����Ͱ� ���� ���� �ּҿ� ����Ǵ� ����̴�.
	
	//���ǻ��� : �ƽ�Ű �ڵ�� ���� ���� ����Ʈ ���� �����ʹ� ����� ���¿� ���� ������ ����.

	IN_ADDR addr;

	addr.S_un.S_addr = 0x6601a8c0; // 192(c0).168(a8).1(01).102(66)
	printf("%d ", addr.S_un.S_un_b.s_b1);
	printf("%d ", addr.S_un.S_un_b.s_b2);
	printf("%d ", addr.S_un.S_un_b.s_b3);
	printf("%d\n\n", addr.S_un.S_un_b.s_b4);

	//����Ʈ�� �����ؼ� ����
	addr.S_un.S_un_b.s_b2 = 0xa9;
	printf("%x\n", addr.S_un.S_addr);
	printf("%d ", addr.S_un.S_un_b.s_b1);
	printf("%d ", addr.S_un.S_un_b.s_b2);
	printf("%d ", addr.S_un.S_un_b.s_b3);
	printf("%d\n\n", addr.S_un.S_un_b.s_b4);

	//��Ʈ �ʵ� ����ü�� ����ϴ� ����ü
	DATA dt;
	dt.Value = 0x55667788;
	printf("%d", dt.Zone);
	printf(" %d ", dt.Level);
}