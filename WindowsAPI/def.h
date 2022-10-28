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