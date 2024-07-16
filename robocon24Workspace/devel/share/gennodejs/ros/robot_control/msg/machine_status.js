// Auto-generated. Do not edit!

// (in-package robot_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class machine_status {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Roller = null;
      this.Mode = null;
      this.KeepOrNot = null;
      this.PlaceOrNot = null;
      this.RobotStatus = null;
    }
    else {
      if (initObj.hasOwnProperty('Roller')) {
        this.Roller = initObj.Roller
      }
      else {
        this.Roller = 0;
      }
      if (initObj.hasOwnProperty('Mode')) {
        this.Mode = initObj.Mode
      }
      else {
        this.Mode = 0;
      }
      if (initObj.hasOwnProperty('KeepOrNot')) {
        this.KeepOrNot = initObj.KeepOrNot
      }
      else {
        this.KeepOrNot = 0;
      }
      if (initObj.hasOwnProperty('PlaceOrNot')) {
        this.PlaceOrNot = initObj.PlaceOrNot
      }
      else {
        this.PlaceOrNot = 0;
      }
      if (initObj.hasOwnProperty('RobotStatus')) {
        this.RobotStatus = initObj.RobotStatus
      }
      else {
        this.RobotStatus = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type machine_status
    // Serialize message field [Roller]
    bufferOffset = _serializer.uint8(obj.Roller, buffer, bufferOffset);
    // Serialize message field [Mode]
    bufferOffset = _serializer.uint8(obj.Mode, buffer, bufferOffset);
    // Serialize message field [KeepOrNot]
    bufferOffset = _serializer.uint8(obj.KeepOrNot, buffer, bufferOffset);
    // Serialize message field [PlaceOrNot]
    bufferOffset = _serializer.uint8(obj.PlaceOrNot, buffer, bufferOffset);
    // Serialize message field [RobotStatus]
    bufferOffset = _serializer.string(obj.RobotStatus, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type machine_status
    let len;
    let data = new machine_status(null);
    // Deserialize message field [Roller]
    data.Roller = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [Mode]
    data.Mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [KeepOrNot]
    data.KeepOrNot = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [PlaceOrNot]
    data.PlaceOrNot = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [RobotStatus]
    data.RobotStatus = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.RobotStatus.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_control/machine_status';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358fea0a2efe9c679e20648d6430914a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 Roller
    uint8 Mode
    uint8 KeepOrNot
    uint8 PlaceOrNot
    string RobotStatus
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new machine_status(null);
    if (msg.Roller !== undefined) {
      resolved.Roller = msg.Roller;
    }
    else {
      resolved.Roller = 0
    }

    if (msg.Mode !== undefined) {
      resolved.Mode = msg.Mode;
    }
    else {
      resolved.Mode = 0
    }

    if (msg.KeepOrNot !== undefined) {
      resolved.KeepOrNot = msg.KeepOrNot;
    }
    else {
      resolved.KeepOrNot = 0
    }

    if (msg.PlaceOrNot !== undefined) {
      resolved.PlaceOrNot = msg.PlaceOrNot;
    }
    else {
      resolved.PlaceOrNot = 0
    }

    if (msg.RobotStatus !== undefined) {
      resolved.RobotStatus = msg.RobotStatus;
    }
    else {
      resolved.RobotStatus = ''
    }

    return resolved;
    }
};

module.exports = machine_status;
