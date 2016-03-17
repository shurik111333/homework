#include "settings.h"

const QString Settings::numberElements = "Number of elements";
const QString Settings::numberEmpty = "Number of empty spaces";
const QString Settings::loadFactor = "Load factor";
const QString Settings::averageChainLength = "Average length of chain";
const QString Settings::maximalChainLength = "Maximal length of chain";
const QString Settings::mapSize = "Size";

const QMap<QString, IHash *> Settings::hash
{
	{"Polynominal", new PolyHash()},
	{"Linear", new LinearHash()}
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
		map->setHashFunction(hash[name]);
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

IHash *Settings::getHash(const QString &hashName)
{
	return hash[hashName];
}

QString Settings::getInformation(const QString &information)
{
	if (information == numberElements)
		return QString::number(map->count());
	if (information == numberEmpty)
		return QString::number(map->countEmpty());
	if (information == loadFactor)
		return QString::number(map->loadFactor());
	if (information == averageChainLength)
		return QString::number(map->averageLength());
	if (information == maximalChainLength)
		return QString::number(map->getMaxLength());
	if (information == mapSize)
		return QString::number(map->size());
	return QString();
}
