#include "includes.h"

#define GET_X_LPARAM( lp ) ( (int)(short)LOWORD( lp ) )
#define GET_Y_LPARAM( lp ) ( (int)(short)HIWORD( lp) )

static ulong_t __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	if( g_input.handle( hwnd, msg, wparam, lparam ) )
		return true;

	return CallWindowProcA( g_input.m_original_wndproc, hwnd, msg, wparam, lparam );
}

Input::Input() : m_window_handle{}, m_original_wndproc{}, m_key_pressed{} {

}

bool Input::init( const std::string &window_name ) {
    // we already have a window handle, return.
	if( m_window_handle )
		return false;

	m_window_handle = FindWindowA( window_name.c_str(), nullptr );

	m_original_wndproc = (WNDPROC)SetWindowLongA( m_window_handle, GWLP_WNDPROC, (LONG_PTR)hook );

	return m_original_wndproc != nullptr;
}

bool Input::init( HWND wnd ) {
    // invalid window handle.
    if( !wnd )
        return false;

    // already have a window handle, return.
	if( m_window_handle )
		return false;

    m_window_handle = wnd;

	m_original_wndproc = (WNDPROC)SetWindowLongA( m_window_handle, GWLP_WNDPROC, (LONG_PTR)hook );

	return m_original_wndproc != nullptr;
}

bool Input::remove() {
    if( !m_window_handle || !m_original_wndproc )
        return false;

	SetWindowLongA( m_window_handle, GWLP_WNDPROC, (LONG_PTR)m_original_wndproc );

	return true;
}

bool Input::process_message( LPMSG msg, WPARAM wparam, LPARAM lparam ) {
	switch( msg->message ) {
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEWHEEL: {
			if( enableMouseInput ) {
				static OSHGui::Drawing::PointI last_mouse_location;

				auto state = OSHGui::MouseState::Unknown;
				auto button = OSHGui::MouseButton::None;

				OSHGui::Drawing::PointI location( GET_X_LPARAM( msg->lParam ), GET_Y_LPARAM( msg->lParam ) );
				int delta = 0;

				switch( msg->message ) {
					case WM_MOUSEMOVE: state = OSHGui::MouseState::Move; break;
					case WM_LBUTTONDOWN:
						SetCapture( msg->hwnd );
						state = OSHGui::MouseState::Down;
						button = OSHGui::MouseButton::Left;
					break;
					case WM_LBUTTONUP:
						ReleaseCapture();
						state = OSHGui::MouseState::Up;
						button = OSHGui::MouseButton::Left;
					break;
					case WM_RBUTTONDOWN:
						SetCapture( msg->hwnd );
						state = OSHGui::MouseState::Down;
						button = OSHGui::MouseButton::Right;
					break;
					case WM_RBUTTONUP:
						ReleaseCapture();
						state = OSHGui::MouseState::Up;
						button = OSHGui::MouseButton::Right;
					break;
					case WM_XBUTTONDOWN:
						SetCapture( msg->hwnd );
						state = OSHGui::MouseState::Down;
						switch ( GET_XBUTTON_WPARAM( wparam ) ) {
							case XBUTTON1: button = OSHGui::MouseButton::XButton1; break;
							case XBUTTON2: button = OSHGui::MouseButton::XButton2; break;
							default: break;
						}
						break;
					case WM_XBUTTONUP:
						ReleaseCapture();
						state = OSHGui::MouseState::Up;
						switch ( GET_XBUTTON_WPARAM( wparam ) ) {
							case XBUTTON1: button = OSHGui::MouseButton::XButton1; break;
							case XBUTTON2: button = OSHGui::MouseButton::XButton2; break;
							default: break;
						}
						break;
					case WM_MBUTTONDOWN:
						SetCapture( msg->hwnd );
						state = OSHGui::MouseState::Down;
						button = OSHGui::MouseButton::Middle;
					break;
					case WM_MBUTTONUP:
						ReleaseCapture();
						state = OSHGui::MouseState::Up;
						button = OSHGui::MouseButton::Middle;
					break;
					case WM_MOUSEWHEEL:
						state = OSHGui::MouseState::Scroll;
						location = last_mouse_location; // not valid when scrolling.
						delta = -( (short)HIWORD( msg->wParam ) / 120 ) * 2; // number of lines to scroll.
					break;
					default: break;
				}

				last_mouse_location = location;

				return InjectMouseMessage( OSHGui::MouseMessage( state, button, location, delta ) );
			}

			break;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		case WM_CHAR:
		case WM_SYSCHAR:
		case WM_IME_CHAR: {
			if( enableKeyboardInput ) {
				auto key_char = '\0';
				auto key_data = OSHGui::Key::None;

				OSHGui::KeyboardState state;

				if( msg->message == WM_CHAR || msg->message == WM_SYSCHAR ) {
					state = OSHGui::KeyboardState::Character;
					key_char = static_cast< OSHGui::Misc::AnsiChar >( msg->wParam );
				}
				else {
					auto modifier = OSHGui::Key::None;
					if( GetKeyState( (int)OSHGui::Key::ControlKey ) < 0 )
						modifier |= OSHGui::Key::Control;
					if( GetKeyState( (int)OSHGui::Key::ShiftKey ) < 0 )
						modifier |= OSHGui::Key::Shift;
					if( GetKeyState( (int)OSHGui::Key::Menu ) < 0 )
						modifier |= OSHGui::Key::Alt;

					state = msg->message == WM_KEYDOWN || msg->message == WM_SYSKEYDOWN ? OSHGui::KeyboardState::KeyDown : OSHGui::KeyboardState::KeyUp;

					key_data = (OSHGui::Key)msg->wParam | modifier;
				}

				if( state != OSHGui::KeyboardState::Unknown )
					return InjectKeyboardMessage( OSHGui::KeyboardMessage( state, key_data, key_char ) );
			}

			break;
		}
		default: break;
	}

	return false;
}

bool Input::handle( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	switch( msg ) {
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

	if( !OSHGui::Application::HasBeenInitialized() )
		return false;

	static bool is_down = false;
	static bool is_clicked = false;

	if( m_key_pressed[ VK_INSERT ] ) {
		is_clicked = false;
		is_down = true;
	}
	else if ( !m_key_pressed[ VK_INSERT ] && is_down ) {
		is_clicked = true;
		is_down = false;
	}
	else {
		is_clicked = false;
		is_down = false;
	}

	if( is_clicked ) {
		// lol bad, fix later.
		static ConVar *cl_mouseenable = g_csgo.m_convar->FindVar( "cl_mouseenable" );

		if( g_custom_renderer.m_instance->IsEnabled() ) {
			g_custom_renderer.m_instance->Disable();
			cl_mouseenable->SetValue( 1 );
		}
		else {
			g_custom_renderer.m_instance->Enable();
			cl_mouseenable->SetValue( 0 );
		}
	}

	if( g_custom_renderer.m_instance->IsEnabled() ) {
		// pass input to oshgui.
		MSG new_msg;
		new_msg.hwnd = hwnd;
		new_msg.message = msg;
		new_msg.wParam = wparam;
		new_msg.lParam = lparam;

		process_message( &new_msg, wparam, lparam );

		return true;
	}

	return false;
}