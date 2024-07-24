#include "pch.h"
#include "WorldMap.h"
#include "Misc/Delegate.h"
#include "Misc/Function.h"

WorldMap::WorldMap(const std::wstring& kName) 
	: 
	Level(kName),
	func(&WorldMap::ABETest, this)
{
}


void WorldMap::Load()
{
	
}
