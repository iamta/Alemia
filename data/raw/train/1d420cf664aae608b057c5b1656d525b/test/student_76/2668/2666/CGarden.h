#pragma once
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "CPoint.h"
#include <vector>
#include "CTimeVerifier.h"
#include "CPlayer.h"
#include "IResursa.h"
#define Col 10
#define Lines 6
using namespace UserInterface;
class CGarden
{
private:
	CPlayer* Player;
	CTimeVerifier* TimeVer;
	ConsoleInput* conIn;
	ConsoleOutput* conOut;
	static CGarden* instance;
	std::vector<IResursa*>Suns;
	std::vector<CPoint*>SunPosiblePositions;
	std::vector<CPoint*>GroundPositions;
	void Draw();
	CGarden() { ; };
	~CGarden() { ; };
public:
	std::vector<CPoint*>& GetGroundPosition() { return GroundPositions; };
	std::vector<CPoint*> GetZombieStartPos();
	static CGarden& GetInstance(CPlayer* Player);
	static void RemoveInstance();
	void SpamSuns();
	bool VerifiSun(CPoint P);
};

