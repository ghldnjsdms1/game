#include "WndDefine.h"
#include "GameManager.h"



// �̰��� main �� ������
// ��Ʈ������Ʈ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd) {

	GameManager::GetGameManager()->Loop(hInstance, nShowCmd);

	return 0;


}
