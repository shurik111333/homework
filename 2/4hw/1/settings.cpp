#include "settings.h"

const QHash<QString, IHash*> Settings::hash
{
	{"Polynominal", new PolyHash()},
	{"Linear", new LinearHash()}
};

QHash<QString, bool> Settings::checkBoxes
{
	{"Number of elements", true},
	{"Number of empty spaces", true},
	{"Load factor", true},
	{"Average length of chain", true},
	{"Maximal length of chain", true}
};

Settings::Settings(IHash *hash):
    currentHash(hash)
{}

Settings::~Settings()
{
	delete currentHash;
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

void Settings::changeState(const QString &name)
{
	checkBoxes[name] = !checkBoxes[name];
	/*bool value = checkBoxes[name];
	checkBoxes.insert(name, !value);*/
}

void Settings::changeHash(const QString &hash)
{
	currentHash = getHash(hash);
}

IHash *Settings::getHash(const QString &hashName)
{
	return hash[hashName];
}
