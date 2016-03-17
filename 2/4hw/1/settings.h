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
#include <QObject>

class Settings : public QObject
{
	Q_OBJECT

public:
	Settings();
	~Settings();

	static int countCheckBox();
	static QStringList getHashNames();
	static QStringList getCheckBoxNames();
	QString getInformation();
	void setCheckInformationState(const QString &state, bool value);
	void setHash(const QString &name);
	bool getCheckInformationState(const QString &box);
	QString getCurrentHash();
	void insert(const QString &key, int value);
	void remove(const QString &key, int value);
	int find(const QString &key);

signals:
	void mapChanged();

private:
	HashMap *map;
	QString currentHash;
	static const QMap<QString, IHash *> hash;
	static QMap<QString, bool> checkBoxes;
	static const QString numberElements;
	static const QString numberEmpty;
	static const QString loadFactor;
	static const QString averageChainLength;
	static const QString maximalChainLength;

	static IHash *getHash(const QString &hashName);
	QString getInformation(const QString &information);
};
