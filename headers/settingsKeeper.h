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
	void UpdatePath(QString path);
	void UpdateDrawParams(PlotParameters* params);
    //Класс записи данных в реестр
	void SaveSettings() const;
    //Параметры
	QString GetLastPath() const;
	~SettingsKeeper();
	QString lastPath = "";
	int quality = 90;
	double scale = 6;
	int imageType = 0;

private:
	QSettings* Settings;
};
