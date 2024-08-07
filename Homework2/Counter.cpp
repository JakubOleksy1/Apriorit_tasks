#include "counter.h"

Counter::Counter(int startValue, QObject *parent) : QObject(parent), m_count(startValue) {}

int Counter::increment() {
    ++m_count;
    emit valueChanged(m_count);
    return m_count;
}

int Counter::decrement() {
    --m_count;
    emit valueChanged(m_count);
    return m_count;
}

int Counter::value() const {
    return m_count;
}

void Counter::setValue(int newValue) {
    if (m_count != newValue) {
        m_count = newValue;
        emit valueChanged(m_count);
    }
}
