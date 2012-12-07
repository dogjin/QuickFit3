#ifndef QFRAWDATAPROPERTYEDITOR_H
#define QFRAWDATAPROPERTYEDITOR_H

#include <QtGui>
#include <QPointer>
#include <QMap>
#include <QSortFilterProxyModel>
#include "qfproject.h"
#include "qfrawdatarecord.h"
#include "programoptions.h"
#include "qfpluginservices.h"
#include "qftools.h"
#include "qenhancedtableview.h"
#include "lib_imexport.h"
#include <QMenu>
#include <QAction>
#include <QList>
#include <QPair>
#include <QTimer>
#include <QModelIndexList>
#include "qfenhancedlineedit.h"
#include "qfstyledbutton.h"
#include "qfcompleterfromfile.h"
#include "qfpropertyitemdelegate.h"
#include "dlg_qffileeditdialog.h"

/*! \brief editor widget (window) for raw data items
    \ingroup qf3lib_project


 As there were problems when changing the displayed editor for different types of raw data items. One editor window
 is only useable for one type of  raw data!
*/
class QFLIB_EXPORT QFRawDataPropertyEditor : public QWidget {
        Q_OBJECT
    public:
        /** Default constructor */
        QFRawDataPropertyEditor(QFPluginServices* services, ProgramOptions* set, QFRawDataRecord* current=NULL, int id=0, QWidget* parent=NULL, Qt::WindowFlags f = Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
        /** Default destructor */
        virtual ~QFRawDataPropertyEditor();
        /** \brief set the current record */
        void setCurrent(QFRawDataRecord* c);
        /** \brief set a Programoptions object to use for storing application settings */
        void setSettings(ProgramOptions* settings);
        /** \brief write the settings */
        void writeSettings();
        /** \brief returns the menubar of this widget */
        QMenuBar* getMenuBar() const;
        /** \brief chages the visiblity of the menubar */
        void setMenuBarVisible(bool visible);
        /** \brief add a new menu to te menubar that is visible for the specified editor only, if editor>=0 or always, if editor<0 */
        QMenu* addMenu(const QString &title, int editor=-1);
        /** \brief tells the editor to switch the visibility of the specified menu according to the set editor (see addMenu() ), but does not add the menu to the main menu bar */
        void registerMenu(QMenu* menu, int editor=-1);
        /** \brief returns a pointer to the help menu of this editor */
        QMenu* getHelpMenu() const;
    protected:
        /** \brief points to the record currently displayed */
        QPointer<QFRawDataRecord> current;
        /** \brief read the settings */
        void readSettings();
        void closeEvent( QCloseEvent * event );
        void resizeEvent ( QResizeEvent * event );


    private slots:
        /** \brief called when the name editor changes its contents */
        void nameChanged(const QString& text);
        /** \brief called when the folder editor changes its contents */
        void folderChanged(const QString& text);
        /** \brief called when the description editor changes its contents */
        void descriptionChanged();
        /** \brief this will be connected to the project to indicate when  the currently
         *         displayed record should be deleted */
        void recordAboutToBeDeleted(QFRawDataRecord* r);
        /** \brief emitted when the "next" button is pressed */
        void nextPressed();
        /** \brief emitted when the "previous" button is pressed */
        void previousPressed();
        /** \brief emitted when the raw data record data changes (i.e. ID, name, description, ...) */
        //void propsChanged(const QString &property=QString(""), bool visible=true);
        void basicPropsChanged();
        /** \brief insert a new property */
        void newPropClicked();
        /** \brief delete a property */
        void deletePropClicked();
        void makePropEditable();
        void copyProperties();
        void cutProperties();
        void pasteProperties();
        /** \brief resize the cells in the properties table */
        void resizePropertiesTable();
        /** \brief remove the current record */
        void deleteRecord();
        void tvResultsSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
        /** \brief delete selected results */
        void deleteSelectedResults();

        /** \brief save results to a file */
        void saveResults();
        void saveResultsAveraged();

        /** \brief display help dialog */
        void displayHelp();

        /** \brief display help dialog with the plugin help */
        void displayHelpPlugin();

        /** \brief display help dialog with the plugin tutorial */
        void displayHelpPluginTutorial();

        /** \brief display help dialog with the plugin copyright note */
        void displayHelpPluginCopyright();

        /** \brief display help dialog with the common RDR help */
        void displayHelpRDR();

        void copyValErrResults();
        void copyValErrResultsNoHead();
        void copyMedianQuantilesResults();
        void copyMedianQuantilesResultsNoHead();

        void filterEvaluationTextChanged(const QString& text);
        void filterResultsTextChanged(const QString& text);
        void currentTabChanged(int tab);
        void checkHelpAvailable();
        void resizePropertiesLater();


        void addFile();
        void removeFile();
        void editFile();
        void showEditFilesWarning(bool activated);
        void copyFile();
        void moveFilesUp();
        void moveFilesDown();
        void openFilesDirectory();
        void showAvgClicked(bool checked);

    private:
        QTimer* timerResizeProps;

        /** \brief create all widgets needed to display data */
        void createWidgets();
        /** \brief QLineEdit for the name */
        QLineEdit* edtName;
        /** \brief QLineEdit for the folder */
        QLineEdit* edtFolder;
        /** \brief QPlainTextEdit for the description */
        QPlainTextEdit* pteDescription;
        /** \brief list of files associated with this rawdatarecord */
        QListWidget* lstFiles;
        /** \brief label next to buttons on top */
        QLabel* labTop;
        /** \brief label next to buttons on top */
        QLabel* labTopIcon;
        /** \brief label for the ID */
        QLabel* labID;
        /** \brief label for the type */
        QLabel* labType;
        /** \brief label for the type icon */
        QLabel* labTypeIcon;
        /** \brief Tab to change between property editor and data view */
        QTabWidget* tabMain;
        /** \brief tabel view for the properties */
        QEnhancedTableView* tvProperties;
        /** \brief button to switch to next record */
        QToolButton* btnNext;
        /** \brief button to insert a new property */
        QToolButton* btnNewProperty;
        QAction* actNewProperty;
        /** \brief button to delete a property */
        QToolButton* btnDeleteProperty;
        QAction* actDeleteProperty;
        /** \brief button to switch to previous record */
        QToolButton* btnPrevious;
        /** \brief button to delete the current record */
        QToolButton* btnDeleteReord;
        /** \brief points to a settings object that is used to store application settings */
        ProgramOptions* settings;
        /** \brief tabel display the evaluation results associated with this file  */
        QEnhancedTableView* tvResults;
        /** \brief label for averaging over selected values in tvResults */
        QLabel* labAveragedresults;
        /** \brief toolbar to access functions of tvResults */
        QToolBar* tbResults;


        QToolButton* btnCopyProperty;
        QAction* actCopyProperty;
        QToolButton* btnCutProperty;
        QAction* actCutProperty;
        QToolButton* btnPasteProperty;
        QAction* actPasteProperty;

        /** \brief widget that is used to display the tvResults table + opt. some more compoinents */
        QWidget* widResults;
        /** \brief button to display help */
        QToolButton* btnHelp;
        QAction* actHelp;
        QAction* actHelpPlugin;
        QAction* actHelpPluginTutorial;
        QAction* actHelpPluginCopyright;
        QAction* actHelpRDR;
        QAction* actPrevious;
        QAction* actNext;
        QAction* actDelete;
        QAction* actClose;

        QAction* actAddFile;
        QAction* actRemoveFile;
        QAction* actEditFile;
        QAction* actCopyFile;
        QAction* actEnableFileActions;
        QAction* actMoveFilesUp;
        QAction* actMoveFilesDown;
        QAction* actOpenFileDirectory;
        QAction* actMakePropertyEditable;



        QMenuBar* menuBar;

        QMenu* menuRDR;
        QMenu* menuHelp;
        QMenu* menuResults;
        QList<QPair<int, QMenu*> > menus;

        /** \brief action used to copy selection in tvResults to clipbord */
        QAction* actCopyValErrResults;
        QAction* actCopyValErrResultsNoHead;
        /** \brief action used to copy selection in tvResults to clipbord */
        QAction* actCopyResults;
        QAction* actCopyResultsNoHead;
        /** \brief action used to save selection in tvResults to file */
        QAction* actSaveResults;
        QAction* actSaveResultsAveraged;
        /** \brief action used to delete selection in tvResults */
        QAction* actDeleteResults;
        QAction* actCopyMedianQuantilesResults;
        QAction* actCopyMedianQuantilesNoHead;

        QFEnhancedLineEdit* edtFilterEvaluation;
        QFEnhancedLineEdit* edtFilterResults;
        QFEnhancedLineEdit* edtFilterEvaluationNot;
        QFEnhancedLineEdit* edtFilterResultsNot;
        QFCompleterFromFile* compFilterEvaluation;
        QFCompleterFromFile* compFilterResults;
        QFCompleterFromFile* compFilterEvaluationNot;
        QFCompleterFromFile* compFilterResultsNot;
        QCheckBox* chkFilterEvaluationRegExp;
        QCheckBox* chkFilterResultsRegExp;
        QCheckBox* chkShowAvg;

        //QSortFilterProxyModel* paramFilterProxy;

        QList<QPointer<QFRawDataEditor> > editorList;
        int id;
        /** \brief pointer that allows for access to central QuickFit services */
        QFPluginServices* services;

        QString currentSaveDir;

        QFPropertyItemDelegate* propDelegate;
};

#endif // QFRAWDATAPROPERTYEDITOR_H
