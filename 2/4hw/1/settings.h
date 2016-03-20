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
#include <QSharedPointer>

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

	enum class CheckBoxKeys
	{
		numberElements,
		numberEmpty,
		loadFactor,
		averageChainLength,
		maximalChainLength,
		mapSize
	};

	static const QMap<QString, QSharedPointer<IHash>> hash;
	static QMap<QString, bool> checkBoxes;
	static const QMap<QString, Settings::CheckBoxKeys> checkBoxKeys;

	static const QString numberElements;
	static const QString numberEmpty;
	static const QString loadFactor;
	static const QString averageChainLength;
	static const QString maximalChainLength;
	static const QString mapSize;

	static const QString polyHash;
	static const QString lineHash;

	static QSharedPointer<IHash> getHash(const QString &hashName);
	QString getInformation(const QString &information);
};
