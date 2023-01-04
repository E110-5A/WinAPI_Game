#pragma once

// Application enum
#define Window_Width    1280
#define Window_Height   720
enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};
enum class eBrushColor
{
	Transparent,
	Black,
	Gray,	// 167 0 67
	White,
	End,
};
enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
	End,
};
#define KEY_PRESSE(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::PRESSED
#define KEY_DOWN(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::DOWN
#define KEY_UP(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::UP

// Scene enum
enum class eSceneType
{
	MapTool,
	Test,
	Test2,
	Title,
	Select,
	STGA,
	STGB,
	STGC,
	Option,
	End,
};

// UI enum
enum class eUIType
{
	TEST,
	// 씬 버튼
	SelectBtn,		// title
	OptionBtn,		// title
	QuitBtn,		// title

	PlayBtn,		// select

	// 인게임
	PlayerInfo,		
	HpBar,			
	ExpBar,			
	Z,				
	X,				
	C,				
	V,

	Difficulty,		// 난이도
	DifficultyBar,


	ItemInventory,	// 인게임 HUD
	Option,			// 

	END,
};
enum class eBtnType
{
	GoToSelectScene,
	GoToOption,
	GoToPlayScene,
	GoToTitleScene,
	End,
};


// Tool enum
union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};
	UINT64 ID;
};
typedef ColliderID TileID;

#define TILE_SIZE	32			// 가로세로 크기
#define TILE_SCALE	2			// 이미지 크기
#define TILE_LINE_X 12			// 아틀라스 가로 개수
#define TILE_LINE_Y 6			// 아틀라스 세로 개수

#define GRID_SIZE 64			// 타일 크기


// Component enum
#define _COLLIDER_LAYER 25		// 충돌체 유형
enum class eComponentType
{
	Rigidbody,
	Collider,
	Animator,
	Sound,
	End,
};
enum class eColliderLayer
{
	Default,					//		//	// None
	BackGroundImage,			//			// 제일 바닥에 깔리는 이미지
	Tile,						//			// 타일로 존재하는 배경 오브젝트
	BackgroundMap,
	BGObj,						//			// 이미지 외에 컴포넌트가 필요한 배경 오브젝트
									
	Teleporter,
	Propellant,					//			// 상자, 추진체
	Chest,
	Platform,					//			// 벽, 바닥
	Ladder,						//			// 사다리
	Item,						//			// 

	Head,						//			// Creature 머리충돌
	Foot,						//			// Creature 바닥충돌
	Player,						//			// 
	Projectile,					//			// 
	Monster,					//			// 플레이어 투사체에 의해서만 피해를 입음
	Monster_Projectile,
	DamageObject,				//			// 용암바닥, 몬스터 투사체 등

	UI = _COLLIDER_LAYER - 1,	//	
	End = _COLLIDER_LAYER,		//	
};
// 1 백그라운드 레이어 통일할 것

// Object enum
enum class ePlayerState
{
	Idle,		
	Move,		
	Jump,		
	Climb,		
	DoubleTab,
	FMJ,
	TacticalDive,		
	SupressiveFire,
	Death,		// 끝?
};
enum class eProjectileType
{
	DoubleTab,			// 1번 기술
	FMJ,				// 2번 기술
	TacticalDive,		// 3번 기술
	SuppresiveFire,		// 4번 기술

	End,
};

enum class eBossAttackType
{
	A,			// 1번 기술
	B,				// 2번 기술
	
	End,
};

enum class eStagger
{
	Light,		// 소형 몬스터 넉백
	Nomal,		// 중형 몬스터 넉백
	Heave,		// 보스 제외 기절유발
};

#define PLAYER_PROJECTILE_POOL	40
#define MONSTER_POOL			45
#define CHEST_POOL				4
// item enum
enum class eChestType
{
	Small,
	Large,
	Golden,
};

#define ITEM_SIZE 34
enum class eItemType
{
	Common,
	Uncommon,
	Rare,
	Active,
};
enum class eItemList
{
	// Common
	Glasses,		// 치명타 증가
	Syringe,		// 공격속도 증가
	Hoof,			// 이동속도 증가
	Tooth,			// 처치시 체력 회복
	Root,			// 최대 채력 증가
	// Uncommon
	TimeKeeper = 5,	// 치명상을 입을 때, 시간을 멈춤
	Wisp,			// 처치시 폭발
	MissileMk1,		// 일정확률로 투사체 사출
	Seed,			// 타격마다 회복
	Feather,		// 점프 1회 추가
	// Rare
	MissileMk2 = 10,// 더많이 더 강한 투사체 사출
	Behemoth,		// 모든 공격이 폭발함
	Ring,			// 치명타 증가, 치명타시 쿨다운 감소
	Scepter,		// 4번째 스킬 강화
	// Active
	Key	= 15,		// 화면에 보이는 상자를 열음
	Fruit,			// 즉시 회복
	Watch,			// 시간을 멈춤
	End,
};