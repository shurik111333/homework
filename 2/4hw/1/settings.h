#pragma once

#include "hashmap.h"
#include "ihash.h"
#include "polyhash.h"
#include "linearhash.h"
#include <QString>
#include <QVector>
#include <QObject>
#include <QMap>
#include <QStringList>

class Settings
{
public:
	Settings();
	~Settings();

	static void init(const QString &hashName);
	static int countCheckBox();
	static QStringList getHashNames();
	static QStringList getCheckBoxNames();
	static QString getInformation();
	static void setCheckInformationState(const QString &state, bool value);
	static void setHash(const QString &name);
	static bool getCheckInformationState(const QString &box);
	static QString getCurrentHash();

public slots:
	void changeState(const QString &name);
	void changeHash(const QString &hash);

private:
	static HashMap *map;
	static QString currentHash;
	static const QMap<QString, IHash*> hash;
	static QMap<QString, bool> checkBoxes;
	static const QString numberElements;
	static const QString numberEmpty;
	static const QString loadFactor;
	static const QString averageChainLength;
	static const QString maximalChainLength;

	static IHash *getHash(const QString &hashName);
	static QString getInformation(const QString &information);
};
