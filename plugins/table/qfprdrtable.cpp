#include "qfprdrtable.h"
#include <QtGui>
#include "qfrdrtable.h"
#include "dlgcsvparameters.h"

QFPRDRTable::QFPRDRTable(QObject* parent):
    QObject(parent)
{
    //ctor
}

QFPRDRTable::~QFPRDRTable()
{
    //dtor
}

QFRawDataRecord* QFPRDRTable::createRecord(QFProject* parent) {
    return new QFRDRTable(parent);
}


void QFPRDRTable::registerToMenu(QMenu* menu) {
    QAction* insertRDTableFileAct = new QAction(QIcon(":/table_open.png"), tr("Table from File"), parentWidget);
    insertRDTableFileAct->setStatusTip(tr("Insert a new table raw data item from a specified file"));
    connect(insertRDTableFileAct, SIGNAL(triggered()), this, SLOT(insertTableFile()));

    QAction* insertRDTableAct = new QAction(QIcon(":/table_insert.png"), tr("Editable Table"), parentWidget);
    insertRDTableAct->setStatusTip(tr("Insert a new table raw data item, which may be edited in QuickFit 3.0 and is not connected to a file."));
    connect(insertRDTableAct, SIGNAL(triggered()), this, SLOT(insertTable()));

    QMenu* m=new QMenu(tr("&Table"), menu);
    m->setIcon(QIcon(":/projecttree_tablefile.png"));
    m->addAction(insertRDTableAct);
    m->addAction(insertRDTableFileAct);
    menu->addMenu(m);
}


void QFPRDRTable::insertTable() {
    if (project) {
        project->addRawData("table", tr("NEW_TABLE"));
    }
}


void QFPRDRTable::insertTableFile() {
    if (project) {

        dlgCSVParameters* csvDlg=new dlgCSVParameters(parentWidget, settings->getQSettings()->value("table/column_separator", ",").toString(),
                                                              settings->getQSettings()->value("table/decimal_separator", ".").toString(),
                                                      settings->getQSettings()->value("table/comment_start", "#").toString(),
                                                      settings->getQSettings()->value("table/header_start", "#!").toString());
        if (csvDlg->exec()==QDialog::Accepted) {
            QMap<QString, QVariant> p;
            p["column_separator"]=QString(csvDlg->column_separator);
            p["decimal_separator"]=QString(csvDlg->decimal_separator);
            p["comment_start"]=QString(csvDlg->comment_start);
            p["header_start"]=QString(csvDlg->header_start);
            settings->getQSettings()->setValue("table/column_separator", QString(csvDlg->column_separator));
            settings->getQSettings()->setValue("table/decimal_separator", QString(csvDlg->decimal_separator));
            settings->getQSettings()->setValue("table/comment_start", QString(csvDlg->comment_start));
            settings->getQSettings()->setValue("table/header_start", QString(csvDlg->header_start));

            QStringList roParams;
            roParams<<"column_separator"<<"decimal_separator"<<"comment_start"<<"header_start";

            QStringList files = QFileDialog::getOpenFileNames(parentWidget, tr("Select Table File(s) to Import ..."), settings->getCurrentRawDataDir(), tr("Comma Separated Value Files (*.txt *.dat *.csv);;All Files (*.*)"));
            QStringList list = files;
            QStringList::Iterator it = list.begin();
            reporter->setProgressRange(0, list.size());
            int i=0;
            while(it != list.end()) {
                i++;
                reporter->log_text(tr("importing CSV file '%1' using (column_separator='%2', decimal_separator='%3', comment_start='%4', header_start='%5')\n").arg(*it).arg(QString(csvDlg->column_separator)).arg(QString(csvDlg->decimal_separator)).arg(QString(csvDlg->comment_start)).arg(QString(csvDlg->header_start)));
                QFRawDataRecord* e=project->addRawData("table", QFileInfo(*it).fileName(), QStringList(*it), p, roParams);
                if (e->error()) {
                    project->deleteRawData(e->getID());
                    QMessageBox::critical(parentWidget, tr("QuickFit 3.0"), tr("Error while importing '%1':\n%2").arg(*it).arg(e->errorDescription()));
                    reporter->log_error(tr("Error while importing '%1':\n    %2\n").arg(*it).arg(e->errorDescription()));
                }
                settings->setCurrentRawDataDir(QFileInfo(*it).dir().absolutePath());
                ++it;
                reporter->setProgress(i);
                QApplication::processEvents();
            }
            reporter->setProgress(0);
        }
        delete csvDlg;
    }
}

Q_EXPORT_PLUGIN2(qfrdrtable, QFPRDRTable)
