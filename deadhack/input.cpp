#include "includes.h"

Input input;

ulong_t __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	return CallWindowProcA( input.m_original_wndproc, hwnd, msg, wparam, lparam );
}

bool Input::init( std::string window_name ) {
	if ( m_window_handle )
		return false;

	// obtain handle to game window
	m_window_handle = FindWindow( window_name.c_str( ), nullptr );

	// save the original wndproc and install hook
	m_original_wndproc = (WNDPROC)SetWindowLongPtr( m_window_handle, GWLP_WNDPROC, (LONG_PTR)hook );

	return true;
}