#ifndef QFRDRIMAGINGFCSDATA_H
#define QFRDRIMAGINGFCSDATA_H

#include <QList>
#include <QObject>
#include <QMap>
#include <QProgressBar>
#include <QStatusBar>
#include <QWidget>
#include <QMenu>
#include <QPair>
#include <QList>
#include <QAction>
#include "qfrawdatarecord.h"
#include "qfrdrimagingfcs_dataeditor.h"
#include "qfrdrimagingfcs_dataeditor_image.h"
#include "qfrawdatarecordfactory.h"
#include "../interfaces/qfrdrfcsdatainterface.h"
#include "../interfaces/qfrdrimagetoruninterface.h"
#include "../interfaces/qfrdroverviewimageinterface.h"
#include "../interfaces/qfrdrsimplecountrateinterface.h"
#include "csvtools.h"
#include "qtriple.h"
#include "qfrdrimagingfcsoverviewrateeditor.h"
#include "qfrdrimagestackinterface.h"



/*! \brief QFRawDataRecord implementation
    \ingroup qf3rdrdp_imaging_fcs

*/
class QFRDRImagingFCSData : public QFRawDataRecord, public QFRDRFCSDataInterface, public QFRDRImageToRunInterface, public QFRDROverviewImageInterface, public QFRDRImageStackInterface, public QFRDRSimpleCountRatesInterface {
        Q_OBJECT
        Q_INTERFACES(QFRDRFCSDataInterface QFRDRImageToRunInterface QFRDROverviewImageInterface QFRDRImageStackInterface QFRDRSimpleCountRatesInterface)
    public:
        /** Default constructor */
        QFRDRImagingFCSData(QFProject* parent);
        /** Default destructor */
        virtual ~QFRDRImagingFCSData();

        /** \brief return type (short type string) */
        virtual QString getType() const { return "imaging_fcs"; }
        /** \brief return type (longer type string, user readable) */
        virtual QString getTypeName() const { return tr("Imaging FCS Data"); }
        /** \brief return a small icon (16x16) */
        virtual QIcon getSmallIcon() const { return QIcon(":/imaging_fcs/qfrdrimagingfcs_small.png"); }
        /** \brief return type description */
        virtual QString getTypeDescription() const { return tr("manages FCS correlation curves from an imaging FCS experiment (SPIM-FCS, TIR-FCS ...)"); }
        /** \brief return a large icon (32x32) */
        virtual QIcon getLargeIcon() const { return QIcon(":/imaging_fcs/qfrdrimagingfcs.png"); }
        /** \brief returns the number of additional editor panes for this record */
        virtual int getEditorCount() { return 3; }
        /** \brief returns the name for the i-th editor pane */
        virtual QString getEditorName(int i);
        /** \brief create an object for the i-th editor pane */
        virtual QFRawDataEditor* createEditor(QFPluginServices* services, int i=0, QWidget* parent=NULL);
        /** \brief export the raw data into the specified format */
        virtual void exportData(const QString& format, const QString& filename)const ;
        /** \brief returns a list of filetypes which correspond to the filetypes returned by getExportFiletypes() */
        QStringList getExportFiletypes();
        /** \brief returns the title of the Export file dialog */
        QString getExportDialogTitle();
        /** \brief returns the filetype of the Export file dialog */
        QString getExportDialogFiletypes();



        /** \copydoc QFRDRFCSDataInterface::getCorrelationRuns() */
        virtual int getCorrelationRuns();
        /** \copydoc QFRDRFCSDataInterface::getCorrelationN() */
        virtual long long getCorrelationN();
        /** \copydoc QFRDRFCSDataInterface::getCorrelationT() */
        virtual double* getCorrelationT();
        /** \copydoc QFRDRFCSDataInterface::getCorrelation() */
        virtual double* getCorrelation();
        /** \copydoc QFRDRFCSDataInterface::getCorrelationRun() */
        virtual double* getCorrelationRun(int run);
        /** \copydoc QFRDRFCSDataInterface::getCorrelationRunError() */
        virtual double* getCorrelationRunError(int run);
        /** \copydoc QFRDRFCSDataInterface::getCorrelationRunName() */
        virtual QString getCorrelationRunName(int run);
        /** \copydoc QFRDRFCSDataInterface::getCorrelationMean() */
        virtual double* getCorrelationMean();
        /** \copydoc QFRDRFCSDataInterface::getCorrelationStdDev() */
        virtual double* getCorrelationStdDev();
        /** \copydoc QFRDRFCSDataInterface::isCorrelationRunVisible() */
        virtual bool isCorrelationRunVisible(int run);
        /** \copydoc QFRDRFCSDataInterface::getCorrelationRunErrors() */
        virtual double* getCorrelationRunErrors();






