#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QString,QString,QString,QString,QString,QString,QString,QString, QWidget *parent = nullptr);
    ~Form();

signals:
    void scanButtonClicked(const QString &taskId, const QString &className, const QString &subject);
    void printButtonClicked(const QString &taskId, const QString &className, const QString &subject);

private slots:
    void onPushButtonClicked();

private:
    Ui::Form *ui;
    QString m_taskId;
    QString m_className;
    QString m_subject;
    QString m_buttonType; // "扫描" 或 "打印"
};

#endif // FORM_H
