#include "bash.h"
#include <iostream>
#include <QDir>

Bash::Bash(QObject *parent):
    QObject(parent),
    manager(new QNetworkAccessManager()),
    url("http://bash.im/rss/")
{
	//update();
	QObject::connect(manager, &QNetworkAccessManager::finished,
	                 this, &Bash::getUpdate);
}

Bash::~Bash()
{
	delete manager;
}

void Bash::update()
{
	manager->get(QNetworkRequest(QUrl(url)));
}

void Bash::getUpdate(QNetworkReply *reply)
{
	//xml.clear();
	//QTemporaryFile xmlFile;
	qDebug() << QDir::tempPath() << "\n";
	QTemporaryFile xmlFile;

	int x = xmlFile.write(reply->readAll());
	qDebug() << x << "\n";
	//delete xmlFile;
	return;
	//xml.setDevice(&xmlFile);
	//QXmlStreamReader xml(&xmlFile);

	//updateContent();
}

void Bash::updateContent()
{
	content.clear();
	while (!xml.atEnd())
	{
		auto token = xml.readNext();
		if (token == QXmlStreamReader::StartDocument)
			continue;
		if (token == QXmlStreamReader::StartElement)
		{
			if (xml.name() != "item")
				continue;
			content["description"].push_back(xml.attributes().value("description").toString());
		}
	}

	emit newContent(content);
}
