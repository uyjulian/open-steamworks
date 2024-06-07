//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef ISTEAMHTMLSURFACE005_H
#define ISTEAMHTMLSURFACE005_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"
#include "HTMLSurfaceCommon.h"

class ISteamHTMLSurface005
{
public:
	virtual ~ISteamHTMLSurface005() {}

	// Must call init and shutdown when starting/ending use of the interface
	virtual bool Init() = 0;
	virtual bool Shutdown() = 0;

	// Create a browser object for display of a html page, when creation is complete the call handle
	// will return a HTML_BrowserReady_t callback for the HHTMLBrowser of your new browser.
	//   The user agent string is a substring to be added to the general user agent string so you can
	// identify your client on web servers.
	//   The userCSS string lets you apply a CSS style sheet to every displayed page, leave null if
	// you do not require this functionality.
	//
	// YOU MUST HAVE IMPLEMENTED HANDLERS FOR HTML_BrowserReady_t, HTML_StartRequest_t,
	// HTML_JSAlert_t, HTML_JSConfirm_t, and HTML_FileOpenDialog_t! See the CALLBACKS
	// section of this interface (AllowStartRequest, etc) for more details. If you do
	// not implement these callback handlers, the browser may appear to hang instead of
	// navigating to new pages or triggering javascript popups.
	//
	virtual SteamAPICall_t CreateBrowser( const char *pchUserAgent, const char *pchUserCSS ) = 0;

	// Call this when you are done with a html surface, this lets us free the resources being used by it
	virtual void RemoveBrowser( HHTMLBrowser unBrowserHandle ) = 0;

	// Navigate to this URL, results in a HTML_StartRequest_t as the request commences 
	virtual void LoadURL( HHTMLBrowser unBrowserHandle, const char *pchURL, const char *pchPostData ) = 0;

	// Tells the surface the size in pixels to display the surface
	virtual void SetSize( HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight ) = 0;

	// Stop the load of the current html page
	virtual void StopLoad( HHTMLBrowser unBrowserHandle ) = 0;
	// Reload (most likely from local cache) the current page
	virtual void Reload( HHTMLBrowser unBrowserHandle ) = 0;
	// navigate back in the page history
	virtual void GoBack( HHTMLBrowser unBrowserHandle ) = 0;
	// navigate forward in the page history
	virtual void GoForward( HHTMLBrowser unBrowserHandle ) = 0;

	// add this header to any url requests from this browser
	virtual void AddHeader( HHTMLBrowser unBrowserHandle, const char *pchKey, const char *pchValue ) = 0;
	// run this javascript script in the currently loaded page
	virtual void ExecuteJavascript( HHTMLBrowser unBrowserHandle, const char *pchScript ) = 0;

	enum EHTMLMouseButton
	{
		eHTMLMouseButton_Left = 0,
		eHTMLMouseButton_Right = 1,
		eHTMLMouseButton_Middle = 2,
	};

	// Mouse click and mouse movement commands
	virtual void MouseUp( HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton ) = 0;
	virtual void MouseDown( HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton ) = 0;
	virtual void MouseDoubleClick( HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton ) = 0;
	// x and y are relative to the HTML bounds
	virtual void MouseMove( HHTMLBrowser unBrowserHandle, int x, int y ) = 0;
	// nDelta is pixels of scroll
	virtual void MouseWheel( HHTMLBrowser unBrowserHandle, int32 nDelta ) = 0;

	//enum EMouseCursor
	//{
	//	dc_user = 0,
	//	dc_none,
	//	dc_arrow,
	//	dc_ibeam,
	//	dc_hourglass,
	//	dc_waitarrow,
	//	dc_crosshair,
	//	dc_up,
	//	dc_sizenw,
	//	dc_sizese,
	//	dc_sizene,
	//	dc_sizesw,
	//	dc_sizew,
	//	dc_sizee,
	//	dc_sizen,
	//	dc_sizes,
	//	dc_sizewe,
	//	dc_sizens,
	//	dc_sizeall,
	//	dc_no,
	//	dc_hand,
	//	dc_blank, // don't show any custom cursor, just use your default
	//	dc_middle_pan,
	//	dc_north_pan,
	//	dc_north_east_pan,
	//	dc_east_pan,
	//	dc_south_east_pan,
	//	dc_south_pan,
	//	dc_south_west_pan,
	//	dc_west_pan,
	//	dc_north_west_pan,
	//	dc_alias,
	//	dc_cell,
	//	dc_colresize,
	//	dc_copycur,
	//	dc_verticaltext,
	//	dc_rowresize,
	//	dc_zoomin,
	//	dc_zoomout,
	//	dc_help,
	//	dc_custom,

