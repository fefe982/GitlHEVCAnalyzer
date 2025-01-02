#ifndef COMTU_H
#define COMTU_H
#include "gitldef.h"
class ComTU
{
public:
    ComTU();
    ADD_CLASS_FIELD(std::vector<ComTU>, apcTUs, getTUs, setTUs)
    ADD_CLASS_FIELD(short, iX, getX, setX)                                        ///< X Position in frame
    ADD_CLASS_FIELD(short, iY, getY, setY)                                        ///< Y Position in frame
    ADD_CLASS_FIELD(short, iSize, getSize, setSize)                               ///< CU Size

};

#endif // COMTU_H
