#pragma once

#include <QtXml/QDomDocument>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTemporaryFile>
#include <QXmlStreamReader>
#include <QMap>
#include <QList>
#include <QString>

/// Represents interface for work with bash.im through rss
class Bash : public QObject
{
	Q_OBJECT

public:
	Bash(QObject *parent = 0);
	~Bash();

	void update();

signals:
	void newContent(QMap<QString, QList<QString> > &content);

private:
	QNetworkAccessManager *manager;
	QString url;
	QMap<QString, QList<QString> > content;
	QTemporaryFile xmlFile;
	QXmlStreamReader xml;

private slots:
	void getUpdate(QNetworkReply *reply);
	void updateContent();
};
