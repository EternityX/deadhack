#include "includes.h"

static ulong_t __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	if ( g_input.handle( hwnd, msg, wparam, lparam ) )
		return true;

	return CallWindowProcA( g_input.m_original_wndproc, hwnd, msg, wparam, lparam );
}

Input::Input() : m_window_handle{}, m_original_wndproc{}, m_key_pressed{} {

}

bool Input::init( const std::string &window_name ) {
    // we already have a window handle, return.
	if ( m_window_handle )
		return false;

	m_window_handle = FindWindowA( window_name.c_str(), nullptr );

	m_original_wndproc = (WNDPROC)SetWindowLongA( m_window_handle, GWLP_WNDPROC, (LONG_PTR)hook );
    if( !m_original_wndproc )
        return false;

	return true;
}

bool Input::init( HWND wnd ) {
    // invalid window handle.
    if( !wnd )
        return false;

    // already have a window handle, return.
	if ( m_window_handle )
		return false;

    m_window_handle = wnd;

	m_original_wndproc = (WNDPROC)SetWindowLongA( m_window_handle, GWLP_WNDPROC, (LONG_PTR)hook );
    if( !m_original_wndproc )
        return false;

    return true;
}

bool Input::remove() {
    if( !m_window_handle || !m_original_wndproc )
        return false;

	SetWindowLongA( m_window_handle, GWLP_WNDPROC, (LONG_PTR)m_original_wndproc );

	return true;
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

	// todo; pass the input to imgui / etc.

	return false;
}