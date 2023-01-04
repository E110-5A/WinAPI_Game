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
	// �� ��ư
	SelectBtn,		// title
	OptionBtn,		// title
	QuitBtn,		// title

	PlayBtn,		// select

	// �ΰ���
	PlayerInfo,		
	HpBar,			
	ExpBar,			
	Z,				
	X,				
	C,				
	V,

	Difficulty,		// ���̵�
	DifficultyBar,


	ItemInventory,	// �ΰ��� HUD
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

#define TILE_SIZE	32			// ���μ��� ũ��
#define TILE_SCALE	2			// �̹��� ũ��
#define TILE_LINE_X 12			// ��Ʋ�� ���� ����
#define TILE_LINE_Y 6			// ��Ʋ�� ���� ����

#define GRID_SIZE 64			// Ÿ�� ũ��


// Component enum
#define _COLLIDER_LAYER 25		// �浹ü ����
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
	BackGroundImage,			//			// ���� �ٴڿ� �򸮴� �̹���
	Tile,						//			// Ÿ�Ϸ� �����ϴ� ��� ������Ʈ
	BackgroundMap,
	BGObj,						//			// �̹��� �ܿ� ������Ʈ�� �ʿ��� ��� ������Ʈ
									
	Teleporter,
	Propellant,					//			// ����, ����ü
	Chest,
	Platform,					//			// ��, �ٴ�
	Ladder,						//			// ��ٸ�
	Item,						//			// 

	Head,						//			// Creature �Ӹ��浹
	Foot,						//			// Creature �ٴ��浹
	Player,						//			// 
	Projectile,					//			// 
	Monster,					//			// �÷��̾� ����ü�� ���ؼ��� ���ظ� ����
	Monster_Projectile,
	DamageObject,				//			// ��Ϲٴ�, ���� ����ü ��

	UI = _COLLIDER_LAYER - 1,	//	
	End = _COLLIDER_LAYER,		//	
};
// 1 ��׶��� ���̾� ������ ��

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
	Death,		// ��?
};
enum class eProjectileType
{
	DoubleTab,			// 1�� ���
	FMJ,				// 2�� ���
	TacticalDive,		// 3�� ���
	SuppresiveFire,		// 4�� ���

	End,
};

enum class eBossAttackType
{
	A,			// 1�� ���
	B,				// 2�� ���
	
	End,
};

enum class eStagger
{
	Light,		// ���� ���� �˹�
	Nomal,		// ���� ���� �˹�
	Heave,		// ���� ���� ��������
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
	Glasses,		// ġ��Ÿ ����
	Syringe,		// ���ݼӵ� ����
	Hoof,			// �̵��ӵ� ����
	Tooth,			// óġ�� ü�� ȸ��
	Root,			// �ִ� ä�� ����
	// Uncommon
	TimeKeeper = 5,	// ġ����� ���� ��, �ð��� ����
	Wisp,			// óġ�� ����
	MissileMk1,		// ����Ȯ���� ����ü ����
	Seed,			// Ÿ�ݸ��� ȸ��
	Feather,		// ���� 1ȸ �߰�
	// Rare
	MissileMk2 = 10,// ������ �� ���� ����ü ����
	Behemoth,		// ��� ������ ������
	Ring,			// ġ��Ÿ ����, ġ��Ÿ�� ��ٿ� ����
	Scepter,		// 4��° ��ų ��ȭ
	// Active
	Key	= 15,		// ȭ�鿡 ���̴� ���ڸ� ����
	Fruit,			// ��� ȸ��
	Watch,			// �ð��� ����
	End,
};