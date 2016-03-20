#include "settings.h"

const QString Settings::numberElements = "Number of elements";
const QString Settings::numberEmpty = "Number of empty spaces";
const QString Settings::loadFactor = "Load factor";
const QString Settings::averageChainLength = "Average length of chain";
const QString Settings::maximalChainLength = "Maximal length of chain";
const QString Settings::mapSize = "Size";
const QString Settings::polyHash = "Polynominal";
const QString Settings::lineHash = "Linear";

const QMap<QString, QSharedPointer<IHash>> Settings::hash
{
	{Settings::polyHash, QSharedPointer<IHash>(new PolyHash())},
	{Settings::lineHash, QSharedPointer<IHash>(new LinearHash())}
};

QMap<QString, bool> Settings::checkBoxes
{
	{Settings::numberElements, true},
	{Settings::numberEmpty, true},
	{Settings::loadFactor, true},
	{Settings::averageChainLength, true},
	{Settings::maximalChainLength, true},
	{Settings::mapSize, true}
};

const QMap<QString, Settings::CheckBoxKeys> Settings::checkBoxKeys
{
	{Settings::numberElements, Settings::CheckBoxKeys::numberElements},
	{Settings::numberEmpty, Settings::CheckBoxKeys::numberEmpty},
	{Settings::loadFactor, Settings::CheckBoxKeys::loadFactor},
	{Settings::averageChainLength, Settings::CheckBoxKeys::averageChainLength},
	{Settings::maximalChainLength, Settings::CheckBoxKeys::maximalChainLength},
	{Settings::mapSize, Settings::CheckBoxKeys::mapSize}
};

Settings::Settings()
{
	currentHash = hash.begin().key();
	map = new HashMap(getHash(currentHash));
}

Settings::~Settings()
{
	delete map;
}

int Settings::countCheckBox()
{
	return checkBoxes.size();
}

QStringList Settings::getHashNames()
{
	return hash.keys();
}

QStringList Settings::getCheckBoxNames()
{
	return checkBoxes.keys();
}

QString Settings::getInformation()
{
	QString information("Hash function: ");
	information.append(currentHash).append("\n");
	for (QString s : checkBoxes.keys())
	{
		if (checkBoxes[s])
			information.append(s).append(": ").append(getInformation(s)).append("\n");
	}
	return information;
}

void Settings::setCheckInformationState(const QString &state, bool value)
{
	checkBoxes[state] = value;
}

void Settings::setHash(const QString &name)
{
	if (currentHash != name)
	{
		currentHash = name;
		map->setHashFunction(getHash(name));
		emit mapChanged();
	}
}

bool Settings::getCheckInformationState(const QString &box)
{
	return checkBoxes[box];
}

QString Settings::getCurrentHash()
{
	return currentHash;
}

void Settings::insert(const QString &key, int value)
{
	map->insert(key, value);
	emit mapChanged();
}

void Settings::remove(const QString &key, int value)
{
	map->remove(key, value);
	emit mapChanged();
}

int Settings::find(const QString &key)
{
	return map->find(key);
}

QSharedPointer<IHash> Settings::getHash(const QString &hashName)
{
	return hash[hashName];
}

QString Settings::getInformation(const QString &information)
{
	CheckBoxKeys key = checkBoxKeys[information];
	switch (key)
	{
		case CheckBoxKeys::averageChainLength:
			return QString::number(map->averageLength());
		case CheckBoxKeys::loadFactor:
			return QString::number(map->loadFactor());
		case CheckBoxKeys::mapSize:
			return QString::number(map->size());
		case CheckBoxKeys::maximalChainLength:
			return QString::number(map->getMaxLength());
		case CheckBoxKeys::numberElements:
			return QString::number(map->count());
		case CheckBoxKeys::numberEmpty:
			return QString::number(map->countEmpty());
		default:
			return QString();
	}
}
