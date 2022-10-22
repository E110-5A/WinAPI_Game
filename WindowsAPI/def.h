#pragma once

#define KEY_PRESSE(KEY) js::jsInput::GetKeyState(KEY) == js::eKeyState::PRESSED
#define KEY_DOWN(KEY) js::jsInput::GetKeyState(KEY) == js::eKeyState::DOWN
#define KEY_UP(KEY) js::jsInput::GetKeyState(KEY) == js::eKeyState::UP


enum class eSceneType
{
	LOGO,
	TITLE,
	PLAY,
	END,
};