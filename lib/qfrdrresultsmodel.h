#ifndef QFRDRRESULTSMODEL_H
#define QFRDRRESULTSMODEL_H

#include "lib_imexport.h"
#include <QAbstractTableModel>
#include <QStringList>

// forward declaration
class QFRawDataRecord;

/*! \brief class to display the results stored in QFRawDataRecord
    \ingroup qf3lib_project

    This model is meant to be used together with QFHTMLDelegate

*/
class QFLIB_EXPORT QFRDRResultsModel : public QAbstractTableModel {
        Q_OBJECT
    public:
        /** Default constructor */
        QFRDRResultsModel(QObject* parent=NULL);
        /** Default destructor */
        virtual ~QFRDRResultsModel();

        void init(QFRawDataRecord* record);

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;

        Qt::ItemFlags flags(const QModelIndex &index) const;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        enum {
            ValueRole=Qt::UserRole,        /**< returns the value as a string, the way it should be displayed in the table (i.e. with shortened lists/matrices ...) */
            NameRole=Qt::UserRole+1,       /**< same as ResultNameRole, i.e. returns the resultName of the result displayed in the cell */
            AvgRole=Qt::UserRole+2,        /**< returns the average of all numeric values (for lists and matrices) in this cell */
            SDRole=Qt::UserRole+3,         /**< same as AvgRole, but retruns the standard deviation */
            SumRole=Qt::UserRole+4,        /**< same as AvgRole, but returns the sum (usefull when calculating avergae/SD over several cells) */
            Sum2Role=Qt::UserRole+5,       /**< same as AvgRole, but returns the sum of squares (usefull when calculating avergae/SD over several cells) */
            CountRole=Qt::UserRole+6,      /**< returns the number of values represented by the cell (i.e. items in list/matrix, or 1) */
            EvalNameRole=Qt::UserRole+7,   /**< returns the evaluation name of the result in the cell */
            ResultNameRole=Qt::UserRole+8  /**< returns the resultname of the result in the cell */
        };
    public slots:
        void setResultFilter(QString filter);
        void setEvaluationFilter(QString filter);
        void setResultFilterNot(QString filter);
        void setEvaluationFilterNot(QString filter);
        void setEvaluationFilterUsesRegExp(bool use);
        void setResultFilterUsesRegExp(bool use);
    private slots:
        void resultsChanged(const QString &evalName=QString(""), const QString &resultName=QString(""), bool deleted=false);
    protected:
        QFRawDataRecord* record;
    private:

        /** \brief calculate average and standard deviation over all result for a given result name */
        void calcStatistics(QString resultName, double& average, double& stddev) const;

        /** \brief current list of all shown result names (updated on model reset, using calcResultNames() */
        QStringList lastResultNames;
        /** \brief current list of all shown result labels (updated on model reset, using calcResultNames() */
        QStringList lastResultLabels;
        /** \brief list of all columns/evaluation result sets in the model (as they are unsorted in the QFRawDataRecord), where one string is the ID and the second the label */
        QList<QPair<QString, QString> > lastResultSets;

        QString resultFilter;
        QString evaluationFilter;
        QString resultFilterNot;
        QString evaluationFilterNot;
        bool resultFilterRegExp;
        bool evaluationFilterRegExp;

        /** �brief checks whether the specified result is visible, also returns (optionally) the row/column header label for the result */
        bool fulfillsFilters(const QString& en, const QString& resultName, QString* enLabel=NULL, QString* rnLabel=NULL);
};

#endif // QFRDRRESULTSMODEL_H
