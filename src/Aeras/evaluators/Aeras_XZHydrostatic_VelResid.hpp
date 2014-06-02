//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#ifndef AERAS_XZHYDROSTATICRESID_HPP
#define AERAS_XZHYDROSTATICRESID_HPP

#include "Phalanx_ConfigDefs.hpp"
#include "Phalanx_Evaluator_WithBaseImpl.hpp"
#include "Phalanx_Evaluator_Derived.hpp"
#include "Phalanx_MDField.hpp"
#include "Aeras_Layouts.hpp"
#include "Sacado_ParameterAccessor.hpp"

namespace Aeras {
/** \brief XZHydrostatic equation Residual for atmospheric modeling

    This evaluator computes the residual of the XZHydrostatic equation for
    atmospheric dynamics.

*/

template<typename EvalT, typename Traits>
class XZHydrostatic_VelResid : public PHX::EvaluatorWithBaseImpl<Traits>,
                   public PHX::EvaluatorDerived<EvalT, Traits>,
                   public Sacado::ParameterAccessor<EvalT, SPL_Traits>  {

public:
  typedef typename EvalT::ScalarT ScalarT;
  typedef typename EvalT::MeshScalarT MeshScalarT;

  XZHydrostatic_VelResid(const Teuchos::ParameterList& p,
                const Teuchos::RCP<Aeras::Layouts>& dl);

  void postRegistrationSetup(typename Traits::SetupData d,
			     PHX::FieldManager<Traits>& vm);

  void evaluateFields(typename Traits::EvalData d);

  ScalarT& getValue(const std::string &n);

private:

  // Input:
  PHX::MDField<MeshScalarT,Cell,Node,QuadPoint> wBF;
  PHX::MDField<MeshScalarT,Cell,Node,QuadPoint,Dim> wGradBF;

  PHX::MDField<ScalarT,Cell,QuadPoint,Dim> keGrad;
  PHX::MDField<ScalarT,Cell,QuadPoint> uDot;
  PHX::MDField<MeshScalarT,Cell,Point,Dim> coordVec;

  // Output:
  PHX::MDField<ScalarT,Cell,Node> Residual;

  ScalarT Re; // Reynolds number (demo on how to get info from input file)

  const int numNodes;
  const int numQPs;
  const int numDims;
  const int numLevels;
};
}

#endif