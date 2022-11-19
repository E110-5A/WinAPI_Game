#pragma once

#define KEY_PRESSE(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::PRESSED
#define KEY_DOWN(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::DOWN
#define KEY_UP(KEY) js::Input::GetKeyState(KEY) == js::eKeyState::UP


enum class eSceneType
{
	Tool,
	Test,
	Title,
	Play,
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
	Default,
	BackGround,
	Tile,

	Player,
	Player_Projectile,
	Monster,
	Monster_Projectile,

	Ground,
	UI = _COLLIDER_LAYER - 1,
	End = _COLLIDER_LAYER,
};

enum class eUIType
{
	HP,
	MP,
	SHOP,
	INVENTORY,
	OPTION,


	END,
	
};

enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
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