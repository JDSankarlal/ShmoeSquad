#pragma once
#include <Windows.h>
#include <unordered_map>

/*----User defined classes----*/
class keyinput
{
private:
	std::unordered_map<int, bool>enter;

public:
	/*
	bool stroke(int key);
	* key - The key which is pressed. You can either
	use VK_KEYS (i.e. VK_RIGHT) or characters
	(Note: characters must be in uppercase) to be
	checked if key is pressed and then released
	*/
	bool stroke(int key)
	{
		enter.insert(std::pair<int, bool>(key, false));

		if (GetAsyncKeyState(key))
			enter[key] = true;
		else if (enter[key] && !GetAsyncKeyState(key))
		{
			enter[key] = false;
			return true;
		}
		return false;
	}

	/*
	bool press(int key)
	* key - The key which is pressed. You can either
	use VK_KEYS (i.e. VK_RIGHT) or characters
	(Note: characters must be in uppercase) to be
	checked if key is pressed
	*/
	bool press(int key)
	{
		return GetAsyncKeyState(key);
	}

	/*
	bool release(int key)
	* key - The key which is pressed. You can either
	use VK_KEYS (i.e. VK_RIGHT) or characters
	(Note: characters must be in uppercase) to be
	checked if key is released
	*/
	bool release(int key)
	{
		return !GetAsyncKeyState(key);
	}
};
