#pragma once

#include <QObject>
#include <QSettings>
#include "plotparameters.h"

//Класс-хранилище настроек (качество изображения, последний путь)

class SettingsKeeper : public QObject
{
	Q_OBJECT

public:
	SettingsKeeper(QObject* parent);
    //Обновление параметров
	void updatePath(QString path);
	void updateDrawParams(PlotParameters* params);
    //Класс записи данных в реестр
	void saveSettings();
    //Параметры
	QString getLastPath();
	~SettingsKeeper();
	QString lastPath = "";
	int quality = 90;
	double scale = 6;
	int imageType = 0;

private:
	QSettings* settings;
};
