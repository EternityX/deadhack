#pragma once

class Input {
public:
	bool init( std::string window_name );
	WNDPROC m_original_wndproc = nullptr;

private:
	HWND m_window_handle = nullptr;
};

extern Input input;