	//	dc_last, // custom cursors start from this value and up
	//};

	/*enum EHTMLKeyModifiers
	{
		k_eHTMLKeyModifier_None = 0,
		k_eHTMLKeyModifier_AltDown = 1 << 0,
		k_eHTMLKeyModifier_CtrlDown = 1 << 1,
		k_eHTMLKeyModifier_ShiftDown = 1 << 2,
	};*/

	// keyboard interactions, native keycode is the virtual key code value from your OS, system key flags the key to not
	// be sent as a typed character as well as a key down
	virtual void KeyDown( HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers, bool bIsSystemKey = false ) = 0;
	virtual void KeyUp( HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers ) = 0;
	// cUnicodeChar is the unicode character point for this keypress (and potentially multiple chars per press)
	virtual void KeyChar( HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar, EHTMLKeyModifiers eHTMLKeyModifiers ) = 0;

	// programmatically scroll this many pixels on the page
	virtual void SetHorizontalScroll( HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll ) = 0;
	virtual void SetVerticalScroll( HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll ) = 0;

	// tell the html control if it has key focus currently, controls showing the I-beam cursor in text controls amongst other things
	virtual void SetKeyFocus( HHTMLBrowser unBrowserHandle, bool bHasKeyFocus ) = 0;

	// open the current pages html code in the local editor of choice, used for debugging
	virtual void ViewSource( HHTMLBrowser unBrowserHandle ) = 0;
	// copy the currently selected text on the html page to the local clipboard
	virtual void CopyToClipboard( HHTMLBrowser unBrowserHandle ) = 0;
	// paste from the local clipboard to the current html page
	virtual void PasteFromClipboard( HHTMLBrowser unBrowserHandle ) = 0;

	// find this string in the browser, if bCurrentlyInFind is true then instead cycle to the next matching element
	virtual void Find( HHTMLBrowser unBrowserHandle, const char *pchSearchStr, bool bCurrentlyInFind, bool bReverse ) = 0;
	// cancel a currently running find
	virtual void StopFind( HHTMLBrowser unBrowserHandle ) = 0;

	// return details about the link at position x,y on the current page
	virtual void GetLinkAtPosition(  HHTMLBrowser unBrowserHandle, int x, int y ) = 0;

	// set a webcookie for the hostname in question
	virtual void SetCookie( const char *pchHostname, const char *pchKey, const char *pchValue, const char *pchPath = "/", RTime32 nExpires = 0, bool bSecure = false, bool bHTTPOnly = false ) = 0;

	// Zoom the current page by flZoom ( from 0.0 to 2.0, so to zoom to 120% use 1.2 ), zooming around point X,Y in the page (use 0,0 if you don't care)
	virtual void SetPageScaleFactor( HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY ) = 0;

	// Enable/disable low-resource background mode, where javascript and repaint timers are throttled, resources are
	// more aggressively purged from memory, and audio/video elements are paused. When background mode is enabled,
	// all HTML5 video and audio objects will execute ".pause()" and gain the property "._steam_background_paused = 1".
	// When background mode is disabled, any video or audio objects with that property will resume with ".play()".
	virtual void SetBackgroundMode( HHTMLBrowser unBrowserHandle, bool bBackgroundMode ) = 0;

	// Scale the output display space by this factor, this is useful when displaying content on high dpi devices.
	// Specifies the ratio between physical and logical pixels.
	virtual void SetDPIScalingFactor( HHTMLBrowser unBrowserHandle, float flDPIScaling ) = 0;

	// Open HTML/JS developer tools
	virtual void OpenDeveloperTools( HHTMLBrowser unBrowserHandle ) = 0;

	// CALLBACKS
	//
	//  These set of functions are used as responses to callback requests
	//

	// You MUST call this in response to a HTML_StartRequest_t callback
	//  Set bAllowed to true to allow this navigation, false to cancel it and stay 
	// on the current page. You can use this feature to limit the valid pages
	// allowed in your HTML surface.
	virtual void AllowStartRequest( HHTMLBrowser unBrowserHandle, bool bAllowed ) = 0;

	// You MUST call this in response to a HTML_JSAlert_t or HTML_JSConfirm_t callback
	//  Set bResult to true for the OK option of a confirm, use false otherwise
	virtual void JSDialogResponse( HHTMLBrowser unBrowserHandle, bool bResult ) = 0;

	// You MUST call this in response to a HTML_FileOpenDialog_t callback
	virtual void FileLoadDialogResponse( HHTMLBrowser unBrowserHandle, const char **pchSelectedFiles ) = 0;
};

#endif