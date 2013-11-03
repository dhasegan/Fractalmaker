#ifndef _REGION_MAKER
#define _REGION_MAKER

// System includes
#include <string>

// Local includes
#include "region.hpp"

// Constants 
#define RegionMoveMaximumConstant 0.05 
  // this means that the total zoom is more than 5% we change the location to the new center before we reach the 5% increase

void makeRegionFile(Region a,std::string filename);
void makeRegionFile(Region a,Region b,int i,std::string filename);
double getZoom(Region a,Region b,int i);

#endif