        /** \brief returns whether to leave out a run */
        virtual bool leaveoutRun(int run);
        /** \brief add a run to the leaveouts */
        virtual void leaveoutAddRun(int run);
        /** \brief remove a run from the leaveouts */
        virtual void leaveoutRemoveRun(int run);
        /** \brief clear all leaveouts */
        virtual void leaveoutClear();

        void maskLoad(const QString& filename);
        void maskSave(const QString& filename);
        void maskClear();
        void maskSetAll();
        void maskSet(uint16_t x, uint16_t y);
        void maskUnset(uint16_t x, uint16_t y, bool value=true);
        void maskToggle(uint16_t x, uint16_t y);
        void maskInvert();
        bool maskGet(uint16_t x, uint16_t y);
        bool* maskGet();

        /** \brief recalculate the averages/std. deviations */
        void recalcCorrelations();


        /** \brief return the number of datapoints in the statistics dataset */
        uint32_t getStatisticsN() const;
        /** \brief return the array of average values of the statsitics */
        double* getStatisticsMean() const;
        /** \brief return the array of standard deviation values of the statsitics */
        double* getStatisticsStdDev() const;
        double* getStatisticsMin() const;
        double* getStatisticsMax() const;
        /** \brief return the array of time points [seconds] for the statsitics */
        double *getStatisticsT() const;

    protected:
        /** \brief write the contents of the object to a XML file */
        virtual void intWriteData(QXmlStreamWriter& w);
        /** \brief read in external data files <b>and</b> data stored in the project file <b>IMPLEMENT IN CHILD CLASSES!</b>
         *
         * If \a e is \c NULL then this method should only read the datafiles already saved in the files property.
         */
        virtual void intReadData(QDomElement* e=NULL);

        /** \brief load data file from videocorrelator CSV file */
        bool loadVideoCorrelatorFile(const QString& filename);

        /** \brief load data file in binary format*/
        bool loadVideoCorrelatorFileBin(const QString &filename);

        /** \brief load data file from Radhard2 array */
        bool loadRadhard2File(const QString& filename);

        /** \brief load overview image file */
        bool loadOverview(const QString& filename);

        /** \brief load an image file into the given arrays */
        bool loadImage(const QString &filename, double **data, int *width, int *height);

        /** \brief load a TIFF video file into the given arrays */
        bool loadVideo(const QString &filename, double **data, int *width, int *height, uint32_t *frames);

        /** \brief load the statistics file */
        bool loadStatistics(const QString& filename);

        void loadQFPropertiesFromB040SPIMSettingsFile(QSettings& settings);

        double getTauMin() const;

    private:
        /** \brief width of the image */
        int width;
        /** \brief height of the image */
        int height;
        /** \brief number of points in correlation curve */
        int N;
        /** \brief points to the correlation curves */
        double* correlations;
        /** \brief average over all correlation curves */
        double* correlationMean;
        /** \brief average over all correlation curves */
        double* correlationStdDev;
        /** \brief points to the correlation curve erorrs */
        double* sigmas;
        /** \brief time axis [seconds] */
        double* tau;


        /** \brief number of data points in the statistics  */
        uint32_t statN;
        /** \brief statistics: average vector */
        double* statAvg;
        /** \brief statistics: standard deviation vector */
        double* statStdDev;
        /** \brief statistics: time [seconds] vector */
        double* statT;
        double* statMin;
        double* statMax;

        bool hasStatistics;
        double statAvgCnt;
        double statSigmaCnt;

        /** \brief overview image */
        double* overviewF;

        struct ovrImageData {
            double* image;
            QString name;
            int width;
            int height;
            QList<QFRDROverviewImageInterface::OverviewImageGeoElement> geoElements;

            ovrImageData() {
                image=NULL;
                name=QString("");
                width=0;
                height=0;
            }
        };

