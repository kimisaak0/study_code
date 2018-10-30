//예제임 분석 및 공부 필요.


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
			//GUID를 문자열로 변환 할 수 없다.(사용 가능한 메모리가 충분하지 않은 결과).
		}
	}
	else
	{
		//GUID를 만들 수 없다.
	}

	return 0;
}