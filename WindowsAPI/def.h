#pragma once

#define Window_Width    1280
#define Window_Height   720


#define KEY_PRESSE(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::PRESSED
#define KEY_DOWN(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::DOWN
#define KEY_UP(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::UP


enum class eSceneType
{
	Tool,
	Test,
	Title,
	Select,
	Play,
	Option,
	End,
};
enum class eUIType
{
	TEST,
	SelectBtn,		// title
	OptionBtn,		// title
	QuitBtn,		// title

	PlayBtn,		// select

	PLAYER_INFO,	// 인게임 HUD
	ITEM_SELECT,	// 인게임 HUD
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

enum class eComponentType
{
	Rigidbody,
	Collider,
	Animator,
	Sound,
	End,
};

#define _COLLIDER_LAYER 16
enum class eColliderLayer
{
	Default,					//	0
	BackGround,					//	1
	Tile,						//	2
	BGObj,						//	3
	Player,						//	4
	Player_Projectile,			//	5
	Monster,					//	6
	Monster_Projectile,			//	7

	Ground,						//	13
	UI = _COLLIDER_LAYER - 1,	//	14
	End = _COLLIDER_LAYER,		//	15
};

enum class eState
{
	Idle,		// 아무 상태로 변환 가능
	Move,		// 아무 상태로 변환 가능
	Jump,		// 아무 상태로 변환 가능
	Climb,
	Attack,
	Dodge,
	Die,
};

enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
	End,
};

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

#define TILE_SIZE	32
#define TILE_SCALE	2
#define TILE_LINE_X 12
#define TILE_LINE_Y 6