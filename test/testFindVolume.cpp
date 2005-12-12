
/* PLEASE NOTE:
 * This program is for DEBUGGING purposes only. 
 * It is not supposed to be taken as an example!!!
 * 
 * Performs two tests:
 * 1. Random points must be found found in one volume
 * 2. Random points must be found within one and only one volume.
 * Note that thin gaps and tolerance mess things up.
 */

#include "MagneticField/VolumeBasedEngine/interface/MagGeometry.h"
#include "MagneticField/GeomBuilder/test/stubs/MagGeometryExerciser.h"
#include "DetectorDescription/Core/interface/DDCompactView.h"
#include "DetectorDescription/Core/interface/DDFilteredView.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "Utilities/Timing/interface/TimingReport.h"
#include "FWCore/ParameterSet/interface/Makers.h"
#include "FWCore/ParameterSet/interface/parse.h"

#include "stubs/initDDD.h"
#include "MagneticField/Layers/interface/MagVerbosity.h"
#include "FWCore/Utilities/interface/Exception.h"

#include <iostream>

//dirty hack
#define private public
#include "MagneticField/GeomBuilder/src/MagGeoBuilderFromDDD.h"
#undef public


using namespace std;
using namespace edm;

int main() {
  FileInPath fp("TESTconfiguration.xml");
  initDDD(fp.fullPath());

  DDCompactView cpv;

  edm::ParameterSet p;
  p.addParameter<double>("findVolumeTolerance", 0.0);
  p.addParameter<bool>("cacheLastVolume", true);
  p.addUntrackedParameter<bool>("timerOn", true);
  
  // hack: set verbosity
  bldVerb::debugOut = false;

  // Create the field geometry
  MagGeoBuilderFromDDD builder;
  try{
    builder.build(cpv);
  } catch (cms::Exception& e) {
    cout << e.what();
    abort();
  }
  
  
  MagGeometry* field = new MagGeometry(p,
				       builder.barrelLayers(),
				       builder.endcapSectors(),
				       builder.barrelVolumes(),
				       builder.endcapVolumes());

  // Example call...
  cout << "B-field(T) at (0,0,0)(cm): " << field->fieldInTesla(GlobalPoint(0,0,0))<< endl;

  // Stress test of volume finding
  MagGeometryExerciser exe(field);
  exe.testFindVolume(100000);

  delete TimingReport::current();
  return 0;
}

