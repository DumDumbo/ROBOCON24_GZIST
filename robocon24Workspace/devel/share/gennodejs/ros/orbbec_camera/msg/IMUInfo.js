// Auto-generated. Do not edit!

// (in-package orbbec_camera.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class IMUInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.noise_density = null;
      this.random_walk = null;
      this.reference_temperature = null;
      this.bias = null;
      this.gravity = null;
      this.scale_misalignment = null;
      this.temperature_slope = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('noise_density')) {
        this.noise_density = initObj.noise_density
      }
      else {
        this.noise_density = 0.0;
      }
      if (initObj.hasOwnProperty('random_walk')) {
        this.random_walk = initObj.random_walk
      }
      else {
        this.random_walk = 0.0;
      }
      if (initObj.hasOwnProperty('reference_temperature')) {
        this.reference_temperature = initObj.reference_temperature
      }
      else {
        this.reference_temperature = 0.0;
      }
      if (initObj.hasOwnProperty('bias')) {
        this.bias = initObj.bias
      }
      else {
        this.bias = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('gravity')) {
        this.gravity = initObj.gravity
      }
      else {
        this.gravity = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('scale_misalignment')) {
        this.scale_misalignment = initObj.scale_misalignment
      }
      else {
        this.scale_misalignment = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('temperature_slope')) {
        this.temperature_slope = initObj.temperature_slope
      }
      else {
        this.temperature_slope = new Array(9).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type IMUInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [noise_density]
    bufferOffset = _serializer.float64(obj.noise_density, buffer, bufferOffset);
    // Serialize message field [random_walk]
    bufferOffset = _serializer.float64(obj.random_walk, buffer, bufferOffset);
    // Serialize message field [reference_temperature]
    bufferOffset = _serializer.float64(obj.reference_temperature, buffer, bufferOffset);
    // Check that the constant length array field [bias] has the right length
    if (obj.bias.length !== 3) {
      throw new Error('Unable to serialize array field bias - length must be 3')
    }
    // Serialize message field [bias]
    bufferOffset = _arraySerializer.float64(obj.bias, buffer, bufferOffset, 3);
    // Check that the constant length array field [gravity] has the right length
    if (obj.gravity.length !== 3) {
      throw new Error('Unable to serialize array field gravity - length must be 3')
    }
    // Serialize message field [gravity]
    bufferOffset = _arraySerializer.float64(obj.gravity, buffer, bufferOffset, 3);
    // Check that the constant length array field [scale_misalignment] has the right length
    if (obj.scale_misalignment.length !== 9) {
      throw new Error('Unable to serialize array field scale_misalignment - length must be 9')
    }
    // Serialize message field [scale_misalignment]
    bufferOffset = _arraySerializer.float64(obj.scale_misalignment, buffer, bufferOffset, 9);
    // Check that the constant length array field [temperature_slope] has the right length
    if (obj.temperature_slope.length !== 9) {
      throw new Error('Unable to serialize array field temperature_slope - length must be 9')
    }
    // Serialize message field [temperature_slope]
    bufferOffset = _arraySerializer.float64(obj.temperature_slope, buffer, bufferOffset, 9);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type IMUInfo
    let len;
    let data = new IMUInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [noise_density]
    data.noise_density = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [random_walk]
    data.random_walk = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [reference_temperature]
    data.reference_temperature = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [bias]
    data.bias = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [gravity]
    data.gravity = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [scale_misalignment]
    data.scale_misalignment = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [temperature_slope]
    data.temperature_slope = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 216;
  }

  static datatype() {
    // Returns string type for a message object
    return 'orbbec_camera/IMUInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'efdf590a2d0b51a471d0de8470a87a58';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    float64 noise_density
    float64 random_walk
    float64 reference_temperature
    float64[3] bias
    float64[3] gravity
    float64[9] scale_misalignment
    float64[9] temperature_slope
    
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new IMUInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.noise_density !== undefined) {
      resolved.noise_density = msg.noise_density;
    }
    else {
      resolved.noise_density = 0.0
    }

    if (msg.random_walk !== undefined) {
      resolved.random_walk = msg.random_walk;
    }
    else {
      resolved.random_walk = 0.0
    }

    if (msg.reference_temperature !== undefined) {
      resolved.reference_temperature = msg.reference_temperature;
    }
    else {
      resolved.reference_temperature = 0.0
    }

    if (msg.bias !== undefined) {
      resolved.bias = msg.bias;
    }
    else {
      resolved.bias = new Array(3).fill(0)
    }

    if (msg.gravity !== undefined) {
      resolved.gravity = msg.gravity;
    }
    else {
      resolved.gravity = new Array(3).fill(0)
    }

    if (msg.scale_misalignment !== undefined) {
      resolved.scale_misalignment = msg.scale_misalignment;
    }
    else {
      resolved.scale_misalignment = new Array(9).fill(0)
    }

    if (msg.temperature_slope !== undefined) {
      resolved.temperature_slope = msg.temperature_slope;
    }
    else {
      resolved.temperature_slope = new Array(9).fill(0)
    }

    return resolved;
    }
};

module.exports = IMUInfo;
