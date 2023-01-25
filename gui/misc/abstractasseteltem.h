#ifndef ABSTRACTASSETELTEM_H
#define ABSTRACTASSETELTEM_H

#include <QWidget>

class AbstractAsseteltem : public QWidget
{
public:
    explicit AbstractAsseteltem(QWidget *parent = nullptr);

    virtual std::pair<float, float> getPosition();
    virtual void setPosition();
    virtual type?? getParent();
    virtual type?? getChild();


signals:

};

#endif // ABSTRACTASSETELTEM_H
