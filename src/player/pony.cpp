#include <algorithm>

#include "pony.hpp"
#include "../stream_helpers.hpp"

using namespace boost::endian;

PonyData::PonyData():
	characterId(-1),
	bodyColor(0),
	eyeColor(0),
	hoofColor(0),
	hairColors({0, 0, 0}),
	cutieMarks({0, 0, 0}),
	bodySize(1.f),
	hornSize(1.f),
	combatLevel(1),
	hoof(0),
	mane(0),
	tail(0),
	eye(0),
	race(Race::earthPony),
	gender(Gender::mare),
	inUse(false)
{
}

float PonyData::getBodySize() const
{
	return bodySize;
}

float PonyData::getHornSize() const
{
	return hornSize;
}

uint32 PonyData::getCombatLevel() const
{
	return combatLevel;
}

void PonyData::setBodySize(float value)
{
	bodySize = std::min(std::max(value, 0.5f), 2.f);
}

void PonyData::setHornSize(float value)
{
	hornSize = std::min(std::max(value, 0.5f), 2.f);
}