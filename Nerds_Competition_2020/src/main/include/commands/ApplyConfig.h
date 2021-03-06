/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

/**
 * @brief Allow the robot to apply configurations from NetworkTable to the 
 * instances specified in ApplyConfig
 * 
 */
class ApplyConfig
    : public frc2::CommandHelper<frc2::CommandBase, ApplyConfig> {
 public:
  ApplyConfig();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  bool RunsWhenDisabled();
};
