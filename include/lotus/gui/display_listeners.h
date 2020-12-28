
#ifndef LOTUS_GUI_DISPLAY_LISTENERS_H
#define LOTUS_GUI_DISPLAY_LISTENERS_H

namespace lotus {
	
	
	class DisplayMoveListener {
	public:
		virtual ~DisplayMoveListener() {}
		virtual void OnDisplayMove(float x, float y) = 0;
	};
	
	class DisplayResizeListener {
	public:
		virtual ~DisplayResizeListener() {}
		virtual void OnDisplayResize(float width, float height) = 0;
	};
	
	class DisplayCloseListener {
	public:
		virtual ~DisplayCloseListener() {}
		virtual void OnDisplayClose() = 0;
	};
	
	
}

#endif
