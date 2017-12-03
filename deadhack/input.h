#pragma once

class Input {
public:
    HWND                    m_window_handle;
    WNDPROC                 m_original_wndproc;
    std::array< bool, 255 > m_key_pressed;

    Input();

	bool init( const std::string &window_name );
    bool init( HWND wnd );
	bool remove();
	bool handle( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
};

extern Input g_input;