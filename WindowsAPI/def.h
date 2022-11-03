#pragma once

#define KEY_PRESSE(KEY) js::jsInput::GetKeyState(KEY) == js::eKeyState::PRESSED
#define KEY_DOWN(KEY) js::jsInput::GetKeyState(KEY) == js::eKeyState::DOWN
#define KEY_UP(KEY) js::jsInput::GetKeyState(KEY) == js::eKeyState::UP


enum class eSceneType
{
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
	Animator,
	Collider,
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


	UI = _COLLIDER_LAYER - 1,
	End = _COLLIDER_LAYER,
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