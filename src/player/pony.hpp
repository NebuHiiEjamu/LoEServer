#ifndef _PONY_H
#define _PONY_H

#include <array>

#include "forward.hpp"
#include "../stream.hpp"

enum class Race : Byte
{
	none,
	earthPony,
	unicorn,
	pegasus,
	moose,
	gryphon,
	crystal
};

enum class Gender : Byte
{
	filly,
	colt,
	mare,
	stallion,
	batStallion,
	batMare
};

class PonyData
{
public:
	PonyData();
	float getBodySize() const;
	float getHornSize() const;
	uint32 getCombatLevel() const;
	void setBodySize(float);
	void setHornSize(float);
	void toStream(GameOutStream&) const;
public:
	std::string name;
	std::string nonPonyModel;
	int32 characterId;
	uint32 bodyColor;
	uint32 eyeColor;
	uint32 hoofColor;
	std::array<uint32, 3> hairColors;
	std::array<uint32, 3> cutieMarks;
private:
	float bodySize;
	float hornSize;
	uint32 combatLevel;
public:
	uint16 hoof;
	uint16 mane;
	uint16 tail;
	uint16 eye;
	Race race;
	Gender gender;
private:
	bool inUse;
};

class Pony : public Entity
{
public:
	static constexpr uint32 maxInventorySize = 12;
	static constexpr uint32 maxWornItems = 32;
	Pony(PlayerRef);
private:
	PonyData data;
	PlayerRef owner;
	uint32 bits;
	float maxHealth;
	float defense;
	bool dead;
};

#endif // _PONY_H
