#include "settingsKeeper.h"

SettingsKeeper::SettingsKeeper(QObject *parent)
	: QObject(parent)
{
	Settings = new QSettings("KemSU","QGraphViewer");
	if(!Settings->contains("lastPath"))
		Settings->setValue("lastPath", "");
	else
		lastPath = Settings->value("lastPath").toString();
	if (!Settings->contains("quality"))
		Settings->setValue("quality", 90);
	else
		quality = Settings->value("quality").toInt();
	if (!Settings->contains("scale"))
		Settings->setValue("scale", 6);
	else
		scale = Settings->value("scale").toDouble();
	if (!Settings->contains("imageType"))
		Settings->setValue("imageType", 0);
	else
		imageType = Settings->value("imageType").toInt();
	
}

void SettingsKeeper::UpdatePath(QString path)
{
	if (path == "") return;
	if (path[path.size() - 1] != "/")
		path += "/";
	lastPath = path;
}

void SettingsKeeper::UpdateDrawParams(PlotParameters *params)
{
	this->imageType = params->preferFormat;
	this->scale = params->drawScale;
	this->quality = params->drawQuality;
}

void SettingsKeeper::SaveSettings() const
{
	Settings->setValue("lastPath", lastPath);
	Settings->setValue("imageType", imageType);
	Settings->setValue("scale", scale);
	Settings->setValue("quality", quality);
}

QString SettingsKeeper::GetLastPath() const
{
	return lastPath;
}

SettingsKeeper::~SettingsKeeper()
= default;
