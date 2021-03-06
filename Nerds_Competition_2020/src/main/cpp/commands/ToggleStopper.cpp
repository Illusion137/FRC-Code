/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleStopper.h"

#include "subsystems/Climber.h"

ToggleStopper::ToggleStopper(Climber* climber) :
  climber_(climber) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({climber_});
}

// Called when the command is initially scheduled.
void ToggleStopper::Initialize() {
  bool state = climber_->GetStopper();
  climber_->SetStopper(!state);
}

// Called repeatedly when this Command is scheduled to run
void ToggleStopper::Execute() {}

// Called once the command ends or is interrupted.
void ToggleStopper::End(bool interrupted) {}

// Returns true when the command should end.
bool ToggleStopper::IsFinished() { return true; }
