// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "changelog.h"

changelog::changelog(SettingsKeeper *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changelog)
{
    ui->setupUi(this);
    QTranslator qtTranslator;
    qtTranslator.load(settings->lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);
    appLogo.load(":logos/Logos/icon.png");
    this->setWindowTitle(STR_Window_Changelog);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));
	this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

#ifdef OWN_HIGHDPI_SCALE
	getOriginFrames();
#endif

	//QMovie* movie = new QMovie(":logos/EasterEgg.gif");
	//QRect frameSize = movie->frameRect();
    //QSize size = QSize(ui->logo->width(), ui->logo->height() * (frameSize.width()/ frameSize.height()));

    //movie->setScaledSize(size);
    //ui->logo->setMovie(movie);
    //movie->start();
}

void changelog::cancelButtonPushed()
{
    this->hide();
}

void changelog::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);
    appLogo.setDevicePixelRatio(this->window()->windowHandle()->devicePixelRatio());
    qreal scale = this->window()->windowHandle()->devicePixelRatio();
    QPixmap labelLogo = appLogo.scaled(ui->logo->width() * scale, ui->logo->height() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->logo->setPixmap(labelLogo);
}

void changelog::resizeEvent(QResizeEvent* event)
{
#ifdef OWN_HIGHDPI_SCALE
	QScreen* screen = this->screen();
	qreal scale = screen->logicalDotsPerInch() / 96.0;
	if (this->maximumSize().height() > sizeH * scale)
	{
		this->setMinimumSize(sizeW * scale, sizeH * scale);
		this->resize(sizeW * scale, sizeH * scale);
		this->setMaximumSize(sizeW * scale, sizeH * scale);
	}
	else
	{
		this->setMaximumSize(sizeW * scale, sizeH * scale);
		this->resize(sizeW * scale, sizeH * scale);
		this->setMinimumSize(sizeW * scale, sizeH * scale);
	}
	resizeUi(scale);
	QPixmap labelLogo = appLogo.scaled(ui->logo->width(), ui->logo->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
#else
	QDialog::resizeEvent(event);
	appLogo.setDevicePixelRatio(this->window()->windowHandle()->devicePixelRatio());
	qreal scale = this->window()->windowHandle()->devicePixelRatio();
	QPixmap labelLogo = appLogo.scaled(ui->logo->width() * scale, ui->logo->height() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
#endif
    ui->logo->setPixmap(labelLogo);
}

#ifdef OWN_HIGHDPI_SCALE

void changelog::resizeUi(qreal mratio)
{
#ifdef DEBUG_PAINT
	QString wName = "";
	int counter = 0;
#endif
	QString widgetClass;
	QString widgetName;
	widgetParams* params;
	foreach(QWidget * w, this->findChildren<QWidget*>())
	{
		widgetClass = w->metaObject()->className();
		widgetName = w->objectName();

		if (widgetClass == "QWidget" || widgetName.count() == 0 || widgetName.contains("qt_")) // Skip all non-user elements
			continue;

		int i = hashWidgets.value(w->objectName());
		if (i > 0)
		{
			params = windgetPramsList[i - 1];
			QPoint pos = params->pos * mratio;

			w->resize(params->geom.width() * mratio, params->geom.height() * mratio);
			w->move(pos);
#ifdef DEBUG_PAINT
			counter++;
			w->update();
			w->repaint();
			QApplication::processEvents();
#endif
		}
	}
}

void changelog::getOriginFrames()
{
	QString widgetClass;
	QString widgetName;
	widgetParams* params;
	foreach(QWidget * w, this->findChildren<QWidget*>())
	{
		widgetClass = w->metaObject()->className();
		widgetName = w->objectName();
		if (widgetClass == "QWidget" || widgetName.count() == 0 || widgetName.contains("qt_")) // Skip all non-user elements
			continue;
		widgetParams* params = new widgetParams();
		params->pos = w->pos();
		params->geom = w->geometry();
		params->minSize = w->minimumSize();
		params->maxSize = w->maximumSize();
		windgetPramsList.append(params);
		hashWidgets.insert(w->objectName(), windgetPramsList.count());
	}
	sizeH = this->height();
	sizeW = this->width();
}

#endif

changelog::~changelog()
{
    delete ui;
}
