#pragma once

class Color {
private:
	unsigned char m_color [ 4 ];

public:
	Color() {
		*(int * )this = 0;
	}

	Color( int r, int g, int b, int a = 255 ) {
		SetColor( r, g, b, a );
	}

	int r() const {
		return m_color[ 0 ];
	}

	int g() const {
		return m_color[ 1 ];
	}

	int b() const {
		return m_color[ 2 ];
	}

	int a() const {
		return m_color[ 3 ];
	}

	int GetRawColor() const {
		return *(int *)this;
	}

	Color &operator =( const Color &other ) {
		SetRawColor( other.GetRawColor( ) );

		return *this;
	}

	bool operator ==( const Color &other ) const {
		return *(int *)this == *(int *)&other;
	}

	bool operator !=( const Color &other ) const {
		return !operator ==( other );
	}

	Color operator /( int other ) {
		if( r() > 1 && g() > 1 && b() > 1 )
			return Color( r() / 2, g() / 2, b() / 2 );
		return Color( r(), g(), b() );
	}

	Color operator -( int other ) {
		Color ret = Color( r(), g(), b() );

		if( r() >= other )
			ret.SetR( r() - other );
		else
			ret.SetR( 0 );

		if( g() >= other )
			ret.SetG( g() - other );
		else
			ret.SetG( 0 );

		if( b() >= other )
			ret.SetB( b() - other );
		else
			ret.SetB( 0 );

		return ret;
	}

	Color operator +( int other ) {
		Color ret = Color( r(), g(), b() );

		if( r() + other <= 255 )
			ret.SetR( r() + other );
		else
			ret.SetR( 255 );

		if( g() + other <= 255 )
			ret.SetG( g() + other );
		else
			ret.SetG( 255 );

		if( b() + other <= 255 )
			ret.SetB( b() + other );
		else
			ret.SetB( 255 );

		return ret;
	}

	unsigned char &operator[]( int index ) {
		switch( index ) {
		case 1:
			return m_color[ 1 ];
		case 2:
			return m_color[ 2 ];
		case 3:
			return m_color[ 3 ];
		default:
			return m_color[ 0 ];
		}
	}

	const unsigned char &operator[]( int index ) const {
		switch( index ) {
		case 1:
			return m_color[ 1 ];
		case 2:
			return m_color[ 2 ];
		case 3:
			return m_color[ 3 ];
		default:
			return m_color[ 0 ];
		}
	}

	void SetColor( int r, int g, int b, int a = 255 ) {
		m_color[ 0 ] = unsigned char( r );
		m_color[ 1 ] = unsigned char( g );
		m_color[ 2 ] = unsigned char( b );
		m_color[ 3 ] = unsigned char( a );
	}

	void SetRawColor( int color32 ) {
		*(int *)this = color32;
	}

	void SetR( int r ) {
		m_color[ 0 ] = unsigned char( r );
	}

	void SetG( int g ) {
		m_color[ 1 ] = unsigned char( g );
	}

	void SetB( int b ) {
		m_color[ 2 ] = unsigned char( b );
	}

	void SetA( int a ) {
		m_color[ 3 ] = unsigned char( a );
	}

	template< class T > T R() const {
		return (T)m_color[ 0 ];
	}

	template< class T > T G() const {
		return (T)m_color[ 1 ];
	}

	template< class T > T B() const {
		return (T)m_color[ 2 ];
	}

	template< class T > T A() const {
		return (T)m_color[ 3 ];
	}

	static Color White() {
		return Color( 255, 255, 255 );
	}

	static Color Black() {
		return Color( 0, 0, 0 );
	}

	static Color Red() {
		return Color( 255, 0, 0 );
	}

	static Color Yellow() {
		return Color( 255, 255, 0 );
	}

	static Color Orange() {
		return Color( 255, 165, 0 );
	}

	static Color Green() {
		return Color( 0, 255, 0 );
	}

	static Color Blue() {
		return Color( 0, 0, 255 );
	}
};
