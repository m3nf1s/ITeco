#ifndef DOUBLER_H
#define DOUBLER_H

#include <QtGlobal>

class Doubler
{
public:
    void GenerateNewValues(quint16 minimal_value, quint16 maximum_value);

    quint16& GetCurrentValue();
    quint16& GetCurrentCountSteps();

    quint16 GetCurrentValue()       const;
    quint16 GetFinalValue()         const;
    quint16 GetCurrentCountSteps()  const;
    quint16 GetFinalCountSteps()    const;

private:
    quint16 current_value_        { 1 };
    quint16 final_value_          { 0 };
    quint16 current_count_steps_  { 0 };
    quint16 minimal_count_steps_  { 0 };
};

#endif // DOUBLER_H
