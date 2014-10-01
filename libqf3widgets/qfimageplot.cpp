#include "qfimageplot.h"
#include "ui_qfimageplot.h"
#include "programoptions.h"
#include "qftools.h"
#include "statistics_tools.h"

QFImagePlot::QFImagePlot(QWidget *parent, const QString &prefix):
    QWidget(parent),
    ui(new Ui::QFImagePlot)
{
    plteImage=NULL;
    image_data=NULL;
    image_width=0;
    image_height=0;
    this->prefix=prefix;
    ui->setupUi(this);

    ProgramOptions::getConfigWindowGeometry(this, prefix+"window");
    ProgramOptions::getConfigQRadioButton(ui->chkRangeFull, prefix+"chkRangeFull");
    ProgramOptions::getConfigQRadioButton(ui->chkRangeUser, prefix+"chkRangeUser");
    ProgramOptions::getConfigQComboBox(ui->cmbCOlorbar, prefix+"cmbCOlorbar");
    if (ui->chkRangeUser->isChecked()) {
        qfGetConfigQFDoubleEdit(ui->edtRangeMin, prefix+"edtRangeMin");
        qfGetConfigQFDoubleEdit(ui->edtRangeMax, prefix+"edtRangeMax");
    }
    ui->histogram->readSettings(*(ProgramOptions::getInstance()->getQSettings()), prefix+"histogram/");
    connect(ui->image, SIGNAL(plotMouseMove(double,double)), this, SLOT(plotMouseMove(double,double)));
    ui->tabWidget->setCurrentIndex(0);
}

QFImagePlot::~QFImagePlot()
{
    ProgramOptions::setConfigWindowGeometry(this, prefix+"window");
    ui->histogram->writeSettings(*(ProgramOptions::getInstance()->getQSettings()), prefix+"histogram/");
    ProgramOptions::setConfigQRadioButton(ui->chkRangeFull, prefix+"chkRangeFull");
    ProgramOptions::setConfigQRadioButton(ui->chkRangeUser, prefix+"chkRangeUser");
    ProgramOptions::setConfigQComboBox(ui->cmbCOlorbar, prefix+"cmbCOlorbar");
    if (ui->chkRangeUser->isChecked()) {
        qfSetConfigQFDoubleEdit(ui->edtRangeMin, prefix+"edtRangeMin");
        qfSetConfigQFDoubleEdit(ui->edtRangeMax, prefix+"edtRangeMax");
    }
    delete ui;
    clearData();
}

void QFImagePlot::setImage(double *image, int32_t width, int32_t height)
{
    clear();
    ui->histogram->clear();
    if (image && width>0 && height>0) {
        image_data=qfDuplicateArray(image, width*height);
        image_width=width;
        image_height=height;
        ui->histogram->addHistogram(tr("full"), image_data, image_width*image_height, true);
    }
    ui->histogram->updateHistogram(true);
    //qDebug()<<image_data<<image_width<<image_height;
    new_plots();

}

void QFImagePlot::update_plot()
{
    if (!plteImage || !image_data || image_width<=0 || image_height<=0) return;
    plteImage->set_palette(ui->cmbCOlorbar->currentColorPalette());
    if (ui->chkRangeFull->isChecked()) {
        double imin, imax;
        statisticsMinMax(image_data, image_width*image_height, imin, imax);
        ui->edtRangeMin->setValue(imin);
        ui->edtRangeMax->setValue(imax);
        plteImage->set_imageMin(imin);
        plteImage->set_imageMax(imax);
    } else if (ui->chkRangeUser->isChecked()) {
        plteImage->set_imageMin(ui->edtRangeMin->value());
        plteImage->set_imageMax(ui->edtRangeMax->value());
    }
    ui->image->update_plot();
}

void QFImagePlot::clear()
{
    JKQtBasePlotter* plt=ui->image->get_plotter();
    plt->clearGraphs(true);
    JKQTPdatastore* ds=plt->getDatastore();
    ds->clear();
    plteImage=NULL;
    ui->histogram->clear();
    clearData();
}

void QFImagePlot::clearData()
{
    if (image_data) qfFree(image_data);
    image_data=NULL;
    image_width=0;
    image_height=0;
}

void QFImagePlot::new_plots()
{
    ui->image->set_doDrawing(false);
    ui->image->set_emitSignals(false);

    JKQtBasePlotter* plt=ui->image->get_plotter();
    plt->clearGraphs(true);
    JKQTPdatastore* ds=plt->getDatastore();
    ds->clear();
    plteImage=NULL;

    ui->chkRangeFull->setChecked(true);

    if (image_data) {
        plteImage=new JKQTPColumnMathImage(plt);
        plteImage->set_autoImageRange(false);
        plteImage->set_imageColumn(ds->addCopiedImageAsColumn(image_data, image_width, image_height, tr("image")));
        plteImage->set_x(0);
        plteImage->set_y(0);
        plteImage->set_width(image_width);
        plteImage->set_height(image_height);
        plteImage->set_autoImageRange(false);
        plteImage->set_Nx(image_width);
        plteImage->set_Ny(image_height);
        plteImage->set_palette(ui->cmbCOlorbar->currentColorPalette());
        plteImage->set_imageMin(0);
        plteImage->set_imageMax(1);
        plt->addGraph(plteImage);
        plt->set_axisAspectRatio(double(image_width)/double(image_height));
        plt->set_aspectRatio(double(image_width)/double(image_height));
        plt->set_maintainAspectRatio(true);
        plt->setAbsoluteXY(0,image_width,0,image_height);
    }

    ui->image->set_doDrawing(true);
    ui->image->set_emitSignals(true);
    ui->image->zoomToFit();
    ui->labInfo->setText(tr("image: %1x%2 pixels").arg(image_width).arg(image_height));
    update_plot();
}

void QFImagePlot::plotMouseMove(double x, double y)
{
    if (image_data) {
        int xx=floor(x);
        int yy=floor(y);
        double v=0;
        if (xx>=0 && xx<image_width && yy>=0 && yy<image_height) {
            v=image_data[yy*image_width+xx];
            ui->labMouse->setText(tr("image(%1, %2) = %3").arg(xx).arg(yy).arg(v));
        } else {
            ui->labMouse->setText("");
        }
    } else {
        ui->labMouse->setText("");
    }
}

