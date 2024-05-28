#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP

class IdGenerator
{
public:
    IdGenerator();

    static unsigned int GenerateUniqueId();
    static unsigned int GenerateTileId();
    static unsigned int GenerateEmpireId();

private:
    static IdGenerator* mInstance;

    static unsigned int uniqueId;
    static unsigned int tileId;
    static unsigned int empireId;
};

#endif // IDGENERATOR_HPP
