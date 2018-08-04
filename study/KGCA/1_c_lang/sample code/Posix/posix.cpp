//open.cpp : �ܼ� ���� ���α׷��� �������� �����մϴ�.

//POSIX(������)�� �̽� ���� � ü�� �������̽�(portable operating system interface)�� ���ڷ�
//���� �ٸ� UNIX OS�� ���� API�� �����Ͽ� 
//�̽ļ��� ���� ���н� ���� ���α׷��� �����ϱ� ���� �������� IEEE�� å���� ���ø����̼� �������̽� �԰��̴�.

#include <stdio.h>
#include <io.h> //<fcntl.h> <sys/types.h> <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wchar.h> // _wopen io.h or wchar.h

int main(int argc, char* argv[])
{
	int fd1, fd2;
	char buf[BUFSIZ];
	int n;

	if (argc != 3) {
		fprintf(stderr, "USAGE : %s SourceFile ObjectFile\n", argv[0]);
		return 1;
	}

	_sopen_s(&fd1, argv[1], O_RDONLY | O_BINARY, _SH_DENYNO, S_IREAD | S_IWRITE);

	if (fd1 < 0) {
		fprintf(stderr, "Error : cannot open %s\n", argv[1]);
		return 2;
	}

	_sopen_s(&fd2, argv[2], O_WRONLY | O_TRUNC | O_CREAT | O_BINARY, _SH_DENYNO ,S_IREAD | S_IWRITE);

	if (fd2 < 0) {
		fprintf(stderr, "Error : cannot create %s\n", argv[2]);
		return 2;
	}

	printf("FileCopy %s to %s\n\n", argv[1], argv[2]);
	while ((n = _read(fd1, buf, BUFSIZ)) > 0) {
		if (_write(fd2, buf, n) != n) {
			//������ ȭ�� ����¿��� read�� write �ۿ� ����.
			//���� ���� �����͸� ��¿��� ��������, ������ �Ǽ����� ����ϰ��� �� ������ �̸� ASCII �ڵ� ���·�,
			//�� ���� ���·� ��ȯ�� ���� ����ؾ� �ϱ� ������
			//�׷��� ��쿡�� ������� ����� �Լ��� ����ϴ� ���� �� ���ϴ�.
			fprintf(stderr, "Error in writing %s \n", argv[2]);
			return 4;
		}
	}

	if (n < 0) {
		fprintf(stderr, "Error in reading %s\n", argv[1]);
	}

	_close(fd1);
	_close(fd2);
}