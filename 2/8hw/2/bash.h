#pragma once

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTemporaryFile>
#include <QXmlStreamReader>
#include <QMap>
#include <QList>
#include <QString>
#include <QByteArray>

/// Represents interface for work with bash.im through rss
class Bash : public QObject
{
	Q_OBJECT

public:
	Bash(QObject *parent = 0);
	~Bash();

	/**
	 * @return Return value of field of index-th quote
	 */
	QString getValue(int index, const QString &field) const;
	/**
	 * @return Return count of quotes
	 */
	int getCount() const;
	QString getQuoteId(int index) const;

public slots:

	/// Request new xml and parse it. Emit newContent, if response was correct
	void update() const;

	/// Post request to change rate for index-th quote
	void rateUp(int index) const;
	void rateDown(int index) const;
	void rateBayan(int index) const;

signals:
	/// Emits when new content was uploaded and parsed
	void newContent();

private:
	QNetworkAccessManager *manager;
	QUrl url;
	QUrl urlRss;
	QList<QMap<QString, QString>> content;
	QTemporaryFile xmlFile;
	QXmlStreamReader xml;

	/// Parse next quote from xml
	void parseQuoteToMap();
	/// Parse xml to quotes
	void updateContent();
	/// Get xml from reply and parse it
	void getUpdate(QNetworkReply *reply);
	void sendPost(const QUrl &url, const QString &data) const;
	void sendPost(const QUrl &url, const QByteArray &data) const;

private slots:
	void getResponse(QNetworkReply *reply);
};
