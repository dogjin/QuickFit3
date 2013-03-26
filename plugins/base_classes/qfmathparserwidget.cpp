#include "qfmathparserwidget.h"
#include "ui_qfmathparserwidget.h"
#include "programoptions.h"
#include "jkmathparser.h"
#include "qfpluginservices.h"

jkMathParser::jkmpResult QFMathParserWidget_dummy(jkMathParser::jkmpResult* params, unsigned char n, jkMathParser* p) {
    jkMathParser::jkmpResult res;

    return res;
}

QFMathParserWidget::QFMathParserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFMathParserWidget)
{
    mp=new jkMathParser();
    functionRef=new QFFunctionReferenceTool(NULL);
    functionRef->setCompleterFile(ProgramOptions::getInstance()->getConfigFileDirectory()+"/completers/table/table_expression.txt");
    functionRef->setDefaultWordsMathExpression();

    ui->setupUi(this);

    functionRef->registerEditor(ui->edtFormula);
    functionRef->setLabHelp(ui->labHelp);
    functionRef->setLabProgress(ui->labProgress);
    functionRef->setLabTemplate(ui->labTemplate);
    functionRef->setProgress(ui->progress);
    functionRef->setDefaultHelp(QFPluginServices::getInstance()->getPluginHelpDirectory("table")+"mathparser.html");



    QStringList defaultWords;
    //defaultWords<<"A";
    //defaultWords<<"B";



    functionRef->addDefaultWords(defaultWords);


    ui->edtFormula->setText(ProgramOptions::getConfigValue("QFMathParserWidget/expression", "").toString());
    ui->lstFunctions->setModel(functionRef->getHelpModel());

    QTimer::singleShot(10, this, SLOT(delayedStartSearch()));

}

QFMathParserWidget::~QFMathParserWidget()
{
    delete functionRef;
    ProgramOptions::setConfigValue("QFMathParserWidget/expression", ui->edtFormula->text());
    delete ui;
    delete mp;
}

QString QFMathParserWidget::getExpression() const
{
    return ui->edtFormula->text();
}

void QFMathParserWidget::setExpression(const QString &exp)
{
    ui->edtFormula->setText(exp);
}

void QFMathParserWidget::addExpressionDefaultWords(const QStringList &words)
{
    functionRef->addDefaultWords(words);
}

void QFMathParserWidget::on_edtFormula_textChanged(QString text) {
    try {
        ui->labError->setText(tr("<font color=\"darkgreen\">OK</font>"));
        jkMathParser::jkmpNode* n;
        // parse some numeric expression
        n=mp->parse(getExpression().toStdString());
        delete n;
    } catch(std::exception& E) {
        ui->labError->setText(tr("<font color=\"red\">ERROR:</font> %1").arg(E.what()));
    }

}


void QFMathParserWidget::on_btnHelp_clicked()
{
    QFPluginServices::getInstance()->displayHelpWindow(QFPluginServices::getInstance()->getPluginHelpDirectory("table")+"mathparser.html");
}

void QFMathParserWidget::on_lstFunctions_doubleClicked(const QModelIndex &index)
{
    QString textOld=ui->edtFormula->text();
    QString text="";
    QString templ=index.data().toString();
    int cur=ui->edtFormula->cursorPosition();
    int newcur=cur;
    int selStart=ui->edtFormula->selectionStart();
    int newselStart=selStart;
    int selLen=ui->edtFormula->selectedText().size();
    int newselLen=0;

    if (selLen>0) {
        text=textOld.left(selStart);
        text=text+templ;
        text=text+textOld.right(textOld.size()-(selStart+selLen));

        newcur=cur+templ.size()+1;
        newselStart=newcur;
        newselLen=0;

        int ppos=templ.indexOf("(");
        if (ppos>=0) {
            newcur=selStart+ppos+1;
            newselStart=newcur;
            newselLen=0;
            int i=ppos+1;
            while (i<templ.size() && (templ[i].isLetterOrNumber() || templ[i]=='_')) {
                i++;
                newselLen++;
            }
        }
    } else {
        text=textOld;
        text.insert(cur, templ);

        newcur=cur+templ.size()+1;
        newselStart=newcur;
        newselLen=0;

        int ppos=templ.indexOf("(");
        if (ppos>=0) {
            newcur=cur+ppos+1;
            newselStart=newcur;
            newselLen=0;
            int i=ppos+1;
            while (i<templ.size() && (templ[i].isLetterOrNumber() || templ[i]=='_')) {
                i++;
                newselLen++;
            }
        }
    }

    ui->edtFormula->setText(text);
    ui->edtFormula->setFocus(Qt::OtherFocusReason);
    if (newselLen>0 && newselStart>=0) {
        ui->edtFormula->setCursorPosition(newselStart);
        ui->edtFormula->cursorForward(true, newselLen);
    } else {
        ui->edtFormula->setCursorPosition(newcur);
    }
}

void QFMathParserWidget::on_lstFunctions_clicked(const QModelIndex &index)
{
    QString txt=index.data().toString();
    QString name="";
    int i=0;
    while (i<txt.size() && (txt[i].isLetterOrNumber() || txt[i]=='_')) {
        name=name+txt[i];
        i++;
    }
    QString word=name.toLower().trimmed();
    if (functionRef->hasFunction(word)) {
        ui->labHelp->setText(getFunctionHelp(word));
        ui->labTemplate->setText(tr("<tt>%1</tt>").arg(getFunctionTemplate(word)));
    }

}

void QFMathParserWidget::delayedStartSearch()
{
    QStringList sl;
    sl<<QFPluginServices::getInstance()->getMainHelpDirectory()+"/parserreference/";
    functionRef->startSearch(sl);
}


QString QFMathParserWidget::getFunctionTemplate(QString name)
{
    return functionRef->getFunctionTemplate(name);
}

QString QFMathParserWidget::getFunctionHelp(QString name)
{
    return functionRef->getFunctionHelp(name);
}


