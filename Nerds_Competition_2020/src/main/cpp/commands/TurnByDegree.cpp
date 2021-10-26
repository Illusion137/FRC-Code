/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnByDegree.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <units/units.h>

#include "Config.h"
#include "subsystems/Drivetrain.h"
#include "nerds/Preferences.h"

TurnByDegree::TurnByDegree(double degree, Drivetrain* drivetrain)
  : drivetrain_(drivetrain),
    PID_(0, 0, 0),
    degrees_(degree),
    timer_() {
  p_ = new double(0);
  i_ = new double(0);
  d_ = new double(0);
  time_on_target_ = new double(0);
  autonomous_turn_tolerance_ = new double(0);
  autonomous_turn_max_speed_ = new double(0);
  autonomous_turn_min_speed_ = new double (0);

  SetupListeners();

  AddRequirements({drivetrain_});
}

// Called when the command is initially scheduled.
void TurnByDegree::Initialize() {
  double target_heading = drivetrain_->GetHeading() + degrees_;
  if (target_heading > 180) {
    target_heading = -180 + std::fmod(target_heading, 180);
  } else if (target_heading < -180) {
    target_heading = 180 + std::fmod(target_heading, 180);
  }

  PID_.SetPID(*p_, *i_, *d_);
  PID_.EnableContinuousInput(-180, 180);
  PID_.SetSetpoint(target_heading);
  PID_.SetTolerance(*autonomous_turn_tolerance_);

  timer_.Reset();
  running_ = false;
}

// Called repeatedly when this Command is scheduled to run
void TurnByDegree::Execute() {
  double current_heading = drivetrain_->GetHeading();

  double output = PID_.Calculate(current_heading);

  double turn;
  if (PID_.AtSetpoint()) {
    turn = 0;
  } else {
    double slope = *autonomous_turn_max_speed_ - *autonomous_turn_min_speed_;
    turn = slope * std::fabs(output) + *autonomous_turn_min_speed_;

    if (turn > *autonomous_turn_max_speed_) {
      turn = *autonomous_turn_max_speed_;
    }

    turn *= output > 0 ? 1 : -1;
  }

  frc::SmartDashboard::PutNumber("Turn/Output", turn);

  drivetrain_->ArcadeDrive(0, turn, false);
}

// Called once the command ends or is interrupted.
void TurnByDegree::End(bool interrupted) {
  drivetrain_->ArcadeDrive(0, 0, false);
  PID_.Reset();
}

// Returns true when the command should end.
bool TurnByDegree::IsFinished() {
  if (PID_.AtSetpoint()) {
    if (!running_) {
      timer_.Start();
      running_ = true;
    } else {
      return timer_.Get().to<double>() > *time_on_target_;
    }
  } else if (running_) {
    timer_.Reset();
    running_ = false;
  }

  return false;
}

void TurnByDegree::SetupListeners() {
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_P.key, p_);
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_I.key, i_);
  nerd::Preferences::GetInstance().AddListener(AUTO_TURN_D.key, d_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_TIME_ON_TARGET.key,
    time_on_target_);

  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_TOLERANCE.key,
    autonomous_turn_tolerance_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_MAX_SPEED.key,
    autonomous_turn_max_speed_);
  nerd::Preferences::GetInstance().AddListener(
    AUTONOMOUS_TURN_MIN_SPEED.key,
    autonomous_turn_min_speed_);
}
