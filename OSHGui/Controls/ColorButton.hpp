#pragma once

#include "Control.hpp"
#include "../Drawing/Image.hpp"
#include "ColorPicker.hpp"

namespace OSHGui
{
	class ColorPicker;

	class OSHGUI_EXPORT ColorButton : public Control
	{
	public:
		ColorButton();
		Drawing::Color GetColor();
		void SetColor( Drawing::Color color );
		void Expand();
		void Collapse();
		void OnMouseDown( const MouseMessage &mouse );
		bool Intersect( const Drawing::PointI &point ) const;
		void HandleMouseEvent( const MouseMessage &mouse );
		void DrawSelf( Drawing::RenderContext &context );
		void PopulateGeometry();

	private:
		bool droppedDown_;
		Drawing::Color color_;
		ColorPicker *picker;
	};
}