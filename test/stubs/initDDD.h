#ifndef initDDD_H
#define initDDD_H

//  A simple helper to read the geometry
#include "initDDD.h"
#include "DetectorDescription/Parser/interface/DDLParser.h"
#include "DetectorDescription/Parser/interface/DDLConfiguration.h"
#include "DetectorDescription/Base/interface/DDException.h"
#include "DetectorDescription/Algorithm/src/AlgoInit.h"

#include <string>

static void initDDD(std::string xmlConfiguration){  
  DDLParser * parser = DDLParser::instance();
  AlgoInit();
  parser->dumpFileList();
  DDLConfiguration cf;
  int result1 = cf.readConfig(xmlConfiguration);
  if (result1 !=0) throw DDException("DDLConfiguration: readConfig failed !");
  int result2 = parser->parse(cf);
  if (result2 != 0) throw DDException("DDD-Parser: parsing failed!");
}

#endif
