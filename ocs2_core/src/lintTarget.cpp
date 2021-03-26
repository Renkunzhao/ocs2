#include <ocs2_core/OCS2NumericTraits.h>
#include <ocs2_core/Types.h>

// Automatic Differentation
#include <ocs2_core/automatic_differentiation/CppAdInterface.h>
#include <ocs2_core/automatic_differentiation/CppAdSparsity.h>
#include <ocs2_core/automatic_differentiation/FiniteDifferenceMethods.h>

// Constraint
#include <ocs2_core/constraint/ConstraintBase.h>
#include <ocs2_core/constraint/ConstraintBaseAD.h>
#include <ocs2_core/constraint/ConstraintCollection.h>
#include <ocs2_core/constraint/LinearConstraint.h>
#include <ocs2_core/constraint/StateConstraint.h>
#include <ocs2_core/constraint/StateInputConstraint.h>

// Control
#include <ocs2_core/control/ControllerBase.h>
#include <ocs2_core/control/ControllerType.h>
#include <ocs2_core/control/FeedforwardController.h>
#include <ocs2_core/control/LinearController.h>
#include <ocs2_core/control/StateBasedLinearController.h>
#include <ocs2_core/control/TrajectorySpreadingControllerAdjustment.h>

// Cost
#include <ocs2_core/cost/CostCollection.h>
#include <ocs2_core/cost/CostDesiredTrajectories.h>
#include <ocs2_core/cost/CostFunctionBase.h>
#include <ocs2_core/cost/QuadraticCostFunction.h>
#include <ocs2_core/cost/QuadraticStateCost.h>
#include <ocs2_core/cost/QuadraticStateInputCost.h>
#include <ocs2_core/cost/StateCost.h>
#include <ocs2_core/cost/StateInputCost.h>

// Dynamics
#include <ocs2_core/dynamics/ControlledSystemBase.h>
#include <ocs2_core/dynamics/LinearSystemDynamics.h>
#include <ocs2_core/dynamics/SystemDynamicsBase.h>
#include <ocs2_core/dynamics/SystemDynamicsBaseAD.h>
#include <ocs2_core/dynamics/SystemDynamicsLinearizer.h>
#include <ocs2_core/dynamics/TransferFunctionBase.h>

// Initialization
#include <ocs2_core/initialization/OperatingPoints.h>
#include <ocs2_core/initialization/SystemOperatingTrajectoriesBase.h>

// Integration
#include <ocs2_core/integration/Integrator.h>
#include <ocs2_core/integration/IntegratorBase.h>
#include <ocs2_core/integration/Observer.h>
#include <ocs2_core/integration/OdeBase.h>
#include <ocs2_core/integration/OdeFunc.h>
#include <ocs2_core/integration/StateTriggeredEventHandler.h>
#include <ocs2_core/integration/SystemEventHandler.h>
#include <ocs2_core/integration/steppers.h>

// Logic
#include <ocs2_core/logic/ModeSchedule.h>

// Loopshaping
#include <ocs2_core/loopshaping/Loopshaping.h>

// Misc
#include <ocs2_core/misc/Benchmark.h>
// #include <ocs2_core/misc/LTI_Equations.h>
// #include <ocs2_core/misc/LinearFunction.h>
#include <ocs2_core/misc/LinearInterpolation.h>
#include <ocs2_core/misc/LoadData.h>
#include <ocs2_core/misc/Lookup.h>
#include <ocs2_core/misc/SetThreadPriority.h>
#include <ocs2_core/misc/randomMatrices.h>

// model_data
#include <ocs2_core/model_data/ModelData.h>
#include <ocs2_core/model_data/ModelDataLinearInterpolation.h>

// soft_constraint
#include <ocs2_core/soft_constraint/SoftConstraintPenalty.h>
#include <ocs2_core/soft_constraint/StateInputSoftConstraint.h>
#include <ocs2_core/soft_constraint/StateSoftConstraint.h>
#include <ocs2_core/soft_constraint/penalties/PenaltyBase.h>
#include <ocs2_core/soft_constraint/penalties/QuadraticPenalty.h>
#include <ocs2_core/soft_constraint/penalties/RelaxedBarrierPenalty.h>
#include <ocs2_core/soft_constraint/penalties/SmoothAbsolutePenalty.h>
#include <ocs2_core/soft_constraint/penalties/SquaredHingePenalty.h>

// dummy target for clang toolchain
int main() {
  return 0;
}
