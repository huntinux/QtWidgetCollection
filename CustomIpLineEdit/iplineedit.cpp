#include "iplineedit.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QtGlobal>

//=============================================================================
CustomLineEdit::CustomLineEdit(const QString & contents, QWidget *parent) :
    QLineEdit(contents, parent), selectOnMouseRelease(false)
{
    QIntValidator *valid = new QIntValidator(0, 255, this);
    setValidator(valid);
}

void CustomLineEdit::jumpIn()
{
    setFocus();

    selectOnMouseRelease = false;
    selectAll();
}

void CustomLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    selectOnMouseRelease = true;
}

void CustomLineEdit::keyPressEvent(QKeyEvent * event)
{
    int key = event->key();
    int cursorPos = cursorPosition();

    // Jump forward by Space or '.'
    //if (key == Qt::Key_Space || key == Qt::Key_Period) {

    // Jump forward by Space or '.' and the content is not empty
    if ((key == Qt::Key_Space || key == Qt::Key_Period) && text() != "") {
        emit jumpForward();
        event->accept();
        return;
    }

    // Jump Backward only from 0 cursor position
    if (cursorPos == 0) {
        if ((key == Qt::Key_Left) || (key == Qt::Key_Backspace)) {
            emit jumpBackward();
            event->accept();
            return;
        }
    }

    // Jump forward from last postion by right arrow
    if (cursorPos == text().count()) {
        if (key == Qt::Key_Right) {
            emit jumpForward();
            event->accept();
            return;
        }
    }

    // After key is placed cursor has new position
    QLineEdit::keyPressEvent(event);
    int freshCurPos = cursorPosition();

    if ((freshCurPos == 3) && (key != Qt::Key_Right))
        emit jumpForward();
}

void CustomLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    if(!selectOnMouseRelease)
        return;

    selectOnMouseRelease = false;
    selectAll();

    QLineEdit::mouseReleaseEvent(event);
}

//=============================================================================
void makeCommonStyle(QLineEdit* line) {
    line->setContentsMargins(0, 0, 0, 0);
    line->setAlignment(Qt::AlignCenter);
    line->setStyleSheet("QLineEdit { border: 0px none; }");
    line->setFrame(false);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QLineEdit* makeIpSpliter() {
    QLineEdit *spliter = new QLineEdit(".");
    makeCommonStyle(spliter);

    spliter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spliter->setMaximumWidth(10);
    spliter->setReadOnly(true);
    spliter->setFocusPolicy(Qt::NoFocus);
    return spliter;
}

CustomIpEditor::CustomIpEditor(QWidget *parent) :
    QFrame(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("QFrame { background-color: white;  border: 1px solid white; border-radius: 15px; }");

    //QList <CustomLineEdit *>  lines; // move to member field
    QList <CustomLineEdit *>::iterator linesIterator;

    lines.append(new CustomLineEdit);
    lines.append(new CustomLineEdit);
    lines.append(new CustomLineEdit);
    lines.append(new CustomLineEdit);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    for (linesIterator = lines.begin(); linesIterator != lines.end(); ++linesIterator) {
        makeCommonStyle(*linesIterator);
        mainLayout->addWidget(*linesIterator);

        if (*linesIterator != lines.last()) {
            connect(*linesIterator, &CustomLineEdit::jumpForward,
                    *(linesIterator+1), &CustomLineEdit::jumpIn);
            mainLayout->addWidget(makeIpSpliter());
        }
        if (*linesIterator != lines.first()) {
            connect(*linesIterator, &CustomLineEdit::jumpBackward,
                    *(linesIterator-1), &CustomLineEdit::jumpIn);
        }
    }

}

QString CustomIpEditor::getIp() const
{
    QString ip;
    QList <CustomLineEdit *>::const_iterator litr;
    for(litr = lines.begin(); litr != lines.end(); litr++)
    {
        ip += (*litr)->text() + ".";
    }

    // remove the last '.'
    ip.remove(ip.length() - 1, 1);
    //qDebug("ip=%s", ip.toStdString().c_str());
    return ip;
}
