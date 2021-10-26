/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>
#include <frc2/Timer.h>

class Drivetrain;

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AlignWithTarget
    : public frc2::CommandHelper<frc2::CommandBase, AlignWithTarget> {
 public:
  explicit AlignWithTarget(Drivetrain* drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  void SetupListeners();
  Drivetrain* drivetrain_;
  double* tolerence_;
  double* turn_max_;
  double* turn_min_;
  frc2::PIDController vision_PID_;
  double* p_;
  double* i_;
  double* d_;
  frc2::Timer timer_;
  double* timeontarget_;

  bool running_;
};
