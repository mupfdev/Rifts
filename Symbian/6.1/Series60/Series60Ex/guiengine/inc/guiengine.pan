/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __GUIENGINE_PAN__
#define __GUIENGINE_PAN__


_LIT(KGuiEnginePanicName,	"GuiEngine");

/** GuiEngine application panic codes */
enum TGuiEnginePanics 
{
	EGuiEngineUnknownCommand = 1,		// Command unknown
	EGuiEngineInvalidBrushType = 2, 	// Brush type is not correct
    EGuiEngineBasicUi = 100
};

#endif // __GUIENGINE_PAN__
