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

    unsigned int uniqueId;
    unsigned int tileId;
};

#endif // IDGENERATOR_HPP
