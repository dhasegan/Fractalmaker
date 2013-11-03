/**
  * @brief File containing the implementation of the FlagParser class.
  *
  * @file FlagParser.cpp
  * @author Corneliu-Claudiu Prodescu
  * @date 24 Jul 2011
  *
  * License: GPL v3
  */

// System includes

#include <assert.h>
#include <getopt.h>                    // C getopt function family
#include <map>                         // C++ map container
#include <string>                      // C string header
#include <vector>                      // C++ vector container
#include <cstdio>

// Local includes

#include "FlagParser.hpp" // FlagParser class declaration

// Namespaces

using namespace std;

// Static declarations

string                     FlagParser::_progName;
map<char, FlagOpt>         FlagParser::_flagOpts;
map<char, vector<string> > FlagParser::_parsedArgs;


void
FlagParser::addFlag(const char    aShortOpt,
                    const string& aLongOpt,
                    int           optMandatory,
                    int           argMandatory)
{
    FlagOpt currentFlag;

    currentFlag.longOpt      = aLongOpt;
    currentFlag.optMandatory = optMandatory;
    currentFlag.argMandatory = argMandatory;
    currentFlag.parsed       = false;

    _flagOpts[aShortOpt] = currentFlag;
}


int
FlagParser::parse(const int   argc,
                  char* const argv[])
{
    map<char, FlagOpt> :: iterator it;
    vector<struct option>          longOpts;
    string                         optString;
    char                           ch;
    struct option                  currentOpt;
    const struct option            zeroOpt = {0, 0, 0, 0};
    int                            optIndex;

    // Storing program name
    _progName = argv[0];

    // Building optString and longOpts
    optString = "+"; // Setting POSIXLY_CORRECT ON

    for (it = _flagOpts.begin(); it != _flagOpts.end(); it++)
    {
        optString += it->first;
        if (it->second.argMandatory == ARG_REQ)
        {
            optString += ":";
        }
        else if (it->second.argMandatory == ARG_OPT)
        {
            optString += "::";
        }

        currentOpt.name    = it->second.longOpt.c_str();
        currentOpt.has_arg = it->second.argMandatory;
        currentOpt.flag    = 0;
        currentOpt.val     = it->first;

        longOpts.push_back(currentOpt);
    }

    // Adding a 0 fill element
    longOpts.push_back(zeroOpt);

    while ((ch = getopt_long(argc, argv,
                             optString.c_str(),
                             &longOpts[0],
                             &optIndex))
            != -1)
    {
        if ((it = _flagOpts.find(ch))
                != _flagOpts.end())
        {
            it->second.parsed = true;
            switch(it->second.argMandatory)
            {
            case ARG_NONE:
                _parsedArgs.insert(make_pair(ch, vector<string>()));
                break;
            case ARG_OPT:
                if (optarg == NULL) continue;
                _parsedArgs[ch].push_back(optarg);
                break;
            case ARG_REQ:
                if (optarg == NULL) goto failure;
                _parsedArgs[ch].push_back(optarg);
                break;

            default:
                assert(0);
            }
        }
        else
        {
            goto failure;
        }
    }

    // Checking if all mandatory arguments were parsed
    for (it = _flagOpts.begin(); it != _flagOpts.end(); it++)
    {
        if (it->second.optMandatory == FLAG_REQ &&
            !it->second.parsed)
        {
            fprintf(stderr, "%s: option -%c|--%s is required\n",
                    argv[0], it->first, it->second.longOpt.c_str());
            goto failure;
        }
    }

    return 0;

failure:
    return -1;
}


bool
FlagParser::hasArg(char aShortOpt)
{
    map<char, vector<string> > :: iterator it;

    if (_parsedArgs.find(aShortOpt) != _parsedArgs.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}


std::string
FlagParser::getArg(char aShortOpt)
{
    vector<string>& args = _parsedArgs[aShortOpt];

    if (!args.empty())
        return args[0];
    else
        return "";
}


std::vector<std::string>
FlagParser::getArgs(char aShortOpt)
{
    return _parsedArgs[aShortOpt];
}


std::string
FlagParser::getUsage()
{
    map<char, FlagOpt> :: iterator it;
    string                         result;
    bool                           first;
    string begin,
           sep1,
           arg,
           sep2,
           align;

    align  = string(_progName.size(), ' ');
    result = "Usage:\n";
    first  = true;

    for (it = _flagOpts.begin(); it != _flagOpts.end(); it++)
    {
        if (it->second.optMandatory == FLAG_REQ)
        {
            sep1 = " ";
            sep2 = "";
        }
        else
        {
            sep1 = "[";
            sep2 = "]";
        }

        if (it->second.argMandatory == ARG_NONE)
        {
            arg  = "";
        }
        else if (it->second.argMandatory == ARG_REQ)
        {
            arg = "arg";
        }
        else
        {
            arg = "[arg]";
        }

        if (first)
        {
            begin = _progName;
            first = false;
        }
        else
        {
            begin = align;
        }

        result += begin + " " + sep1 + "-" + it->first + "|--"
               + it->second.longOpt + " " + arg + " " + sep2 + "\n";
    }

    return result;
}
