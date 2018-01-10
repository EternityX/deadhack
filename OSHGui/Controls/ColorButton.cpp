#include "ColorButton.hpp"
#include "MessageBox.hpp"
#include "Misc/Intersection.hpp"

namespace OSHGui
{
	ColorButton::ColorButton() 
		: droppedDown_( false ),
		  color_( Drawing::Color::White() )
	{
		picker = new ColorPicker();
		picker->SetLocation( Drawing::PointI( 0, 10 ) );
		picker->SetVisible( false );

		picker->GetColorChangedEvent() += ColorChangedEventHandler( [ this ]( Control*, const Drawing::Color &color )
		{
			color_ = picker->GetColor();
			Invalidate();
		} );

		AddSubControl( picker );

		ApplyStyle( Application::Instance().GetStyle() );
	}

	void ColorButton::Expand()
	{
		droppedDown_ = true;
		picker->SetVisible( true );
		picker->Focus();

		Invalidate();
	}

	void ColorButton::Collapse()
	{
		droppedDown_ = false;
		picker->SetVisible( false );

		Invalidate();
	}

	void ColorButton::OnMouseDown( const MouseMessage &mouse )
	{
		Control::OnMouseDown( mouse );

		HandleMouseEvent( mouse );
	}

	bool ColorButton::Intersect( const Drawing::PointI &point ) const
	{
		return Intersection::TestRectangle( Drawing::PointI( absoluteLocation_.X, absoluteLocation_.Y ), Drawing::SizeF( 15, 9 ), point );
	}

	void ColorButton::HandleMouseEvent( const MouseMessage &mouse )
	{
		if( !droppedDown_ )
		{
			Expand();
		}
		else
		{
			Collapse();
		}
	}

	void ColorButton::DrawSelf( Drawing::RenderContext &context )
	{
		Control::DrawSelf( context );

		if( droppedDown_ && Control::GetIsFocused() || droppedDown_ && picker->GetIsFocused() && picker->GetParent() == this )
		{
			picker->Render();
		}
	}

	void ColorButton::PopulateGeometry()
	{
		using namespace Drawing;

		Graphics g( *geometry_ );

		g.FillRectangle( Color::FromARGB( 255, 18, 18, 26 ), PointF( -1, -1 ), SizeF( 16, 9 ) );
		g.FillRectangle( color_, PointF( 0, 0 ), SizeF( 14, 7 ) );
		//g.DrawRectangle( color_, Drawing::PointI( absoluteLocation_.X + 7, absoluteLocation_.Y ), Drawing::SizeF( 35, 20 ) );
	}
}
