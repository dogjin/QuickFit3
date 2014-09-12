#ifndef QFECALCULATORPLOTDIALOG_H
#define QFECALCULATORPLOTDIALOG_H

#include <QDialog>
#include "qfplotter.h"

namespace Ui {
    class QFECalculatorPlotDialog;
}

class QFECalculatorPlotDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit QFECalculatorPlotDialog(QWidget *parent = 0);
        ~QFECalculatorPlotDialog();

        QFPlotter *getPlotter() const;
        void clearPlots();
        void startAddingPlots();
        void endAddingPlots();
        void setLog(bool logX, bool logY);
        void setAxisLabel(const QString &labX, const QString &labY);
        void setLogX(bool log);
        void setLogY(bool log);
        void setXAxisLabel(const QString& label);
        void setYAxisLabel(const QString& label);
        void addPlot(const QVector<double>& X, const QVector<double>& Y, const QString& spec=QString(), const QString& label=QString());

    protected slots:
        void showHelp();
        void closeClicked();
        void updatePlot();

        void on_chkLogX_toggled(bool checked);
        void on_chkLogY_toggled(bool checked);

    private:
        Ui::QFECalculatorPlotDialog *ui;
};

#endif // QFECALCULATORPLOTDIALOG_H

