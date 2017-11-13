#include "includes.h"

Input input;

ulong_t __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	if ( input.handle( hwnd, msg, wparam, lparam ) )
		return true;

	// call original
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

void Input::remove( ) const {
	SetWindowLongPtr( m_window_handle, GWLP_WNDPROC, (LONG_PTR)m_original_wndproc );
}

bool Input::handle( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	switch ( msg ) {
		// left mouse
		case WM_LBUTTONDOWN: m_key_pressed[ VK_LBUTTON ] = true; break;
		case WM_LBUTTONUP: m_key_pressed[ VK_LBUTTON ] = false; break;

		// right mouse
		case WM_RBUTTONDOWN: m_key_pressed[ VK_RBUTTON ] = true; break;
		case WM_RBUTTONUP: m_key_pressed[ VK_RBUTTON ] = false; break;

		// regular key
		case WM_KEYDOWN: m_key_pressed[ wparam ] = true; break;
		case WM_KEYUP: m_key_pressed[ wparam ] = false; break;

		// side mouse
		case WM_XBUTTONDOWN: {
			switch ( GET_XBUTTON_WPARAM( wparam ) ) {
				case XBUTTON1: m_key_pressed[ VK_XBUTTON1 ] = true; break;
				case XBUTTON2: m_key_pressed[ VK_XBUTTON2 ] = true; break;
				default: break;
			}

			break;
		}
		case WM_XBUTTONUP: {
			switch ( GET_XBUTTON_WPARAM( wparam ) ) {
				case XBUTTON1: m_key_pressed[ VK_XBUTTON1 ] = false; break;
				case XBUTTON2: m_key_pressed[ VK_XBUTTON2 ] = false; break;
				default: break;
			}

			break;
		}

		default: break;
	}

	// pass the input to imgui
	// todo

	return false;
}