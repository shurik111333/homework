#pragma once

#include "hashmap.h"
#include "ihash.h"
#include "polyhash.h"
#include "linearhash.h"
#include <QString>
#include <QVector>
#include <QObject>
#include <QHash>
#include <QStringList>

class Settings
{
public:
	Settings(IHash *hash);
	~Settings();

	static int countCheckBox();
	static QStringList getHashNames();
	static QStringList getCheckBoxNames();


public slots:
	void changeState(const QString &name);
	void changeHash(const QString &hash);

private:
	HashMap map;
	IHash *currentHash;
	static const QHash<QString, IHash*> hash;
	static QHash<QString, bool> checkBoxes;

	IHash *getHash(const QString &hashName);
};
