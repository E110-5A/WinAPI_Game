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
	Title,
	Select,
	Play,
	Option,
	End,
};


// UI enum
enum class eUIType
{
	TEST,
	SelectBtn,		// title
	OptionBtn,		// title
	QuitBtn,		// title

	PlayBtn,		// select

	PLAYER_INFO,	// �ΰ��� HUD
	ITEM_SELECT,	// �ΰ��� HUD
	OPTION,			// 

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

#define GRID_SIZE 64


// Component enum
#define _COLLIDER_LAYER 16		// �浹ü ����
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
	Default,					//	 1		// None
	BackGroundImage,			//	 2		// �̹����� �����ϴ� ��� ������Ʈ
	Tile,						//	 3		// Ÿ�Ϸ� �����ϴ� ��� ������Ʈ
	BGObj,						//	 4		// �̹��� �ܿ� ������Ʈ�� �ʿ��� ��� ������Ʈ
	EventObject,				//	 5		// ��Ÿ �浹�� �۵��ϴ� �̺�Ʈ ������Ʈ
	Chest,						//	 6		// �ڿ��� �Ҹ��� �����۰� ��ȯ������ �̺�Ʈ ������Ʈ
	Item,						//	 7		// �÷��̾ ���� PickUp ������ �̺�Ʈ ������Ʈ
	Player,						//	 8		// ������ �� �浹�� ���� ����
	Player_Projectile,			//	 9		// ���Ϳ��Ը� ���ظ� ��
	Monster,					//	10		// �÷��̾� ����ü�� ���ؼ��� ���ظ� ����

	Platform,					//	11		// �� ������ �ϴ� ������Ʈ (�񰡽�)
	GroundCheck,				//	12		// �߷� ó���� ������Ʈ (�񰡽�)
	DamagingObj,				//	13		// ��Ϲٴ�, ���� ����ü ��

	UI = _COLLIDER_LAYER - 1,	//	14
	End = _COLLIDER_LAYER,		//	15
};

// 1 ��׶��� ���̾� ������ ��
// 2 Chest�� EventObj �� ������ ��

// Object enum
enum class ePlayerState
{
	Idle,		// �ƹ� ���·� ��ȯ ����
	Move,		// �ƹ� ���·� ��ȯ ����
	Jump,		// �ƹ� ���·� ��ȯ ����
	Climb,		// ������ ��밡��
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

enum class eStagger
{
	Light,		// ���� ���� �˹�
	Nomal,		// ���� ���� �˹�
	Heave,		// ���� ���� ��������
};

#define PLAYER_PROJECTILE_POOL 40

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
	TimeKeeper = 5,		// ġ����� ���� ��, �ð��� ����
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