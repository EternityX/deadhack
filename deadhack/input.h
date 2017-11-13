#pragma once

class Input {
public:
	bool init( std::string window_name );
	void remove( ) const;
	bool handle( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );

	bool m_key_pressed[ 255 ];
	WNDPROC m_original_wndproc = nullptr;

private:
	HWND m_window_handle = nullptr;
};

extern Input input;