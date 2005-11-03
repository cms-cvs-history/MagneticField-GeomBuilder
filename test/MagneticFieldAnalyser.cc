

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include <iostream>
#include <string>
//
// class decleration
//

class MagneticFieldAnalyser : public edm::EDAnalyzer {
   public:
      explicit MagneticFieldAnalyser(const edm::ParameterSet&);
      ~MagneticFieldAnalyser();


      virtual void analyze(const edm::Event&, const edm::EventSetup&);
   private:
      // ----------member data ---------------------------
};

MagneticFieldAnalyser::MagneticFieldAnalyser(const edm::ParameterSet& /*iConfig*/)
{
   //now do what ever initialization is needed

}


MagneticFieldAnalyser::~MagneticFieldAnalyser()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
MagneticFieldAnalyser::analyze(const edm::Event& /*iEvent*/, const edm::EventSetup& iSetup)
{
   using namespace edm;
   ESHandle<MagneticField> pSetup;
   iSetup.get<IdealMagneticFieldRecord>().get(pSetup);
   const GlobalPoint g(0.,0.,0.);
   std::cout << "B-field(T) at (0,0,0)(cm): " << pSetup->inTesla(g) << std::endl;
}

DEFINE_FWK_MODULE(MagneticFieldAnalyser)
