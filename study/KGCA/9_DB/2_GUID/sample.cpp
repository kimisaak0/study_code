//������ �м� �� ���� �ʿ�.


#include "Utils.h"

int main()
{
	// Create a new uuid
	UUID uuid;
	RPC_STATUS ret_val = ::UuidCreate(&uuid);

	if (ret_val == RPC_S_OK)
	{
		// convert UUID to LPWSTR
		WCHAR* wszUuid = NULL;
		::UuidToStringW(&uuid, (RPC_WSTR*)&wszUuid);
		if (wszUuid != NULL)
		{
			// free up the allocated string
			::RpcStringFreeW((RPC_WSTR*)&wszUuid);
			wszUuid = NULL;

			std::cout << uuid.Data1;
		}
		else
		{
			//GUID�� ���ڿ��� ��ȯ �� �� ����.(��� ������ �޸𸮰� ������� ���� ���).
		}
	}
	else
	{
		//GUID�� ���� �� ����.
	}

	return 0;
}