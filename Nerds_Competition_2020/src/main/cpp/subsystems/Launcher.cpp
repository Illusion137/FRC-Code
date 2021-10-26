/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Launcher.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <rev/CANPIDController.h>
#include <rev/ControlType.h>

#include "Config.h"
#include "Constants.h"
#include "nerds/Preferences.h"

Launcher::Launcher() :
  shooter_(CAN_LAUNCHER_MASTER, rev::CANSparkMax::MotorType::kBrushless) {
  SetupListeners();

  double p = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONTROLLER_P.key,
    LAUNCHER_CONTROLLER_P.value);
  double i = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONTROLLER_I.key,
    LAUNCHER_CONTROLLER_I.value);
  double d = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_CONTROLLER_D.key,
    LAUNCHER_CONTROLLER_D.value);
  double max = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_MAX_SPEED.key,
    LAUNCHER_MAX_SPEED.value);
  double min = nerd::Preferences::GetInstance().GetPreference(
    LAUNCHER_MIN_SPEED.key,
    LAUNCHER_MIN_SPEED.value);

  rev::CANPIDController controller = shooter_.GetPIDController();

  controller.SetP(p);
  controller.SetI(i);
  controller.SetD(d);
  // controller.SetOutputRange(min, max);
}

// This method will be called once per scheduler run
void Launcher::Periodic() {
  auto encoder = shooter_.GetEncoder();
  frc::SmartDashboard::PutNumber(
    "SparkMax/Encoder/Velocity",
    encoder.GetVelocity());
  frc::SmartDashboard::PutNumber(
    "SparkMax/Duty Cycle",
    shooter_.GetAppliedOutput());
}

void Launcher::SetLauncherSpeed(double speed) {
  rev::CANPIDController controller = shooter_.GetPIDController();

  // controller.SetReference(speed, rev::ControlType::kVelocity);
  shooter_.Set(speed);
}

void Launcher::SetupListeners() {
  nerd::Preferences::GetInstance().AddFunctionListener(
    LAUNCHER_CONTROLLER_P.key,
    [this] (
      auto table,
      auto name,
      auto entry,
      auto new_value,
      int flag) -> void {
        double value = new_value->GetDouble();
        this->shooter_.GetPIDController().SetP(value);
      });

  nerd::Preferences::GetInstance().AddFunctionListener(
    LAUNCHER_CONTROLLER_I.key,
    [this] (
      auto table,
      auto name,
      auto entry,
      auto new_value,
      int flag) -> void {
        double value = new_value->GetDouble();
        this->shooter_.GetPIDController().SetI(value);
      });

  nerd::Preferences::GetInstance().AddFunctionListener(
    LAUNCHER_CONTROLLER_D.key,
    [this] (
      auto table,
      auto name,
      auto entry,
      auto new_value,
      int flag) -> void {
        double value = new_value->GetDouble();
        this->shooter_.GetPIDController().SetD(value);
      });

  nerd::Preferences::GetInstance().AddFunctionListener(
    LAUNCHER_MAX_SPEED.key,
    [this] (
      auto table,
      auto name,
      auto entry,
      auto new_value,
      int flag) -> void {
        double value = new_value->GetDouble();
        auto controller = this->shooter_.GetPIDController();
        // controller.SetOutputRange(controller.GetOutputMin(), value);
      });

  nerd::Preferences::GetInstance().AddFunctionListener(
    LAUNCHER_MIN_SPEED.key,
    [this] (
      auto table,
      auto name,
      auto entry,
      auto new_value,
      int flag) -> void {
        double value = new_value->GetDouble();
        auto controller = this->shooter_.GetPIDController();
        // controller.SetOutputRange(value, controller.GetOutputMax());
      });
}
