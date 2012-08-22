/*
 * globals.h
 *
 * Defines structs, enums, and global variables that need or might need to be
 * used in multiple places within the Atrias control code.
 *
 *  Created on: Jul 31, 2012
 *      Author: Michael Anderson
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdint.h>

#define SECOND_IN_NANOSECONDS 1000000000LL

//Use namespaces for bonus points (you can't win the game without bonus points)
namespace atrias {

namespace controllerManager {

typedef uint8_t UserCommand_t;

/*
 * Represents the command sent to the Controller Manager from the GUI
 */
enum class UserCommand: UserCommand_t {
    STOP = 0,
    RUN,
    E_STOP,
    UNLOAD_CONTROLLER
};

typedef uint8_t ControllerManagerState_t;

/*
 * Represents the state of the controller manager
 *
 * TODO: CONTROLLER_STARTING and CONTROLLER_STOPPING are for controller startup
 * and shutdown sequences, which will need to be implemented later
 */
enum class ControllerManagerState: ControllerManagerState_t {
    NO_CONTROLLER_LOADED = 0,
    CONTROLLER_STOPPED,
    CONTROLLER_RUNNING,
    CONTROLLER_STARTING,
    CONTROLLER_STOPPING,
    CONTROLLER_ESTOPPED
};

typedef uint8_t ControllerManagerError_t;

/*
 * Represents the type of an error encountered by the Controller Manager
 */
enum class ControllerManagerError: ControllerManagerError_t {
    NO_ERROR = 0,
    CONTROLLER_PACKAGE_NOT_FOUND,
    CONTROLLER_STATE_MACHINE_NOT_FOUND,
    CONTROLLER_STATE_MACHINE_EXCEPTION
};

typedef uint8_t RtOpsCommand_t;

/*
 * Represents the command sent to RT Ops from the controller manager
 */
enum class RtOpsCommand: RtOpsCommand_t {
    NO_CONTROLLER_LOADED = 0,
    DISABLE, //Controller is loaded but not enabled
    ENABLE,  //Controller is both loaded and enabled
    RESET,
    E_STOP
};

typedef int8_t RtOpsEvent_t;

/** @brief Represents an RT Ops event.
  */
enum class RtOpsEvent: RtOpsEvent_t {
    INVALID_CM_COMMAND = 0,   // An invalid command was received from the Controller Manager
    INVALID_RT_OPS_STATE,     // The internal RT Ops state was somehow bad.
    MISSED_DEADLINE,          // We missed a deadline (timing overshoot). This is just a warning.
    CM_COMMAND_ESTOP,         // The controller manager sent an EStop command.
    ACK_NO_CONTROLLER_LOADED, // Acknowledges a NO_CONTROLLER_LOADED command from the CM
    ACK_DISABLE,              // Acknowledges a DISABLE command from the CM
    ACK_ENABLE,               // Acknowledges an ENABLE command from the CM
    ACK_RESET,                // Acknowledges a RESET command from the CM
    ACK_E_STOP,               // Acknowledges an E_STOP command from the CM
    ACK_INVALID,              // This shouldn't ever be sent... it indicates an internal inconsistency in the state machine.
    CONTROLLER_ESTOP,         // The controller commanded an estop.
    MEDULLA_ESTOP             // Sent when any Medulla goes into error mode.
};

}

}

#endif /* GLOBALS_H_ */
