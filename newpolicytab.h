#ifndef NEWPOLICYTAB_H
#define NEWPOLICYTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class NewPolicyTab : public QWidget
{
    Q_OBJECT
public:
    NewPolicyTab(QWidget *parent = nullptr);

public slots:
    void addEntry();

signals:
    void sendDetails(QString type, QString company, QString num, QString period);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;

};

#endif // NEWPOLICYTAB_H
