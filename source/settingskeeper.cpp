#include "settingsKeeper.h"

SettingsKeeper::SettingsKeeper(QObject *parent)
	: QObject(parent)
{
	settings = new QSettings("KemSU","QGraphViewer");
	if(!settings->contains("lastPath"))
		settings->setValue("lastPath", "");
	else
		lastPath = settings->value("lastPath").toString();
	if (!settings->contains("quality"))
		settings->setValue("quality", 90);
	else
		quality = settings->value("quality").toInt();
	if (!settings->contains("scale"))
		settings->setValue("scale", 6);
	else
		scale = settings->value("scale").toDouble();
	if (!settings->contains("imageType"))
		settings->setValue("imageType", 0);
	else
		imageType = settings->value("imageType").toInt();
	
}

void SettingsKeeper::updatePath(QString path)
{
	if (path == "") return;
	if (path[path.size() - 1] != "/")
		path += "/";
	lastPath = path;
}

void SettingsKeeper::updateDrawParams(PlotParameters *params)
{
	this->imageType = params->preferFormat;
	this->scale = params->drawScale;
	this->quality = params->drawQuality;
}

void SettingsKeeper::saveSettings()
{
	settings->setValue("lastPath", lastPath);
	settings->setValue("imageType", imageType);
	settings->setValue("scale", scale);
	settings->setValue("quality", quality);
}

QString SettingsKeeper::getLastPath()
{
	return lastPath;
}

SettingsKeeper::~SettingsKeeper()
{

	
}
