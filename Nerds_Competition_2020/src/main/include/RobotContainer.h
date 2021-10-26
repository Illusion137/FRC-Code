/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>

#include "commands/ApplyConfig.h"
#include "commands/ConveyorVariable.h"
#include "commands/DriveByDistance.h"
#include "commands/DriveJoystick.h"
#include "commands/TurnByDegree.h"
#include "commands/ToggleExtender.h"
#include "commands/ToggleStopper.h"
#include "subsystems/Climber.h"
#include "subsystems/Conveyor.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Launcher.h"
#include "subsystems/OI.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  Climber climber_;
  Conveyor conveyor_;
  Drivetrain drivetrain_;
  Intake intake_;
  Launcher launcher_;
  OI oi_;


  ApplyConfig apply_config_;
  DriveJoystick drive_joy_;
  ConveyorVariable variable_;

  void ConfigureButtonBindings();
};
