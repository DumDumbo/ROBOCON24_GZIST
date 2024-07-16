// Auto-generated. Do not edit!

// (in-package target_detection.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class position {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Class = null;
      this.centerX = null;
      this.centerY = null;
      this.angleX = null;
      this.angleY = null;
      this.distance = null;
    }
    else {
      if (initObj.hasOwnProperty('Class')) {
        this.Class = initObj.Class
      }
      else {
        this.Class = '';
      }
      if (initObj.hasOwnProperty('centerX')) {
        this.centerX = initObj.centerX
      }
      else {
        this.centerX = 0;
      }
      if (initObj.hasOwnProperty('centerY')) {
        this.centerY = initObj.centerY
      }
      else {
        this.centerY = 0;
      }
      if (initObj.hasOwnProperty('angleX')) {
        this.angleX = initObj.angleX
      }
      else {
        this.angleX = 0.0;
      }
      if (initObj.hasOwnProperty('angleY')) {
        this.angleY = initObj.angleY
      }
      else {
        this.angleY = 0.0;
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type position
    // Serialize message field [Class]
    bufferOffset = _serializer.string(obj.Class, buffer, bufferOffset);
    // Serialize message field [centerX]
    bufferOffset = _serializer.uint16(obj.centerX, buffer, bufferOffset);
    // Serialize message field [centerY]
    bufferOffset = _serializer.uint16(obj.centerY, buffer, bufferOffset);
    // Serialize message field [angleX]
    bufferOffset = _serializer.float64(obj.angleX, buffer, bufferOffset);
    // Serialize message field [angleY]
    bufferOffset = _serializer.float64(obj.angleY, buffer, bufferOffset);
    // Serialize message field [distance]
    bufferOffset = _serializer.float64(obj.distance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type position
    let len;
    let data = new position(null);
    // Deserialize message field [Class]
    data.Class = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [centerX]
    data.centerX = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [centerY]
    data.centerY = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [angleX]
    data.angleX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angleY]
    data.angleY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [distance]
    data.distance = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.Class.length;
    return length + 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'target_detection/position';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6b33d03305c0dd807b7a4b6591831277';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string Class   
    uint16 centerX
    uint16 centerY 
    float64 angleX
    float64 angleY
    float64 distance
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new position(null);
    if (msg.Class !== undefined) {
      resolved.Class = msg.Class;
    }
    else {
      resolved.Class = ''
    }

    if (msg.centerX !== undefined) {
      resolved.centerX = msg.centerX;
    }
    else {
      resolved.centerX = 0
    }

    if (msg.centerY !== undefined) {
      resolved.centerY = msg.centerY;
    }
    else {
      resolved.centerY = 0
    }

    if (msg.angleX !== undefined) {
      resolved.angleX = msg.angleX;
    }
    else {
      resolved.angleX = 0.0
    }

    if (msg.angleY !== undefined) {
      resolved.angleY = msg.angleY;
    }
    else {
      resolved.angleY = 0.0
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = 0.0
    }

    return resolved;
    }
};

module.exports = position;
