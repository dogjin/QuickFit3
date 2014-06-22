#include "qfe_plotterexportercairo.h"
#include <QtGui>
#include <QtPlugin>
#include <iostream>
#include "jkqtcairoengineadapter.h"

#include "jkqtpbaseplotter.h"

#define LOG_PREFIX QString("qfe_plotterexportercairo >>> ").toUpper()

QFEPlotterExporterCairo::QFEPlotterExporterCairo(QObject* parent):
    QObject(parent)
{
	logService=NULL;
}

QFEPlotterExporterCairo::~QFEPlotterExporterCairo() {

}


void QFEPlotterExporterCairo::deinit() {
	/* add code for cleanup here */
}

void QFEPlotterExporterCairo::projectChanged(QFProject* oldProject, QFProject* project) {
	/* usually cameras do not have to react to a change of the project in QuickFit .. so you don't need to do anything here
	   But: possibly you could read config information from the project here
	 */
}

void QFEPlotterExporterCairo::initExtension() {
    /* do initializations here but do not yet connect to the camera! */
    
    /*JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(true, true, QTeXPaintDevice::Tikz));
    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(true, false, QTeXPaintDevice::Tikz));
    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(false, true, QTeXPaintDevice::Tikz));
    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(false, false, QTeXPaintDevice::Tikz));

    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(true, true, QTeXPaintDevice::Pgf));
    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(true, false, QTeXPaintDevice::Pgf));
    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(false, true, QTeXPaintDevice::Pgf));
    JKQtBasePlotter::registerPaintDeviceAdapter(new JKQTPCairoEngineAdapter(false, false, QTeXPaintDevice::Pgf));*/

}


void QFEPlotterExporterCairo::loadSettings(ProgramOptions* settingspo) {
	/* here you could read config information from the quickfit.ini file using settings object */
    if (!settingspo) return;
	if (settingspo->getQSettings()==NULL) return;
    QSettings& settings=*(settingspo->getQSettings()); // the QSettings object for quickfit.ini
	// ALTERNATIVE: read/write Information to/from plugins/extensions/<ID>/<ID>.ini file
	// QSettings settings(services->getConfigFileDirectory()+"/plugins/extensions/"+getID()+"/"+getID()+".ini", QSettings::IniFormat);

}

void QFEPlotterExporterCairo::storeSettings(ProgramOptions* settingspo) {
	/* here you could write config information to the quickfit.ini file using settings object */
    if (!settingspo) return;
	if (settingspo->getQSettings()==NULL) return;
    QSettings& settings=*(settingspo->getQSettings()); // the QSettings object for quickfit.ini

	// ALTERNATIVE: read/write Information to/from plugins/extensions/<ID>/<ID>.ini file
	// QSettings settings(services->getConfigFileDirectory()+"/plugins/extensions/"+getID()+"/"+getID()+".ini", QSettings::IniFormat);

}

void QFEPlotterExporterCairo::log_text(QString message) {
	if (logService) logService->log_text(LOG_PREFIX+message);
	else if (services) services->log_text(LOG_PREFIX+message);
}

void QFEPlotterExporterCairo::log_warning(QString message) {
	if (logService) logService->log_warning(LOG_PREFIX+message);
	else if (services) services->log_warning(LOG_PREFIX+message);
}

void QFEPlotterExporterCairo::log_error(QString message) {
	if (logService) logService->log_error(LOG_PREFIX+message);
	else if (services) services->log_error(LOG_PREFIX+message);
}


Q_EXPORT_PLUGIN2(qfe_plotterexporterCairo, QFEPlotterExporterCairo)
