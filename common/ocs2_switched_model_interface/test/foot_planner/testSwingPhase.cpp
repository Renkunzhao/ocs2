//
// Created by rgrandia on 06.05.20.
//

#include <gtest/gtest.h>

#include "ocs2_switched_model_interface/foot_planner/FootPhase.h"

using namespace switched_model;

TEST(TestSwingPhase, flatTerrainSwing) {
  TerrainPlane flatTerrain;
  const SwingPhase::SwingEvent liftOff{0.5, 0.2, &flatTerrain};
  const SwingPhase::SwingEvent touchdown{1.0, -0.2, &flatTerrain};

  SwingPhase::SwingProfile swingProfile;
  swingProfile.nodes.push_back(SwingPhase::SwingProfile::Node{});

  SwingPhase swingPhase(liftOff, touchdown, swingProfile);

  auto startConstraint = swingPhase.getFootNormalConstraintInWorldFrame(liftOff.time);
  ASSERT_TRUE(startConstraint.velocityMatrix.isApprox(surfaceNormalInWorld((flatTerrain)).transpose()));
  ASSERT_DOUBLE_EQ(startConstraint.positionMatrix.norm(), 0.0);
  ASSERT_LT(std::abs(startConstraint.constant + liftOff.velocity), 1e-9);

  auto midConstraint = swingPhase.getFootNormalConstraintInWorldFrame(0.5 * (liftOff.time + touchdown.time));
  ASSERT_TRUE(midConstraint.velocityMatrix.isApprox(surfaceNormalInWorld((flatTerrain)).transpose()));
  ASSERT_DOUBLE_EQ(midConstraint.positionMatrix.norm(), 0.0);
  ASSERT_LT(std::abs(midConstraint.constant), 1e-9);

  auto endConstraint = swingPhase.getFootNormalConstraintInWorldFrame(touchdown.time);
  ASSERT_TRUE(endConstraint.velocityMatrix.isApprox(surfaceNormalInWorld((flatTerrain)).transpose()));
  ASSERT_DOUBLE_EQ(endConstraint.positionMatrix.norm(), 0.0);
  ASSERT_LT(std::abs(endConstraint.constant + touchdown.velocity), 1e-9);
}

TEST(TestQuinticSwing, interpolating) {
  SwingNode start{0.5, 0.1, 0.2};
  SwingNode mid{0.75, 0.2, -0.3};
  SwingNode end{1.0, -0.4, 0.4};
  QuinticSwing quinticSwing(start, mid, end);

  double tol = 1e-9;
  double eps = std::numeric_limits<double>::epsilon();
  EXPECT_LT(std::abs(quinticSwing.position(start.time) - start.position), tol);
  EXPECT_LT(std::abs(quinticSwing.velocity(start.time) - start.velocity), tol);
  EXPECT_LT(std::abs(quinticSwing.position(mid.time) - mid.position), tol);
  EXPECT_LT(std::abs(quinticSwing.velocity(mid.time) - mid.velocity), tol);
  EXPECT_LT(std::abs(quinticSwing.position(end.time) - end.position), tol);
  EXPECT_LT(std::abs(quinticSwing.velocity(end.time) - end.velocity), tol);

  // Start-end acceleration
  EXPECT_LT(std::abs(quinticSwing.acceleration(start.time)), tol);
  EXPECT_LT(std::abs(quinticSwing.acceleration(end.time)), tol);

  // Continuity
  EXPECT_LT(std::abs(quinticSwing.acceleration(mid.time + eps) - quinticSwing.acceleration(mid.time - eps)), tol);
  EXPECT_LT(std::abs(quinticSwing.jerk(mid.time + eps) - quinticSwing.jerk(mid.time - eps)), tol);
}

TEST(TestQuinticSwing, multipleNodes) {
  // Set some random nodes to interpolate
  std::vector<SwingNode> nodes = {{0.5, 0.1, 0.2}};
  for (int i = 1; i < 10; ++i) {
    nodes.push_back({nodes.back().time + i * 0.1, (i - 5) * 0.1, (i - 3) * 0.4});
  }
  QuinticSwing quinticSwing(nodes);

  double tol = 1e-9;
  double eps = std::numeric_limits<double>::epsilon();
  for (const auto& node : nodes) {
    // interpolation
    EXPECT_LT(std::abs(quinticSwing.position(node.time) - node.position), tol);
    EXPECT_LT(std::abs(quinticSwing.velocity(node.time) - node.velocity), tol);

    // Get pre and post node time (and clamp to interval)
    const scalar_t minTime = std::max(node.time - eps, nodes.front().time);
    const scalar_t plusTime = std::min(node.time + eps, nodes.back().time);
    // Continuity
    EXPECT_LT(std::abs(quinticSwing.acceleration(plusTime) - quinticSwing.acceleration(minTime)), tol);
    EXPECT_LT(std::abs(quinticSwing.jerk(plusTime) - quinticSwing.jerk(minTime)), tol);
  }

  // Start-end acceleration
  EXPECT_LT(std::abs(quinticSwing.acceleration(nodes.front().time)), tol);
  EXPECT_LT(std::abs(quinticSwing.acceleration(nodes.back().time)), tol);
}

TEST(TestQuinticSwing3d, interpolating) {
  SwingNode3d start{0.5, vector3_t::Random(), vector3_t::Random()};
  SwingNode3d mid{0.75, vector3_t::Random(), vector3_t::Random()};
  SwingNode3d end{1.0, vector3_t::Random(), vector3_t::Random()};
  SwingSpline3d swingNode3D(start, mid, end);

  double tol = 1e-9;
  double eps = std::numeric_limits<double>::epsilon();
  EXPECT_LT((swingNode3D.position(start.time) - start.position).norm(), tol);
  EXPECT_LT((swingNode3D.velocity(start.time) - start.velocity).norm(), tol);
  EXPECT_LT((swingNode3D.position(mid.time) - mid.position).norm(), tol);
  EXPECT_LT((swingNode3D.velocity(mid.time) - mid.velocity).norm(), tol);
  EXPECT_LT((swingNode3D.position(end.time) - end.position).norm(), tol);
  EXPECT_LT((swingNode3D.velocity(end.time) - end.velocity).norm(), tol);

  // Start-end acceleration
  EXPECT_LT(swingNode3D.acceleration(start.time).norm(), tol);
  EXPECT_LT(swingNode3D.acceleration(end.time).norm(), tol);

  // Continuity
  EXPECT_LT((swingNode3D.acceleration(mid.time + eps) - swingNode3D.acceleration(mid.time - eps)).norm(), tol);
  EXPECT_LT((swingNode3D.jerk(mid.time + eps) - swingNode3D.jerk(mid.time - eps)).norm(), tol);
}