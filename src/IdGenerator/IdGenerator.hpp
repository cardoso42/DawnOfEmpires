#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP

class IdGenerator
{
public:
    IdGenerator();

    static unsigned int GenerateUniqueId();
    static unsigned int GenerateTileId();

private:
    static IdGenerator* mInstance;

    static unsigned int uniqueId;
    static unsigned int tileId;
};

#endif // IDGENERATOR_HPP
