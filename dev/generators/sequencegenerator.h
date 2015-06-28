#ifndef SEQUENCEGENERATOR_H
#define SEQUENCEGENERATOR_H


class SequenceGenerator
{
public:
    SequenceGenerator();

    unsigned operator () ();

private:

    unsigned current;
};

#endif // SEQUENCEGENERATOR_H
