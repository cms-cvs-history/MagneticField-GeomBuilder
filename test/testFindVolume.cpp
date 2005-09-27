//#include "Utilities/Configuration/interface/Architecture.h"

/* Performs two tests:
 * 1. Random points are found in one volume
 * 2. Random points are found within one and only one volume.
 * Note that thin gaps and tolerance mess things up.
 */

#include "MagneticField/GeomBuilder/interface/MagGeometry.h"
#include "MagneticField/GeomBuilder/test/stubs/MagGeometryExerciser.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "Utilities/Timing/interface/TimingReport.h"
#include "FWCore/ParameterSet/interface/Makers.h"
#include "FWCore/ParameterSet/interface/parse.h"

#include "stubs/initDDD.h"
#include "MagneticField/Layers/interface/MagVerbosity.h"

#include <iostream>

using namespace std;
using namespace edm;

int main() {
  // Read the geometry
  initDDD("configuration.xml");

  edm::ParameterSet p;
  p.addParameter<double>("findVolumeTolerance", 0.0);
  p.addParameter<bool>("cacheLastVolume", true);
  p.addUntrackedParameter<bool>("timerOn", true);
  
  // hack: set verbosity
  bldVerb::debugOut = false;

  // Create the field geometry
  MagGeometry* field = new MagGeometry(p);

  // Example call...
  cout << "B-field(T) at (0,0,0)(cm): " << field->fieldInTesla(GlobalPoint(0,0,0))<< endl;

  // Stress test of volume finding
  MagGeometryExerciser exe(field);
  exe.testFindVolume(100000);

  delete TimingReport::current();
  return 0;
}

