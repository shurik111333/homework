#include "bash.h"
#include <iostream>
#include <QDir>
#include <QStringList>

Bash::Bash(QObject *parent):
    QObject(parent),
    manager(new QNetworkAccessManager()),
    url(QUrl("http://bash.im/")),
    urlRss(QUrl("http://bash.im/rss/"))
{
	QObject::connect(manager, &QNetworkAccessManager::finished,
	                 this, &Bash::getResponse);
}

Bash::~Bash()
{
	delete manager;
}

void Bash::update() const
{
    manager->get(QNetworkRequest(urlRss));
}

QString Bash::getValue(int index, const QString &field) const
{
	return content[index][field];
}

int Bash::getCount() const
{
	return content.size();
}

QString Bash::getQuoteId(int index) const
{
	return content[index]["id"];
}

void Bash::rateUp(int index) const
{
	sendPost(url, "quote=" + content[index]["id"] + "&act=rulez");
}

void Bash::rateDown(int index) const
{
	sendPost(url, "quote=" + content[index]["id"] + "&act=sux");
}

void Bash::rateBayan(int index) const
{
	sendPost(url, "quote=" + content[index]["id"] + "&act=bayan");
}

void Bash::parseQuoteToMap()
{
	QMap<QString, QString> values;
	while (!(xml.isEndElement() && xml.name().toString() == "item"))
	{
		auto token = xml.readNext();
		if (token == QXmlStreamReader::StartElement)
			values[xml.name().toString()] = xml.readElementText();
	}
	auto list = values["link"].split('/');
	values["id"] = list.last();
	content.push_back(values);
}

void Bash::updateContent()
{
    content.clear();
	while (!xml.atEnd())
	{
		auto token = xml.readNext();
		if (token == QXmlStreamReader::StartDocument)
			continue;
		if (token == QXmlStreamReader::StartElement && xml.name() == "item")
			parseQuoteToMap();
	}

	xml.clear();
	emit newContent();
}

void Bash::getUpdate(QNetworkReply *reply)
{
	QTemporaryFile xmlFile;
	if (!xmlFile.open())
	{
		qDebug() << "Failed open tmp file\n";
		return;
	}
	if (xmlFile.write(reply->readAll()) == -1)
	{
		qDebug() << "Failed write to temp file\n";
		return;
	}
	xmlFile.reset();

	xml.setDevice(&xmlFile);
	updateContent();
}

void Bash::sendPost(const QUrl &url, const QString &data) const
{
	sendPost(url, data.toUtf8());
}

void Bash::sendPost(const QUrl &url, const QByteArray &data) const
{
    auto request = QNetworkRequest(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

	qDebug() << "Post request:" << request.url().toString() << "; data:" << data << "\n";

	manager->post(request, data);
}

void Bash::getResponse(QNetworkReply *reply)
{
	qDebug() << "Size of answer:" << reply->bytesAvailable();
	qDebug() << "Response from:" << reply->url().toString() << "status code"
	         << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << "\n";
	if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302)
	{
		qDebug() << "Go to location header\n";
		manager->get(QNetworkRequest(reply->header(QNetworkRequest::LocationHeader).toUrl()));
	}
	if (reply->url() == urlRss)
		getUpdate(reply);
    reply->close();
    reply->deleteLater();
}

