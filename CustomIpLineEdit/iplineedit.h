#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H
#include <QFrame>
#include <QLineEdit>

//=============================================================================
class CustomLineEdit;
class CustomIpEditor : public QFrame
{
    Q_OBJECT
public:
    explicit CustomIpEditor(QWidget *parent = 0);
    virtual ~CustomIpEditor() {}
public slots:
    QString getIp() const;

private:
    QList <CustomLineEdit *>  lines;
};

//=============================================================================
class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(const QString & contents = "", QWidget *parent = 0);
    virtual ~CustomLineEdit() {}

signals:
    void jumpForward();
    void jumpBackward();

public slots:
    void jumpIn();

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    bool selectOnMouseRelease;
};


#endif // IPLINEEDIT_H