        double* video;
        int video_width;
        int video_height;
        uint32_t video_frames;

        QList<ovrImageData> ovrImages;

        void clearOvrImages();

        /** \brief the leaveout list */
        bool* leaveout;
        //QList<int> leaveout;
    protected:
        /** \brief allocate memory to store a \a x by \a y set of correlation curves (+ additional data, like average and sigmas) with \a N datapoints each */
        virtual void allocateContents(int x, int y, int N);
        void allocateStatistics(uint32_t N);


    public:
        /** \copydoc QFRDRImageToRunInterface::getImageFromRunsWidth() */
        virtual int getImageFromRunsWidth() const;
        /** \copydoc QFRDRImageToRunInterface::getImageFromRunsHeight() */
        virtual int getImageFromRunsHeight() const;
        /** \copydoc QFRDRImageToRunInterface::xyToRun() */
        virtual int xyToRun(int x, int y) const;
        /** \copydoc QFRDRImageToRunInterface::runToX() */
        virtual int runToX(int run) const;
        /** \copydoc QFRDRImageToRunInterface::runToY() */
        virtual int runToY(int run) const;
        /** \copydoc QFRDRImageToRunInterface::xyToIndex() */
        virtual int xyToIndex(int x, int y) const;
        /** \copydoc QFRDRImageToRunInterface::getImageFromRunsPreview() */
        virtual double* getImageFromRunsPreview() const;


        /** \copydoc QFRDROverviewImageInterface::getPreviewImageCount() */
        virtual int getPreviewImageCount() const;
        /** \copydoc QFRDROverviewImageInterface::getPreviewImageWidth() */
        virtual int getPreviewImageWidth(int image) const;
        /** \copydoc QFRDROverviewImageInterface::getPreviewImageHeight() */
        virtual int getPreviewImageHeight(int image) const;
        /** \copydoc QFRDROverviewImageInterface::getPreviewImageName() */
        virtual QString getPreviewImageName(int image) const;
        /** \copydoc QFRDROverviewImageInterface::getPreviewImage() */
        virtual double* getPreviewImage(int image) const;
        /** \copydoc QFRDROverviewImageInterface::getPreviewImageGeoElements() */
        virtual QList<QFRDROverviewImageInterface::OverviewImageGeoElement> getPreviewImageGeoElements(int image) const;




        /** \copydoc QFRDRImageStackInterface::getImageStackCount() */
        virtual int getImageStackCount() const;
        /** \copydoc QFRDRImageStackInterface::getImageStackFrames() */
        virtual uint32_t getImageStackFrames(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackWidth() */
        virtual int getImageStackWidth(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackHeight() */
        virtual int getImageStackHeight(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackChannels() */
        virtual int getImageStackChannels(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStack() */
        virtual double* getImageStack(int stack, uint32_t frame=0, uint32_t channel=0) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackXUnitFactor() */
        virtual double getImageStackXUnitFactor(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackXUnitName() */
        virtual QString getImageStackXUnitName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackXName() */
        virtual QString getImageStackXName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackYUnitFactor() */
        virtual double getImageStackYUnitFactor(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackYUnitName() */
        virtual QString getImageStackYUnitName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackYName() */
        virtual QString getImageStackYName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackTUnitFactor() */
        virtual double getImageStackTUnitFactor(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackTUnitName() */
        virtual QString getImageStackTUnitName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackTName() */
        virtual QString getImageStackTName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackCUnitFactor() */
        virtual double getImageStackCUnitFactor(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackCUnitName() */
        virtual QString getImageStackCUnitName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackCName() */
        virtual QString getImageStackCName(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackDescription() */
        virtual QString getImageStackDescription(int stack) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackChannelName() */
        virtual QString getImageStackChannelName(int stack, int channel) const;
        /** \copydoc QFRDRImageStackInterface::getImageStackTimepointName() */
        virtual QString getImageStackTimepointName(int stack, int t) const;

        /** \copydoc QFRDRCountRatesInterface::getSimpleCountrateAverage() */
        virtual double getSimpleCountrateAverage(int run=-1);
        /** \copydoc QFRDRCountRatesInterface::getSimpleCountrateVariance() */
        virtual double getSimpleCountrateVariance(int run=-1);

};


#endif // QFRDRIMAGINGFCSDATA_H
