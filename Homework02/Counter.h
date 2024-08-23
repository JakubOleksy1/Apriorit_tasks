#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject {
    Q_OBJECT

public:
    explicit Counter(int startValue, QObject *parent = nullptr);

    int increment();
    int decrement();
    int value() const;

signals:
    void valueChanged(int newValue);

public slots:
    void setValue(int newValue);

private:
    int m_count;
};

#endif // COUNTER_H
