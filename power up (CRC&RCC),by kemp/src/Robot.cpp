
#include <iostream>
#include <string>

#include <Drive/DifferentialDrive.h>
#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Spark.h>
#include <Joystick.h>
#include <Talon.h>
#include <Timer.h>
#include <DigitalInput.h>
#include <ADXRS450_Gyro.h>
#include <Driverstation.h>
#include <math.h>
#include <CameraServer.h>
//int angle=0;
class Robot : public frc::SampleRobot {
public:
	Robot() {
		//angle=toloyi.GetAngle();
		//m_robotDrive.SetExpiration(0.1);
	}
	void RobotInit() {
		//m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		//m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		//frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
		toloyi.Calibrate();
		CameraServer::GetInstance()->StartAutomaticCapture();
	}
	void Autonomous() {
		toloyi.Reset();
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		if(gameData[0]=='R'){
			r2switch();
			//go_fuck();
		}
		if(gameData[0]=='L'){
			l2switch();
			//go_fuck();
		}
	}

	void OperatorControl() override {
		//m_robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {
			if(!stick1.GetRawButton(5) && !stick2.GetRawButton(5)){
				lm1.Set(stick1.GetY()*-0.8);
				lm2.Set(stick1.GetY()*-0.8);
				rm1.Set(stick1.GetRawAxis(5)*0.8);
				rm2.Set(stick1.GetRawAxis(5)*0.8);
			}
			else{
				lm1.Set(stick1.GetY()*-0.4);
				lm2.Set(stick1.GetY()*-0.4);
				rm1.Set(stick1.GetRawAxis(5)*0.4);
				rm2.Set(stick1.GetRawAxis(5)*0.4);
			}
			if(stick2.GetY()<0.2 && stick2.GetY()>-0.2){
				ele1.Set(0);
				ele2.Set(0);
			}
			else if(stick2.GetY()>0.2){
				ele1.Set(stick2.GetY()*0.4);
				ele2.Set(stick2.GetY()*0.4);
			}
			else if(stick2.GetY()<-0.2){
				ele1.Set(stick2.GetY()*0.8);
				ele2.Set(stick2.GetY()*0.8);
			}
			if(stick2.GetRawAxis(5)>0.2 && stick2.GetRawButton(6)){
					intake.Set(-0.45);
			}
			else if(stick2.GetRawAxis(5)>0.2 && !stick2.GetRawButton(6)){
				intake.Set(-0.8);
			}
			if(stick2.GetRawAxis(5)<-0.2 && stick2.GetRawButton(6)){
				intake.Set(0.4);
			}
			else if(stick2.GetRawAxis(5)<-0.2 && !stick2.GetRawButton(6)){
				intake.Set(0.8);
			}
			if(stick2.GetRawAxis(5)>-0.2 && stick2.GetRawAxis(5)<0.2){
				intake.Set(0);
			}

			frc::Wait(0.005);
		}
	}

	void Test() override {}

private:
	// Robot drive system
	//frc::Spark m_leftMotor{0};
	//frc::Spark m_rightMotor{1};
	//frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
	frc::Talon rm1{1};
	frc::Talon rm2{0};
	frc::Talon lm1{2};
	frc::Talon lm2{3};
	frc::Talon ele1{5};
	frc::Talon ele2{6};
	frc::Talon intake{4};


	frc::Joystick stick1{0};
	frc::Joystick stick2{1};

	frc::ADXRS450_Gyro toloyi{};
	std::string gameData;

	//frc::SendableChooser<std::string> m_chooser;
	//const std::string kAutoNameDefault = "Default";
	//const std::string kAutoNameCustom = "My Auto";



//-------------------------------------------------------------------------------------------------------------------


void allstop(){
	lm1.Set(0);
	lm2.Set(0);
	rm1.Set(0);
	rm2.Set(0);
	ele1.Set(0);
	ele2.Set(0);
	intake.Set(0);
}
void chassis_stop(){
	lm1.Set(0);
	lm2.Set(0);
	rm1.Set(0);
	rm2.Set(0);
}
void up_stop(){
	intake.Set(0);
	ele1.Set(0);
	ele2.Set(0);
}
void go_straight(double i){
	lm1.Set(i);
	lm2.Set(i);
	rm1.Set(-i);
	rm2.Set(-i);
	}
void re(){
	double angle=toloyi.GetAngle();
	while(angle<-2 || angle>2){
		if(angle<-2){
		angle=toloyi.GetAngle();
		lm1.Set(-0.4);
		lm2.Set(-0.4);
		rm1.Set(-0.4);
		rm2.Set(-0.4);
		}
		if(angle>2){
		angle=toloyi.GetAngle();
		lm1.Set(0.4);
		lm2.Set(0.4);
		rm1.Set(0.4);
		rm2.Set(0.4);
		}
	}
}



//------------------------------------------------------------------------------------------------------------



void r2switch(){
	float angle;
	int i;
	toloyi.Reset();
	for(int i=0;i<500;i++){
		go_straight(0.4);
	}
	allstop();
	toloyi.Reset();
	while(angle<20){
		angle=toloyi.GetAngle();
		lm1.Set(0.4);
		lm2.Set(0.4);
		rm1.Set(0.4);
		rm2.Set(0.4);
	}
	allstop();
	toloyi.Reset();
	go_straight(0.4);
	ele1.Set(0.3);
	ele2.Set(0.);
	Wait(2);
	allstop();
	intake.Set(0.7);
	Wait(1);
	allstop();
	}


void l2switch(){
	float angle;
	int i;
	toloyi.Reset();
	for(int i=0;i<500;i++){
		go_straight(0.4);
	}
	allstop();
	toloyi.Reset();
	while(angle>-20){
		angle=toloyi.GetAngle();
		lm1.Set(-0.4);
		lm2.Set(-0.4);
		rm1.Set(-0.4);
		rm2.Set(-0.4);
	}
	allstop();
	toloyi.Reset();
	i=26500;
	go_straight(0.4);
	ele1.Set(0.3);
	ele2.Set(0.3);
	Wait(2.5);
	allstop();
	intake.Set(0.7);
	Wait(1);
	allstop();
	}

void go_fuck(){
	go_straight(0.4);
//	lm1.Set(0.4);
//	lm2.Set(0.4);
//	rm1.Set(-0.4);
//	rm2.Set(-0.4);
	Wait(4);
	allstop();
}



};

START_ROBOT_CLASS(Robot)
