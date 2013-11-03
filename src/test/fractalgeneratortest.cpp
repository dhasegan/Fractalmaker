
// System includes
#include <stdlib.h>

// Local includes
#include "types/fractalgenerator.hpp"
#include "utils/FlagParser.hpp"

int main(int argc,char* argv[])
{
    int ret;

    FlagParser::addFlag('s', "Source", FLAG_REQ, ARG_REQ );
    FlagParser::addFlag('p', "process-nr", FLAG_OPT, ARG_REQ);
    FlagParser::addFlag('n', "number-of-processes", FLAG_OPT, ARG_REQ);

    if ((ret = FlagParser::parse(argc, argv))!= 0)
    {
        fprintf(stderr, "%s", FlagParser::getUsage().c_str());
        exit(0);
    }


    FractalGenerator fg(FlagParser::getArg('s'));

    if (FlagParser::hasArg('p'))
    {
        if (FlagParser::hasArg('n'))
        {
            int p = atoi(FlagParser::getArg('p').c_str());
            int nrp = atoi(FlagParser::getArg('n').c_str());
            fg.generate(p,nrp);
        }
        else
        {
            fprintf(stderr,"Please input both flag 'p' and 'n' or neither.\n");
            exit(0);
        }
    }
    else
        fg.generate();


    return 0;
}
