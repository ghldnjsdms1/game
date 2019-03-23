#include "WndDefine.h"
#include "GameManager.h"



// 이곳은 main 과 같은곳
// 엔트리포인트
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd) {

	GameManager::GetGameManager()->Loop(hInstance, nShowCmd);

	return 0;


}
