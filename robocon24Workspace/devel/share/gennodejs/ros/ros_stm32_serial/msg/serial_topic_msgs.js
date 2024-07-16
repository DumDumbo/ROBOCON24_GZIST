// Auto-generated. Do not edit!

// (in-package ros_stm32_serial.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class serial_topic_msgs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.flag = null;
      this.status = null;
      this.linearX = null;
      this.linearY = null;
      this.angularZ = null;
      this.LaserFront = null;
      this.LaserL = null;
      this.LaserR = null;
      this.LaserRear = null;
      this.Roller = null;
      this.Mode = null;
      this.KeepOrNot = null;
      this.PlaceOrNot = null;
      this.RobotStatus = null;
    }
    else {
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = 0.0;
      }
      if (initObj.hasOwnProperty('status')) {
        this.status = initObj.status
      }
      else {
        this.status = 0.0;
      }
      if (initObj.hasOwnProperty('linearX')) {
        this.linearX = initObj.linearX
      }
      else {
        this.linearX = 0.0;
      }
      if (initObj.hasOwnProperty('linearY')) {
        this.linearY = initObj.linearY
      }
      else {
        this.linearY = 0.0;
      }
      if (initObj.hasOwnProperty('angularZ')) {
        this.angularZ = initObj.angularZ
      }
      else {
        this.angularZ = 0.0;
      }
      if (initObj.hasOwnProperty('LaserFront')) {
        this.LaserFront = initObj.LaserFront
      }
      else {
        this.LaserFront = 0;
      }
      if (initObj.hasOwnProperty('LaserL')) {
        this.LaserL = initObj.LaserL
      }
      else {
        this.LaserL = 0;
      }
      if (initObj.hasOwnProperty('LaserR')) {
        this.LaserR = initObj.LaserR
      }
      else {
        this.LaserR = 0;
      }
      if (initObj.hasOwnProperty('LaserRear')) {
        this.LaserRear = initObj.LaserRear
      }
      else {
        this.LaserRear = 0;
      }
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
    // Serializes a message object of type serial_topic_msgs
    // Serialize message field [flag]
    bufferOffset = _serializer.float64(obj.flag, buffer, bufferOffset);
    // Serialize message field [status]
    bufferOffset = _serializer.float64(obj.status, buffer, bufferOffset);
    // Serialize message field [linearX]
    bufferOffset = _serializer.float64(obj.linearX, buffer, bufferOffset);
    // Serialize message field [linearY]
    bufferOffset = _serializer.float64(obj.linearY, buffer, bufferOffset);
    // Serialize message field [angularZ]
    bufferOffset = _serializer.float64(obj.angularZ, buffer, bufferOffset);
    // Serialize message field [LaserFront]
    bufferOffset = _serializer.int32(obj.LaserFront, buffer, bufferOffset);
    // Serialize message field [LaserL]
    bufferOffset = _serializer.int32(obj.LaserL, buffer, bufferOffset);
    // Serialize message field [LaserR]
    bufferOffset = _serializer.int32(obj.LaserR, buffer, bufferOffset);
    // Serialize message field [LaserRear]
    bufferOffset = _serializer.int32(obj.LaserRear, buffer, bufferOffset);
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
    //deserializes a message object of type serial_topic_msgs
    let len;
    let data = new serial_topic_msgs(null);
    // Deserialize message field [flag]
    data.flag = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [status]
    data.status = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [linearX]
    data.linearX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [linearY]
    data.linearY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angularZ]
    data.angularZ = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [LaserFront]
    data.LaserFront = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [LaserL]
    data.LaserL = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [LaserR]
    data.LaserR = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [LaserRear]
    data.LaserRear = _deserializer.int32(buffer, bufferOffset);
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
    return length + 64;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_stm32_serial/serial_topic_msgs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd5bec99ac5726ba6e665cc5e4980b15b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 flag
    float64 status
    float64 linearX
    float64 linearY
    float64 angularZ
    int32 LaserFront
    int32 LaserL
    int32 LaserR
    int32 LaserRear
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
    const resolved = new serial_topic_msgs(null);
    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = 0.0
    }

    if (msg.status !== undefined) {
      resolved.status = msg.status;
    }
    else {
      resolved.status = 0.0
    }

    if (msg.linearX !== undefined) {
      resolved.linearX = msg.linearX;
    }
    else {
      resolved.linearX = 0.0
    }

    if (msg.linearY !== undefined) {
      resolved.linearY = msg.linearY;
    }
    else {
      resolved.linearY = 0.0
    }

    if (msg.angularZ !== undefined) {
      resolved.angularZ = msg.angularZ;
    }
    else {
      resolved.angularZ = 0.0
    }

    if (msg.LaserFront !== undefined) {
      resolved.LaserFront = msg.LaserFront;
    }
    else {
      resolved.LaserFront = 0
    }

    if (msg.LaserL !== undefined) {
      resolved.LaserL = msg.LaserL;
    }
    else {
      resolved.LaserL = 0
    }

    if (msg.LaserR !== undefined) {
      resolved.LaserR = msg.LaserR;
    }
    else {
      resolved.LaserR = 0
    }

    if (msg.LaserRear !== undefined) {
      resolved.LaserRear = msg.LaserRear;
    }
    else {
      resolved.LaserRear = 0
    }

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

module.exports = serial_topic_msgs;
