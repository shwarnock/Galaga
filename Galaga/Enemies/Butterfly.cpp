#include "Butterfly.h"
#include "../../Physics/BoxCollider.h"
#include "../../Managers/AudioManager.h"
#include "../../Physics/CircleCollider.h"

vector<vector<Vector2>> Butterfly::sDivePaths;

void Butterfly::CreateDivePaths()
{
	int currentPath = 0;
	BezierPath* path = new BezierPath();
	
	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -45.0f), Vector2(-60.0f, -45.0f), Vector2(-60.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(-60.0f, 0.0f), Vector2(-60.0f, 80.0f), Vector2(200.0f, 125.0f), Vector2(200.0f, 200.0f) }, 15);
	path->AddCurve({ Vector2(200.0f, 200.0f), Vector2(200.0f, 275.0f), Vector2(175.0f, 250.0f), Vector2(175.0f, 325.0f) }, 15);
	path->AddCurve({ Vector2(175.0f, 325.0f), Vector2(175.0f, 425.0f), Vector2(375.0f, 425.0f), Vector2(375.0f, 525.0f) }, 15);
	path->AddCurve({ Vector2(375.0f, 525.0f), Vector2(375.0f, 575.0f), Vector2(300.0f, 625.0f), Vector2(300.0f, 775.0f) }, 15);

	sDivePaths.push_back(vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 1;
	path = new BezierPath();

	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -45.0f), Vector2(60.0f, -45.0f), Vector2(60.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(60.0f, 0.0f), Vector2(60.0f, 80.0f), Vector2(-200.0f, 125.0f), Vector2(-200.0f, 200.0f) }, 15);
	path->AddCurve({ Vector2(-200.0f, 200.0f), Vector2(-200.0f, 275.0f), Vector2(-175.0f, 250.0f), Vector2(-175.0f, 325.0f) }, 15);
	path->AddCurve({ Vector2(-175.0f, 325.0f), Vector2(-175.0f, 425.0f), Vector2(-375.0f, 425.0f), Vector2(-375.0f, 525.0f) }, 15);
	path->AddCurve({ Vector2(-375.0f, 525.0f), Vector2(-375.0f, 575.0f), Vector2(-300.0f, 625.0f), Vector2(-300.0f, 775.0f) }, 15);

	sDivePaths.push_back(vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 2;
	path = new BezierPath();

	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(-90.0f, -60.0f), Vector2(-90.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(-90.0f, 0.0f), Vector2(-90.0f, 60.0f), Vector2(-100.0f, 272.0f), Vector2(-15.0f, 275.0f) }, 15);
	path->AddCurve({ Vector2(-15.0f, 275.0f), Vector2(85.0f, 275.0f), Vector2(85.0f, 125.0f), Vector2(-15.0f, 125.0f) }, 15);
	path->AddCurve({ Vector2(-15.0f, 125.0f), Vector2(-175.0f, 125.0f), Vector2(0.0f, 450.0f), Vector2(120.0f, 450.0f) }, 25);
	path->AddCurve({ Vector2(120.0f, 450.0f), Vector2(160.0f, 450.0f), Vector2(200.0f, 500.0f), Vector2(200.0f, 550.0f) }, 15);
	path->AddCurve({ Vector2(200.0f, 550.0f), Vector2(200.0f, 540.0f), Vector2(200.0f, 810.0f), Vector2(200.0f, 800.0f) }, 1);

	sDivePaths.push_back(vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 3;
	path = new BezierPath();

	path->AddCurve({ Vector2(0.0f, 0.0f), Vector2(0.0f, -60.0f), Vector2(90.0f, -60.0f), Vector2(90.0f, 0.0f) }, 15);
	path->AddCurve({ Vector2(90.0f, 0.0f), Vector2(90.0f, 60.0f), Vector2(100.0f, 272.0f), Vector2(15.0f, 275.0f) }, 15);
	path->AddCurve({ Vector2(15.0f, 275.0f), Vector2(-85.0f, 275.0f), Vector2(-85.0f, 125.0f), Vector2(15.0f, 125.0f) }, 15);
	path->AddCurve({ Vector2(15.0f, 125.0f), Vector2(175.0f, 125.0f), Vector2(0.0f, 450.0f), Vector2(-120.0f, 450.0f) }, 25);
	path->AddCurve({ Vector2(-120.0f, 450.0f), Vector2(-160.0f, 450.0f), Vector2(-200.0f, 500.0f), Vector2(-200.0f, 550.0f) }, 15);
	path->AddCurve({ Vector2(-200.0f, 550.0f), Vector2(-200.0f, 540.0f), Vector2(-200.0f, 810.0f), Vector2(-200.0f, 800.0f) }, 1);

	sDivePaths.push_back(vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;
}

Butterfly::Butterfly(int index, int path, bool challengeStage)
	: Enemy(index, path, challengeStage)
{
	mTextures[0] = new Texture("Butterfly.png");
	mTextures[0]->Parent(this);
	mTextures[0]->Pos(VEC2_ZERO);

	mTextures[1] = new Texture("Butterfly2.png");
	mTextures[1]->Parent(this);
	mTextures[1]->Pos(VEC2_ZERO);

	mType = butterfly;

	AddCollider(new BoxCollider(mTextures[1]->ScaledDimensions()));
}

Butterfly::~Butterfly()
{

}

Vector2 Butterfly::LocalFormationPosition()
{
	Vector2 retVal;
	
	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 4)) * pow(-1, mIndex % 2 + 1);
	retVal.y = sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Butterfly::HandleDiveState()
{
	int currentPath = mIndex % 2;

	if (mEscort)
		currentPath += 2;

	if (mCurrentWaypoint < sDivePaths[currentPath].size())
	{
		Vector2 wayPointPos = mDiveStartPosition + sDivePaths[currentPath][mCurrentWaypoint];

		Vector2 dist = wayPointPos - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((wayPointPos - Pos()).MagnitudeSqr() < EPSILON)
			++mCurrentWaypoint;

		if (mCurrentWaypoint == sDivePaths[currentPath].size())
			Pos(Vector2(WorldFormationPosition().x, 20.0f));
	} else
	{
		Vector2 dist = WorldFormationPosition() - Pos();
		Translate(dist.Normalized() * mTimer->DeltaTime() * mSpeed, world);

		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON)
			JoinFormation();
	}
}

void Butterfly::RenderDiveState()
{
	mTextures[0]->Render();

	int currentPath = mIndex % 2;
	
	if (mEscort)
		currentPath += 2;

	for (int i = 0; i < sDivePaths[currentPath].size() - 1; ++i)
	{
		Graphics::Instance()->DrawLine(mDiveStartPosition.x + sDivePaths[currentPath][i].x, mDiveStartPosition.y + sDivePaths[currentPath][i].y,
			mDiveStartPosition.x + sDivePaths[currentPath][i + 1].x, mDiveStartPosition.y + sDivePaths[currentPath][i + 1].y);
	}
}

void Butterfly::Dive(int type)
{
	mEscort = type != 0;

	Enemy::Dive();
}

void Butterfly::Hit(PhysicsEntity* other)
{
	AudioManager::Instance()->PlaySFX("galaga_destroyed.wav", 0, 3);
	sPlayer->AddScore(mCurrentState == Enemy::formation ? 80 : 160);
	Enemy::Hit(other);
}