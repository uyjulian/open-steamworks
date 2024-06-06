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

#ifndef ISTEAMPARENTALSETTINGS_H
#define ISTEAMPARENTALSETTINGS_H
#ifdef _WIN32
#pragma once
#endif

#include "SteamTypes.h"

// Feature types for parental settings
enum EParentalFeature
{
	k_EFeatureInvalid = 0,
	k_EFeatureStore = 1,
	k_EFeatureCommunity = 2,
	k_EFeatureProfile = 3,
	k_EFeatureFriends = 4,
	k_EFeatureNews = 5,
	k_EFeatureTrading = 6,
	k_EFeatureSettings = 7,
	k_EFeatureConsole = 8,
	k_EFeatureBrowser = 9,
	k_EFeatureParentalSetup = 10,
	k_EFeatureLibrary = 11,
	k_EFeatureTest = 12,
	k_EFeatureMax
};

class ISteamParentalSettings001
{
public:
	virtual bool BIsParentalLockEnabled() = 0;
	virtual bool BIsParentalLockLocked() = 0;

	virtual bool BIsAppBlocked( AppId_t nAppID ) = 0;
	virtual bool BIsAppInBlockList( AppId_t nAppID ) = 0;

	virtual bool BIsFeatureBlocked( EParentalFeature eFeature ) = 0;
	virtual bool BIsFeatureInBlockList( EParentalFeature eFeature ) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Callback for querying UGC
//-----------------------------------------------------------------------------
struct SteamParentalSettingsChanged_t
{
	enum { k_iCallback = 5000 + 1 };
};


#endif // ISTEAMPARENTALSETTINGS_H
