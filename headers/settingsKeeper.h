// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

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
	void saveSettings() const;
    //Параметры
	QString getLastPath() const;
	~SettingsKeeper();
	QString lastPath = "";
	int quality = 90;
	double scale = 6;
	int imageType = 0;
	int scaleRes = 600;
	QString lang = "";

private:
	QSettings* Settings;
};
