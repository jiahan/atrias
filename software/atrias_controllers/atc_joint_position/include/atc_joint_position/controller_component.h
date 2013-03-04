#ifndef __ATC_JOINT_POSITION_H__
#define __ATC_JOINT_POSITION_H__

/*! \file controller_component.h
 *  \author Andrew Peekema
 *  \brief Orocos Component header for atc_joint_position controller.
 */

// Orocos 
#include <rtt/os/main.h>
#include <rtt/RTT.hpp>
#include <rtt/Logger.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/OperationCaller.hpp>
#include <rtt/Component.hpp>

// C
#include <stdlib.h>

#include <atrias_shared/GuiPublishTimer.h>
#include <atrias_shared/globals.h>
#include <robot_invariant_defs.h>

// Datatypes
#include <atc_joint_position/controller_input.h>
#include <atc_joint_position/controller_status.h>
#include <atc_joint_position/controller_log_data.h>
#include <atrias_msgs/robot_state.h>
#include <atrias_msgs/controller_output.h>
#include <atrias_shared/controller_structs.h>

using namespace RTT;
using namespace Orocos;
using namespace atc_joint_position;

namespace atrias {
using namespace shared;
namespace controller {

class ATCJointPosition : public TaskContext {
private:
    // This Operation is called by the RT Operations Manager.
    atrias_msgs::controller_output runController(atrias_msgs::robot_state rs);

    atrias_msgs::controller_output co;

	// Variables for subcontrollers
    std::string pd0Name;
    std::string pd1Name;
    std::string pd2Name;
    std::string pd3Name;
    std::string pd4Name;
    std::string pd5Name;

    TaskContext *pd0;
    TaskContext *pd1;
    TaskContext *pd2;
    TaskContext *pd3;
    TaskContext *pd4;
    TaskContext *pd5;

    Property<double> P0;
    Property<double> D0;
    Property<double> P1;
    Property<double> D1;
    Property<double> P2;
    Property<double> D2;
    Property<double> P3;
    Property<double> D3;
    Property<double> P4;
    Property<double> D4;
    Property<double> P5;
    Property<double> D5;

    // Subcontroller operations
    OperationCaller<double(double, double, double, double)> pd0Controller;
    OperationCaller<double(double, double, double, double)> pd1Controller;
    OperationCaller<double(double, double, double, double)> pd2Controller;
    OperationCaller<double(double, double, double, double)> pd3Controller;
    OperationCaller<double(double, double, double, double)> pd4Controller;
    OperationCaller<double(double, double, double, double)> pd5Controller;
	OperationCaller<MotorAngle(double, double)>             legToMotorPos;

    // Logging
    controller_log_data              logData;
    OutputPort<controller_log_data>  logPort;

    // For the GUI
    shared::GuiPublishTimer                         *pubTimer;
    controller_input                                guiIn;
    controller_status                               guiOut;
    OutputPort<controller_status>                   guiDataOut;
    InputPort<controller_input>                     guiDataIn;

	// internal variables

	double hipangle_l;
	double hipangle_r;
	MotorAngle leftMotorAngle;
	MotorAngle rightMotorAngle;

public:
    // Constructor
    ATCJointPosition(std::string name);

    // Standard Orocos hooks
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
};
}
}

#endif