#include "Turing.h"

using namespace std;

class Turing: public IterativeRobot
{
private:
	PowerDistributionPanel PDP;
	CANTalon tal1, tal2, tal3;
	CANTalon *tals;

public:
	Turing(): tal1(1), tal2(2), tal3(3), tals(&tal1)
	{
		for(int i = 0; i <= 15; i++)
		{
			auto f = Logger::MakeLogValue<double>("PowerDistributionPanel", Logger::MakeComponentName("current", i).c_str(), std::bind(&PowerDistributionPanel::GetCurrent, &PDP, i));
			SmartDashService::GetInstance().addLog<double>(f, Logger::MakeComponentName("pdp_current", i));
		}

		for(int i = 0; i < 3; i++)
		{
			tals[i].SetVoltageRampRate(5.0);
			auto f = Logger::MakeLogValue(Logger::MakeComponentName("power_level", i+1).c_str(), tals+i, &CANTalon::Get);
			SmartDashService::GetInstance().addLog(f, Logger::MakeComponentName("tal_powerlevel_", i+1));
		}

		auto volt = Logger::MakeLogValue("VOLTAGE", &PDP, &PowerDistributionPanel::GetVoltage);
		SmartDashService::GetInstance().addLog<double>(volt, "pdp_voltage");

		Logger::LogState("GENERAL", LEVEL_t::INFO, "Turing object constructed");
		Logger::LogState("GENERAL", LEVEL_t::NOTICE, string("Built: ")+__DATE__+' '+__TIME__);
	}

private:
	void RobotInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Robot init complete");
	}

	void DisabledInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Disabled Init Complete");
	}

	void DisabledPeriodic() override
	{
	}

	void AutonomousInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Autonomous Init Complete, ready to crack enigma.");
	}

	void AutonomousPeriodic() override
	{

	}

	void TeleopInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Teleop Init Complete");
	}

	void TeleopPeriodic() override
	{

	}

	void TestInit() override
	{
		Logger::LogState("GENERAL", LEVEL_t::INFO, "Test Init Complete");
	}

	void TestPeriodic() override
	{

	}
};

START_ROBOT_CLASS(Turing);
